/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author : BLUEX OD Team
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ...
  *
  ******************************************************************************
  */
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "ke_task.h"
#include "ke_timer.h"
#include "bx_kernel_timer.h"
#include "bx_kernel.h"
#include "bx_dbg.h"

/* private define ------------------------------------------------------------*/


/* private typedef -----------------------------------------------------------*/

/* private function prototypes -----------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static struct kernel_timer_config cfg_hub[BXKE_DELAY_MSG_CONFIG_MAX_COUNT] = { 0 };

//有一个消息用于创建定时器
static struct ke_msg_handler msg_hub[BXKE_DELAY_MSG_CONFIG_MAX_COUNT + 1] = { 0 };
static struct ke_state_handler handler = KE_STATE_HANDLER( msg_hub );

/* private macros ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* import function prototypes ------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int prv_timer_handler( ke_msg_id_t const msgid, void const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    bool end_of_repeat = false;
    u32 index = bx_kernel_timer_id_to_array_index(msgid);

    if( cfg_hub[index].repeat > 0 || cfg_hub[index].repeat == BX_FOREVER ) {
        ke_timer_set( msgid, TASK_BX_KERNEL_TIMER, cfg_hub[index].time );
        if( cfg_hub[index].repeat > 0) {
            cfg_hub[index].repeat--;
        }
    } else if( cfg_hub[index].repeat == 0 ){
        cfg_hub[index].id = 0;
        end_of_repeat = true;
    } else {
        bx_logln("kernel err ");
        while(1);
    }

    bx_kernel_timer_timeout_callback( msgid,end_of_repeat);
    
    return ( KE_MSG_CONSUMED );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int prv_creat_timer( ke_msg_id_t const msgid, void const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    for( u32 i = 0; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        if( cfg_hub[i].id != 0 ) {
            if( !ke_timer_active( cfg_hub[i].id, TASK_BX_KERNEL_TIMER ) ) {
                ke_timer_set( cfg_hub[i].id, TASK_BX_KERNEL_TIMER, cfg_hub[i].time );
            }
        }
    }
    return ( KE_MSG_CONSUMED );
}

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_timer_init( void )
{
    static struct ke_task_desc task_desc = {NULL, &handler, NULL, 1, 1};
    uint8_t state = ke_task_create( TASK_BX_KERNEL_TIMER, &task_desc );
    if( state != KE_TASK_OK ) {
        bx_logln( "ke_task_create false %x", state );
    }

    msg_hub[0].id = BKT_MSG_CREAT_TIMER;
    msg_hub[0].func = prv_creat_timer;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :   time unit ms
 * @retval  :   succeed return timer_id
                fail return 0
-----------------------------------------------------------------------------*/
u16 bx_kernel_timer_creat( u32 time, s32 repeat )
{
    if( repeat != BX_FOREVER ) {
        if( repeat <= 0 ){
            return 0;
        }else {
            // repeat > 0
            repeat -= 1;
        }
    }else {
        // repeat == BX_FOREVER
        // do nothing
    }
        
    GLOBAL_DISABLE_IRQ();
    
    u16 timer_id = 0;

    for( u32 i = 0; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        if( cfg_hub[i].id == 0 ) {
            timer_id = BKT_INDEX_TO_ID(i);
            
            cfg_hub[i].id = timer_id;
            cfg_hub[i].repeat = repeat;
            //会损失精度 （ke_timer的单位为10ms）
            cfg_hub[i].time = time/10;
            
            msg_hub[i+1].id = timer_id;
            msg_hub[i+1].func = prv_timer_handler;
            
            ke_msg_send_basic( BKT_MSG_CREAT_TIMER, TASK_BX_KERNEL_TIMER, TASK_BX_KERNEL_TIMER );
            break;
        }
    }
    
    GLOBAL_ENABLE_IRQ();
    if( timer_id == 0 ) {
        bx_logln("creat fail");
    }
    return timer_id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_timer_stop( u16 id )
{
    u32 index = bx_kernel_timer_id_to_array_index(id);
    // 标记为未使用
    cfg_hub[index].id = 0;
    ke_timer_clear(id,TASK_BX_KERNEL_TIMER);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_kernel_timer_is_active( u16 timer_id )
{
    return ke_timer_active(timer_id,TASK_BX_KERNEL_TIMER);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
struct kernel_timer_config * bx_kernel_timer_get_config(u16 id)
{
    u32 index = bx_kernel_timer_id_to_array_index(id);
    return &cfg_hub[index];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_timer_stop_all(void)
{
    for( u32 i = 0; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        if( cfg_hub[i].id != 0 ) {
            bx_kernel_timer_stop(cfg_hub[i].id);
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u32 bx_kernel_timer_id_to_array_index( u16 id )
{
    u32 index = BKT_ID_TO_INDEX(id);
    //for testing
    if( index >= BXKE_DELAY_MSG_CONFIG_MAX_COUNT ) {
        bx_logln("kernel timer err");
        while(1);
    }
    return index;
}
#if ( BX_KERNEL_TIMER_TEST > 0 )
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_sftim_cmd_handler( char argc, char * argv )
{
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bx_logln( "useage: help [options]" );
            bx_logln( "options:" );
            bx_logln( "\t -c1 \t: creat , time = 10S" );
            bx_logln( "\t -c2 \t: creat , time = 5S " );
            bx_logln( "\t -c3 \t: creat , time = 1S " );
            bx_logln( "\t -c4 \t: creat , time = 2S no-repeat " );
            
            bx_logln( "\t -s \t: stop all " );
        } else if ( !strcmp( "-c1", &argv[argv[1]] ) ) {
            bx_kernel_timer_creat(10000,BX_FOREVER);
        } else if ( !strcmp( "-c2", &argv[argv[1]] ) ) {
            bx_kernel_timer_creat(5000,BX_FOREVER);
        } else if ( !strcmp( "-c3", &argv[argv[1]] ) ) {
            bx_kernel_timer_creat(1000,1);
        } else if ( !strcmp( "-c4", &argv[argv[1]] ) ) {
            bx_kernel_timer_creat(2000,1);
         } else if ( !strcmp( "-s", &argv[argv[1]] ) ) {
            bx_kernel_timer_stop_all();
        } else {
            bxsh_option_unsupport( &argv[argv[0]] );
        }
    } else {
        bxsh_arg_err( &argv[argv[0]] );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_timer_add_shell_cmd(void)
{
    bxsh_add_cmd("ktim",prv_sftim_cmd_handler,"kernel timer test");
}
#endif /* BX_KERNEL_TIMER_TEST > 0 */
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__weak void bx_kernel_timer_timeout_callback( u16 timer_id ,bool end_of_repeat)
{
    bx_logln( "timer_id:%X %X", timer_id, BKT_ID_TO_INDEX(timer_id) );
    
    //ke_timer_set( timer_id, TASK_BX_KERNEL_TIMER, 100 );
}
/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

