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
#include "bx_software_timer.h"
#include "string.h"

#include "shell_api.h"

/* private define ------------------------------------------------------------*/


/* private typedef -----------------------------------------------------------*/
typedef struct {
    uint16_t timer_id;
    bool     periodic;
    uint32_t delay;
} sftim_cfg_t;

/* private function prototypes -----------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static sftim_cfg_t s_cfg_ary[BX_SOFTWARE_TIMER_CONFIG_COUNT_MAX] = { 0 };

static struct ke_msg_handler s_msg_ary[BX_SOFTWARE_TIMER_CONFIG_COUNT_MAX + 1] = { 0 };

static struct ke_state_handler s_timer_handler = KE_STATE_HANDLER( s_msg_ary );

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
static int prv_software_timer_handler( ke_msg_id_t const msgid, void const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    for( uint32_t i = 0; i < sizeof( s_cfg_ary ); i++ ) {
        if( s_cfg_ary[i].timer_id == msgid ) {
            if( s_cfg_ary[i].periodic ){
                ke_timer_set( msgid, TASK_SOFTWARE_TIMER, s_cfg_ary[i].delay );
            }
        }
    }
    sftim_timeout_callback( msgid );
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
    for( uint32_t i = 0; i < sizeof( s_cfg_ary ); i++ ) {
        if( s_cfg_ary[i].timer_id != 0 ) {
            if( !ke_timer_active( s_cfg_ary[i].timer_id, TASK_SOFTWARE_TIMER ) ) {
                ke_timer_set( s_cfg_ary[i].timer_id, TASK_SOFTWARE_TIMER, s_cfg_ary[i].delay );
            }
        }
    }
    return ( KE_MSG_CONSUMED );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint16_t prv_get_free_msg_id( uint8_t msg_ary_index )
{
   return SFTIM_MSG_TIM_FIRST + msg_ary_index - 1;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bool prv_set_timer_cfg( uint16_t timer_id, bool periodic, uint32_t delay_10ms )
{
    for( uint32_t i = 0; i < sizeof( s_cfg_ary ); i++ ) {
        if( s_cfg_ary[i].timer_id == 0 ) {
            s_cfg_ary[i].timer_id = timer_id;
            s_cfg_ary[i].periodic = periodic;
            s_cfg_ary[i].delay = delay_10ms;
            return true;
        }
    }
    return false;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sftim_init( void )
{
    static struct ke_task_desc s_task_desc = {NULL, &s_timer_handler, NULL, 1, 1};
    uint8_t state = ke_task_create( TASK_SOFTWARE_TIMER, &s_task_desc );
    if( state != KE_TASK_OK ) {
        printf( "ke_task_create FAIL %x\r\n", state );
    }

    s_msg_ary[0].id = SFTIM_MSG_CREAT_TIMER;
    s_msg_ary[0].func = prv_creat_timer;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :   succeed return timer_id
                fail return 0xFFFF
-----------------------------------------------------------------------------*/
uint16_t sftim_creat( uint32_t time_10ms, bool periodic )
{
    __disable_irq();
    uint16_t timer_id = 0xFFFF;

    for( uint32_t i = 0; i < sizeof( s_msg_ary ); i++ ) {
        if( s_msg_ary[i].id == 0 ) {
            timer_id = prv_get_free_msg_id(i);
            s_msg_ary[i].id = timer_id;
            s_msg_ary[i].func = prv_software_timer_handler;
            break;
        }
    }
    if( prv_set_timer_cfg( timer_id, periodic, time_10ms ) ) {
        ke_msg_send_basic( SFTIM_MSG_CREAT_TIMER, TASK_SOFTWARE_TIMER, TASK_SOFTWARE_TIMER );
    } else {
        timer_id = 0xFFFF;
    }
    __enable_irq();
    return timer_id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sftim_stop( uint16_t timer_id )
{
    __disable_irq();
    ke_timer_clear(timer_id,TASK_SOFTWARE_TIMER);
    __enable_irq();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool sftim_is_active( uint16_t timer_id )
{
    return ke_timer_active(timer_id,TASK_SOFTWARE_TIMER);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_sftim_cmd_handler( char argc, char * argv )
{
    static uint16_t s_id = 0;
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxs_printfln( "useage: help [options]" );
            bxs_printfln( "options:" );
            bxs_printfln( "\t -c \t: creat " );
            bxs_printfln( "\t -s \t: stop all " );
        } else if ( !strcmp( "-c", &argv[argv[1]] ) ) {
            s_id = sftim_creat(100,1);
        } else if ( !strcmp( "-s", &argv[argv[1]] ) ) {
            sftim_stop(s_id);
        } else {
            bxs_option_unsupport( &argv[argv[0]] );
        }
    } else {
        bxs_arg_err( &argv[argv[0]] );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sftim_add_shell_cmd(void)
{
    bxs_add_cmd("sfitm",prv_sftim_cmd_handler,"software timer test");
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__weak void sftim_timeout_callback( uint16_t timer_id )
{
    bxs_printfln( "timer_id:%d %x", timer_id, timer_id );
    
    //ke_timer_set( timer_id, TASK_SOFTWARE_TIMER, 100 );
}
/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

