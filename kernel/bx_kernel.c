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
#include <string.h>
#include "apollo_00_reg.h"
#include "bx_dbg.h"
/* private define ------------------------------------------------------------*/
#define KERNEL_DATA_SECTION __attribute__((section("kernel_data_section")))

#define KERNEL_DATA_START   (0x12345678)
#define KERNEL_DATA_END     (0x9ABCEDF0)
/* private typedef -----------------------------------------------------------*/

struct bx_msg {
    s32     src;
    s32     dst;
    u32     msg;
    u32     param0;
    u32     param1;
};

struct bx_delay_msg {
    s32     src;
    s32     dst;
    u32     msg;
    u32     param0;
    u32     param1;
    
    void    (*cb)( void * );
    void *  data;
    
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

struct bx_subject {
    s32 src;
    s32 dst;
    u32 msg;
};

struct bx_subject_hub {
    u32 count;
    struct bx_subject hub[BX_SUBSCIBE_MAX_COUNT];
};


struct bx_kernel_data {
    u32 start;
    bool    kernel_is_busy;
    s32     current_msg_source_id;
    s32     current_service_id;
    struct  bx_msg_handle           msg_hdl;
    struct  bx_delay_msg_handle     dly_msg_hdl;
    struct  bx_service_handle       service_hdl;
    struct  bx_subject_hub          subject_hub;
    u32 end;
};
/* private variables ---------------------------------------------------------*/

KERNEL_DATA_SECTION static struct bx_kernel_data bx_ke_env;

//KERNEL_DATA_SECTION static u32      kernel_data_start;
//KERNEL_DATA_SECTION volatile static s32     current_service_id;
//KERNEL_DATA_SECTION volatile static s32     current_msg_source_id;
//KERNEL_DATA_SECTION volatile static bool    kernel_is_busy;

//KERNEL_DATA_SECTION static struct   bx_msg_handle           msg_hdl;
//KERNEL_DATA_SECTION static struct   bx_delay_msg_handle     dly_msg_hdl;
//KERNEL_DATA_SECTION static struct   bx_service_handle       service_hdl;
//KERNEL_DATA_SECTION static struct   bx_subject_hub          subject_hub;
//KERNEL_DATA_SECTION static   u32    kernel_data_end;

/* exported variables --------------------------------------------------------*/
volatile u32 interrupt_disable_count;

/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static struct bx_msg * get_unused_msg( void )
{
    if( bx_ke_env.msg_hdl.count >= BXKE_MSG_CONFIG_MAX_COUNT ) {
        return NULL;
    }
    u32 index = ( bx_ke_env.msg_hdl.start + bx_ke_env.msg_hdl.count ) % BXKE_MSG_CONFIG_MAX_COUNT;
    bx_ke_env.msg_hdl.count++;
    return &bx_ke_env.msg_hdl.hub[index];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static struct bx_msg * get_next_msg( void )
{
    if( bx_ke_env.msg_hdl.count == 0 ) {
        return NULL;
    }
    u32 index = bx_ke_env.msg_hdl.start;
    bx_ke_env.msg_hdl.start++;
    bx_ke_env.msg_hdl.start %= BXKE_MSG_CONFIG_MAX_COUNT;
    bx_ke_env.msg_hdl.count--;
    return &bx_ke_env.msg_hdl.hub[index];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static __inline u16 get_kernel_timer_id( u32 dst, u32 msg )
{
    for( uint32_t i = 0 ; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        struct bx_delay_msg * pmsg = &bx_ke_env.dly_msg_hdl.hub[i];
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
static __inline u16 get_kernel_timer_id_by_callback( void (*cb)(void * data) )
{
    for( uint32_t i = 0 ; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        struct bx_delay_msg * pmsg = &bx_ke_env.dly_msg_hdl.hub[i];
        if( pmsg->cb == cb ) {
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
static __inline bx_err_t post( s32 src, s32 dst, u32 msg, u32 param0, u32 param1 )
{
    struct bx_msg * pmsg = get_unused_msg();
    if( !pmsg ) {
        return BX_ERR_FULL;
    }
    GLOBAL_DISABLE_IRQ();
    pmsg->src = src;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    bx_ke_env.kernel_is_busy = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
#if ( BX_ENABLE_LOG > 0 )
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
char default_name[]="err name";
char * get_service_name(s32 id)
{
    if(id>= bx_ke_env.service_hdl.count )
        return default_name;
    return bx_ke_env.service_hdl.hub[id].name;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_show_data( void )
{
    GLOBAL_DISABLE_IRQ();
    bx_logln("========================= kernel data start ============================");
    bx_logln("start:%08X",bx_ke_env.start);
    bx_logln("end:%08X",bx_ke_env.end);
    bx_logln("service %u:",bx_ke_env.service_hdl.count);
    if( bx_ke_env.service_hdl.count > 0 ) {
        bx_logln("--------------------------------------");
        bx_logln("id\tname");
        for( u32 i=0;i<bx_ke_env.service_hdl.count;i++ ) {
            bx_logln( "%u\t%s\t",get_service_name(i) );
        }
        bx_log("current service :%u\t",bx_ke_env.current_service_id);
        bx_logln("%s",get_service_name(bx_ke_env.current_service_id));
        
        bx_log("current msg source :%u\t",bx_ke_env.current_msg_source_id);
        bx_logln("%s",get_service_name(bx_ke_env.current_msg_source_id));
        bx_logln("\n\n");
    }
    
    
    bx_logln("subject %u:",bx_ke_env.subject_hub.count);
    if( bx_ke_env.subject_hub.count > 0 ) {
        bx_logln("--------------------------------------");
        bx_logln("source name\t\t dest name \t\t msg");
        for( u32 i=0;i<bx_ke_env.subject_hub.count;i++ ) {
            u32 src_id = bx_ke_env.subject_hub.hub[i].src;
            u32 dst_id = bx_ke_env.subject_hub.hub[i].dst;
            bx_log( "%s\t",get_service_name(src_id) );
            bx_log( "%s\t",get_service_name(dst_id) );
            bx_logln("%u",bx_ke_env.subject_hub.hub[i].msg);
        }
        bx_logln("\n\n");
    }
    
    bx_logln("msg %u:",bx_ke_env.msg_hdl.count);
    if( bx_ke_env.msg_hdl.count > 0 ) {
        bx_logln("--------------------------------------");
        bx_logln("source name\t\t dest name \t\t msg");
        for( u32 i=bx_ke_env.msg_hdl.start;i<bx_ke_env.msg_hdl.count;i++ ) {
            u32 src_id = bx_ke_env.msg_hdl.hub[i].src;
            u32 dst_id = bx_ke_env.msg_hdl.hub[i].dst;
            bx_log( "%s\t",get_service_name(src_id) );
            bx_log( "%s\t",get_service_name(dst_id) );
            bx_logln("%u",bx_ke_env.msg_hdl.hub[i].msg);
        }
        bx_logln("\n\n");
    }
    
    bx_logln("delay msg :");
    bx_logln("--------------------------------------");
    bx_logln("source\t\t dest\t\t msg\t period\t repeat");
    for( u32 i=0;i<BXKE_DELAY_MSG_CONFIG_MAX_COUNT;i++ ) {
        struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[i] );
        if( pmsg->used ) {
            bx_log( "%s\t",get_service_name(pmsg->src) );
            bx_log( "%s\t",get_service_name(pmsg->dst) );
            bx_log("%u\t",pmsg->msg);
            u16 tm_id = get_kernel_timer_id( pmsg->dst, pmsg->msg );
            struct kernel_timer_config * cfg = bx_kernel_timer_get_config(tm_id);
            bx_log("%ums\t",cfg->time * 10);
            bx_logln("%d\t",cfg->repeat);
        }
    }
    bx_logln("========================= kernel data end ============================");
    bx_logln("\n\n");
    GLOBAL_ENABLE_IRQ();
}
#endif
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_init( void )
{
    memset( &bx_ke_env, 0, sizeof( struct bx_kernel_data ) );
    bx_ke_env.start = KERNEL_DATA_START;
    bx_ke_env.end = KERNEL_DATA_END;
    bx_kernel_timer_init();
    
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
        if( bx_ke_env.start != KERNEL_DATA_START || bx_ke_env.end != KERNEL_DATA_END ) {
            bx_logln("mem overflow , kernel data err");
            //bx_err(  );
            while(1);
        }
        struct bx_msg * pmsg = get_next_msg();

    #if ( BX_USE_WDT > 0 )
        BX_MODIFY_REG( BX_WDT->CR, WDT_CR_VAL, 0X76 );
    #endif

        if( pmsg == NULL ) {
            bx_ke_env.kernel_is_busy = false;
            // do something to notify app
            return;
        }
        
        msg_handle_f func = bx_ke_env.service_hdl.hub[pmsg->dst].msg_handle_func ;
        bx_ke_env.current_service_id = pmsg->dst;
        bx_ke_env.current_msg_source_id = pmsg->src;
        
        if( func == NULL ) {
            // do something to notify app
            continue;
        }
        bx_err_t err = func( pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        if( err == BX_OK ) {
            // do something to notify app
        } else if ( err == BX_ERR_BUSY ) {
            //把消息再扔进队列
            post( pmsg->src,pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        } else {
            // do something to notify app
            bx_logln("excute err:%u,%u,%u",pmsg->dst, pmsg->msg,err);
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_post( s32 dst, u32 msg, u32 param0, u32 param1 )
{
    return post(bx_ke_env.current_service_id,dst,msg,param0,param1);
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_defer( s32 dst, u32 msg, u32 param0, u32 param1, u32 time )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( time, 1 );
    if( tm_id == 0 ) {
        bx_logln("bx_defer BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = bx_ke_env.current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    pmsg->cb = 0;
    pmsg->data = 0;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   : period unit ms
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_repeat( s32 dst, u32 msg, u32 param0, u32 param1, u32 period )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( period, BX_FOREVER );
    if( tm_id == 0 ) {
        bx_logln("bx_repeat BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = bx_ke_env.current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_repeatn( s32 dst, u32 msg, u32 param0, u32 param1, u32 period, s32 num )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( period, num );
    if( tm_id == 0 ) {
        bx_logln("bx_repeatn BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = bx_ke_env.current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_cancel( s32 dst, u32 msg )
{
    u16 id = get_kernel_timer_id( dst, msg );
    if( id == 0 ) {
        return ;
    }
    bx_kernel_timer_stop( id );
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );
    GLOBAL_DISABLE_IRQ();
    pmsg->used = false;
    GLOBAL_ENABLE_IRQ();
    return ;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bx_register( struct bx_service * p_svc )
{
    if( bx_ke_env.service_hdl.count < BXKE_SERVICE_CONFIG_MAX_COUNT ) {
        GLOBAL_DISABLE_IRQ();
        u32 index = bx_ke_env.service_hdl.count;
        bx_ke_env.service_hdl.hub[index].prop_set_func = p_svc->prop_set_func;
        bx_ke_env.service_hdl.hub[index].prop_get_func = p_svc->prop_get_func;
        bx_ke_env.service_hdl.hub[index].msg_handle_func = p_svc->msg_handle_func;
        bx_ke_env.service_hdl.hub[index].name = p_svc->name;
        bx_ke_env.service_hdl.count++;
        GLOBAL_ENABLE_IRQ();
        return index;
    } else {
        bx_logln("bx_register BX_ERR_NOMEM");
        return -1;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_subscibe( s32 dst, u32 msg, u32 param0, u32 param1 )
{
    if( bx_ke_env.subject_hub.count >= BX_SUBSCIBE_MAX_COUNT ) {
        return false;
    }
    
    u32 count = bx_ke_env.subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( bx_ke_env.subject_hub.hub[i].src != bx_ke_env.current_service_id ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].dst != dst ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].msg == msg ) {
            return BX_OK;
        }
    }
    
    GLOBAL_DISABLE_IRQ();

    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].src = bx_ke_env.current_service_id;
    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].dst = dst;
    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].msg = msg;
    bx_ke_env.subject_hub.count++;

    GLOBAL_ENABLE_IRQ();

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_subscibeex( s32 src, s32 dst, u32 msg )
{
    if( bx_ke_env.subject_hub.count >= BX_SUBSCIBE_MAX_COUNT ) {
        return false;
    }
    
    u32 count = bx_ke_env.subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( bx_ke_env.subject_hub.hub[i].src != src ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].dst != dst ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].msg == msg ) {
            return BX_OK;
        }
    }
    
    GLOBAL_DISABLE_IRQ();

    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].src = src;
    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].dst = dst;
    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].msg = msg;
    bx_ke_env.subject_hub.count++;

    GLOBAL_ENABLE_IRQ();

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_public( s32 src, u32 msg, u32 param0, u32 param1 )
{
    bx_err_t err;
    u32 count = bx_ke_env.subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( bx_ke_env.subject_hub.hub[i].dst != src ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].msg == msg ) {
            err = post( src, bx_ke_env.subject_hub.hub[i].src, msg, param0, param1 );
            if( err != BX_OK ) {
                return err;
            }
        }
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_set( s32 dst, u32 prop, u32 param0, u32 param1 )
{
    if( (u32)dst > bx_ke_env.service_hdl.count || bx_ke_env.service_hdl.hub[dst].prop_set_func == NULL ) {
        return BX_ERR_NOTSUP;
    }
    GLOBAL_DISABLE_IRQ();
    bx_err_t ret = bx_ke_env.service_hdl.hub[dst].prop_set_func(dst, prop, param0, param1 );
    GLOBAL_ENABLE_IRQ();
    return ret;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_get( s32 dst, u32 prop, u32 param0, u32 param1 )
{
    if( (u32)dst > bx_ke_env.service_hdl.count || bx_ke_env.service_hdl.hub[dst].prop_get_func == NULL ) {
        return false;
    }
    GLOBAL_DISABLE_IRQ();
    bx_err_t ret = bx_ke_env.service_hdl.hub[dst].prop_get_func(dst, prop, param0, param1 );
    GLOBAL_ENABLE_IRQ();
    return ret;
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
    if( (u32)dst > bx_ke_env.service_hdl.count || bx_ke_env.service_hdl.hub[dst].msg_handle_func == NULL ) {
        return BX_ERR_EMPTY;
    }
    return bx_ke_env.service_hdl.hub[dst].msg_handle_func(dst, msg, param0, param1 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_err(s32 svc, u32 msg,u32 param0,u32 param1, bx_err_t err )
{
    // 当前服务的 msg 出现错误 bx_ke_env.current_service_id
    //存log
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_dwork( void (*cb)(void *),void * data,u32 time, s32 num )
{
    u16 tm_id = get_kernel_timer_id_by_callback( cb );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( time, num );
    if( tm_id == 0 ) {
        bx_logln("bx_dwork ERR_NOMEM or INVAL");
        return BX_ERROR;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = -1;
    pmsg->dst = -1;
    pmsg->msg = 0;
    pmsg->param0 = 0;
    pmsg->param1 = 0;
    pmsg->cb = cb;
    pmsg->data = data;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_dwork_cancel( void (*func)(void *) )
{
    u16 id = get_kernel_timer_id_by_callback( func );
    if( id == 0 ) {
        return ;
    }
    bx_kernel_timer_stop( id );
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );
    GLOBAL_DISABLE_IRQ();
    pmsg->used = false;
    GLOBAL_ENABLE_IRQ();
    return ;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u32 bx_service_get_count( void )
{
    return bx_ke_env.service_hdl.count;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
struct bx_service * bx_get_service( s32 id )
{
    if( id >= bx_ke_env.service_hdl.count || id < 0   ) {
        return NULL;
    }
    return &bx_ke_env.service_hdl.hub[id];
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bx_msg_source( void )
{
    return bx_ke_env.current_msg_source_id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_ke_busy(void)
{
    return bx_ke_env.kernel_is_busy;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_timer_timeout_callback( u16 id, bool end_of_repeat )
{
    //bx_logln( "id:%X %X", id, BKT_ID_TO_INDEX(id) );

    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    //bx_logln("%08X:%08x",pmsg->dst,pmsg->msg);
    if( pmsg->used ) {
        if( end_of_repeat ) {
            pmsg->used = false;
        }
        if( pmsg->cb != NULL && pmsg->dst == -1 && pmsg->src == -1) {
            pmsg->cb( pmsg->data );
        }else if( pmsg->cb == NULL && pmsg->dst != -1 && pmsg->src != -1 ) {
            post( pmsg->src,pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        }else{
            bx_err( pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1,BX_ERR_INVAL );
        }
    }
}
/*=========================== end of import function =========================*/

/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



