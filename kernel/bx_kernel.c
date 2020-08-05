/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* includes ------------------------------------------------------------------*/

#include "bx_kernel.h"
#include "bx_kernel_timer.h"
#include "bx_service.h"
#include <string.h>

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

struct bx_msg {
    u32     dst;
    u32     msg;
    u32     param0;
    u32     param1;
};

struct bx_delay_msg {
    u32     dst;
    u32     msg;
    u32     param0;
    u32     param1;
    //kernel timer id
    u16     bkt_id;
    bool    used;
};

struct bx_msg_handle {
    struct bx_msg       hub[BXKE_MSG_CONFIG_MAX_COUNT];
    u32                 start;
    u32                 count;
};

struct bx_delay_msg_handle {
    struct bx_delay_msg hub[BXKE_DELAY_MSG_CONFIG_MAX_COUNT];
};

struct bx_service_handle {
    struct bx_service   hub[BXKE_SERVICE_CONFIG_MAX_COUNT];
    u32                 count;  /* always increase */
};

struct bx_async {
    s32 dst;
    u32 prop;
    u32 param0;
    u32 param1;
    async_callback cb_func;
};

struct bx_async_handle {
    u32 count;
    u32 index;
    struct bx_async hub[BX_ASYNC_MAX_COUNT];
};


/* private variables ---------------------------------------------------------*/
static struct   bx_msg_handle           msg_hdl;
static struct   bx_delay_msg_handle     dly_msg_hdl;
static struct   bx_service_handle       service_hdl;

static struct   bx_async_handle         async_hdl = {0};

static s32      kernel_service_id = -1;
//当前的服务
static s32      current_service_id=0;
/* exported variables --------------------------------------------------------*/
volatile u32    interrupt_disable_count = 0;
volatile u32    kernel_time             = 0;
/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static struct bx_msg * get_unused_msg( void )
{
    if( msg_hdl.count >= BXKE_MSG_CONFIG_MAX_COUNT ) {
        return NULL;
    }
    u32 index = ( msg_hdl.start + msg_hdl.count ) % BXKE_MSG_CONFIG_MAX_COUNT;
    msg_hdl.count++;
    return &msg_hdl.hub[index];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static struct bx_msg * get_next_msg( void )
{
    if( msg_hdl.count == 0 ) {
        return NULL;
    }
    u32 index = msg_hdl.start;
    msg_hdl.start++;
    msg_hdl.start %= BXKE_MSG_CONFIG_MAX_COUNT;
    msg_hdl.count--;
    return &msg_hdl.hub[index];
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t kernel_msg_handle(s32 srv, u32 msg, u32 param0, u32 param1 )
{
    struct bx_async * p_async = ( struct bx_async * )param0;
    if( p_async == NULL ) {
        return BX_ERR_EMPTY;
    }
    bx_err_t  err = BX_OK;
    switch( msg ) {
        case BXM_KERNEL_ASET:
            if( ! bx_set( p_async->dst, p_async->prop, p_async->param0, p_async->param1 ) ) {
                err = BX_ERROR;
            }
            break;

        case BXM_KERNEL_AGET:
            if( ! bx_get( p_async->dst, p_async->prop, ( u8 * )p_async->param0, p_async->param1 ) ) {
                err = BX_ERROR;
            }
            break;

        default:
            err = BX_ERROR;
            break;
    }
    if( p_async->cb_func != NULL ) {
        p_async->cb_func( err, p_async->prop, p_async->param0, p_async->param1 );
    }
    async_hdl.count--;
    return BX_OK;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_init( void )
{
    memset( &msg_hdl, 0, sizeof( struct bx_msg_handle ) );
    memset( &dly_msg_hdl, 0, sizeof( struct bx_delay_msg_handle ) );

    bx_kernel_timer_init();

    struct bx_service svc;
    svc.msg_handle_func = kernel_msg_handle;
    svc.name = "Kernel Name";
    svc.prop_get_func = NULL;
    svc.prop_set_func = NULL;
    kernel_service_id = bx_register( &svc );

    //bxs_init();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_schedule( void )
{
    while( 1 ) {
        struct bx_msg * pmsg = get_next_msg();
        if( pmsg == NULL ) {
            // do something to notify app
            return;
        }

        msg_handle_f func = service_hdl.hub[pmsg->dst].msg_handle_func ;
        current_service_id = pmsg->dst;
        
        if( func == NULL ) {
            // do something to notify app
            continue;
        }
        bx_err_t err = func( pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        if( err == BX_OK ) {
            // do something to notify app
        } else if ( err == BX_ERR_BUSY ) {
            //把消息再扔进队列
            bx_post( pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        } else {
            // do something to notify app
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_post( u32 dst, u32 msg, u32 param0, u32 param1 )
{
    struct bx_msg * pmsg = get_unused_msg();
    if( !pmsg ) {
        return false;
    }
    GLOBAL_DISABLE_IRQ();
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    GLOBAL_ENABLE_IRQ();
    return true;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u16 get_kernel_timer_id( u32 dst, u32 msg )
{
    for( uint32_t i = 0 ; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        struct bx_delay_msg * pmsg = &dly_msg_hdl.hub[i];
        if( pmsg->dst == dst && pmsg->msg == msg  ) {
            return pmsg->bkt_id;
        }
    }
    return 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_defer( u32 dst, u32 msg, u32 param0, u32 param1, u32 time )
{
    u16 id = get_kernel_timer_id( dst, msg );
    if( id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( id );
    }

    //重新设置时间
    id = bx_kernel_timer_creat( time, 1 );
    if( id == 0 ) {
        return false;
    }
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   : period unit ms
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_repeat( u32 dst, u32 msg, u32 param0, u32 param1, u32 period )
{
    u16 id = get_kernel_timer_id( dst, msg );
    if( id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( id );
    }

    //重新设置时间
    id = bx_kernel_timer_creat( period, BX_FOREVER );
    if( id == 0 ) {
        return false;
    }
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_repeatn( u32 dst, u32 msg, u32 param0, u32 param1, u32 period, s32 num )
{
    u16 id = get_kernel_timer_id( dst, msg );
    if( id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( id );
    }

    //重新设置时间
    id = bx_kernel_timer_creat( period, num );
    if( id == 0 ) {
        return false;
    }
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_cancel( u32 dst, u32 msg )
{
    u16 id = get_kernel_timer_id( dst, msg );
    if( id == 0 ) {
        return;
    }
    bx_kernel_timer_stop( id );
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );
    pmsg->used = false;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bx_register( struct bx_service * p_svc )
{
    if( service_hdl.count < BXKE_SERVICE_CONFIG_MAX_COUNT ) {
        GLOBAL_DISABLE_IRQ();
        u32 index = service_hdl.count;
        service_hdl.hub[index].prop_set_func = p_svc->prop_set_func;
        service_hdl.hub[index].prop_get_func = p_svc->prop_get_func;
        service_hdl.hub[index].msg_handle_func = p_svc->msg_handle_func;
        service_hdl.hub[index].name = p_svc->name;
        service_hdl.count++;
        GLOBAL_ENABLE_IRQ();
        return index;
    } else {
        return -1;
    }
}

struct bx_subject {
    s32 src;
    s32 dst;
    u32 msg;
};

struct bx_subject_hub {
    u32 count;
    struct bx_subject hub[BX_SUBSCIBE_MAX_COUNT];
};

static struct bx_subject_hub subject_hub = {0};

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_subscibe( s32 dst, u32 msg, u32 param0, u32 param1 )
{
    if( subject_hub.count >= BX_SUBSCIBE_MAX_COUNT ) {
        return false;
    }
    
    u32 count = subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( subject_hub.hub[i].src != current_service_id ) {
            continue;
        }
        if( subject_hub.hub[i].dst != dst ) {
            continue;
        }
        if( subject_hub.hub[i].msg == msg ) {
            return true;
        }
    }
    
    GLOBAL_DISABLE_IRQ();

    subject_hub.hub[subject_hub.count].src = current_service_id;
    subject_hub.hub[subject_hub.count].dst = dst;
    subject_hub.hub[subject_hub.count].msg = msg;
    subject_hub.count++;

    GLOBAL_ENABLE_IRQ();

    return true;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_public(s32 src, u32 msg, u32 param0, u32 param1 )
{
    u32 count = subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( subject_hub.hub[i].dst != src ) {
            continue;
        }
        if( subject_hub.hub[i].msg == msg ) {
            if( !bx_post( subject_hub.hub[i].src, msg, param0, param1 ) ) {
                // do something to notify app
            }
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :不可在中断中使用
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_set( s32 dst, u32 prop, u32 param0, u32 param1 )
{
//    if( __get_IPSR() != 0 ) {
//        return BX_ERR_PERM;
//    }
    if( dst > service_hdl.count || service_hdl.hub[dst].prop_set_func == NULL ) {
        return BX_ERR_NOTSUP;
    }

    return service_hdl.hub[dst].prop_set_func(dst, prop, param0, param1 );
        
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_get( s32 dst, u32 prop, u8 * buff, u32 len )
{
//    if( __get_IPSR() != 0 ) {
//        return BX_ERR_PERM;
//    }
    if( dst > service_hdl.count || service_hdl.hub[dst].prop_get_func == NULL ) {
        return false;
    }

    return service_hdl.hub[dst].prop_get_func(dst, prop, ( u32 )buff, len );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_aset( s32 dst, u32 prop, u32 param0, u32 param1 )
{
    if( async_hdl.count >= BX_ASYNC_MAX_COUNT ) {
        return false;
    }

    GLOBAL_DISABLE_IRQ();
    u32 index = async_hdl.index;
    async_hdl.hub[index].dst = dst;
    async_hdl.hub[index].prop = prop;
    async_hdl.hub[index].param0 = param0;
    async_hdl.hub[index].param1 = param1;
    //async_hdl.hub[index].cb_func = cb_func;
    async_hdl.index++;
    async_hdl.index %= BX_ASYNC_MAX_COUNT;
    async_hdl.count++;
    GLOBAL_ENABLE_IRQ();

    return bx_post( kernel_service_id, BXM_KERNEL_ASET, ( u32 ) & ( async_hdl.hub[index] ), 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_aget( s32 dst, u32 prop, u8 * buff, u32 len )
{
    if( async_hdl.count >= BX_ASYNC_MAX_COUNT ) {
        return false;
    }

    GLOBAL_DISABLE_IRQ();
    u32 index = async_hdl.index;
    async_hdl.hub[index].dst = dst;
    async_hdl.hub[index].prop = prop;
    async_hdl.hub[index].param0 = ( u32 )buff;
    async_hdl.hub[index].param1 = len;
    //async_hdl.hub[index].cb_func = cb_func;
    async_hdl.index++;
    async_hdl.index %= BX_ASYNC_MAX_COUNT;
    async_hdl.count++;
    GLOBAL_ENABLE_IRQ();

    return bx_post( kernel_service_id, BXM_KERNEL_AGET, ( u32 ) & ( async_hdl.hub[index] ), 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_call( s32 dst,u32 msg,u32 param0,u32 param1)
{
//    if( __get_IPSR() != 0 ) {
//        return BX_ERR_PERM;
//    }
    if( dst > service_hdl.count || service_hdl.hub[dst].prop_get_func == NULL ) {
        return BX_ERR_EMPTY;
    }
    return service_hdl.hub[dst].msg_handle_func(dst, msg, param0, param1 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_err(s32 svc, u32 msg,u32 param0,u32 param1, bx_err_t err )
{
    // 当前服务的 msg 出现错误 current_service_id
    //存log
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u32  bx_service_get_count( void )
{
    return service_hdl.count;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
struct bx_service * bx_get_service( s32 id )
{
    if( id >= service_hdl.count || id < 0   ) {
        return NULL;
    }
    return &service_hdl.hub[id];
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
void bx_kernel_timer_timeout_callback( u16 id, bool end_of_repeat )
{
    //bxs_logln( "id:%X %X", id, BKT_ID_TO_INDEX(id) );

    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );

    //bxs_logln("%08X:%08x",pmsg->dst,pmsg->msg);
    if( pmsg->used ) {
        bx_post( pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
    }
    if( end_of_repeat ) {
        pmsg->used = false;
    }
}
/*=========================== end of import function =========================*/

/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



