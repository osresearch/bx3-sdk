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
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "rwip_config.h"
#include "rwip.h"
#include "patch.h"
#include "h4tl_custom.h"
#include "log.h"
#include "h4tl.h"
#ifdef METAL_APP_TWO_MCU_SLAVE
#include "mcu_slave.h"
#endif

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
#define H4TL_ENV                                        ( ( struct h4tl_env_tag * ) ( 0x0012f74c ) )
#define H4TL_RX_DONE                                    ( void * ) ( 0xb089 )
#define H4TL_READ_START_PATCH_ADDR                      0xb064
/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

void H4TL_READ_START_PATCH( void );

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void h4tl_read_start_patch( struct h4tl_env_tag * env )
{
    rwip_prevent_sleep_clear( RW_TL_RX_ONGOING );
    //TODO  enable ext int
#ifdef METAL_APP_TWO_MCU_SLAVE
    two_mcu_slave_unmask_exti();
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_h4tl_read_start_skip_patch()
{
    uint8_t patch_no;
    if( patch_alloc( &patch_no ) == false ) {
        BX_ASSERT( 0 );
    }
    uint32_t code = cal_patch_bl( H4TL_READ_START_PATCH_ADDR, ( uint32_t )H4TL_READ_START_PATCH - 1 );
    patch_entrance_exit_addr( patch_no, H4TL_READ_START_PATCH_ADDR, code );
    PATCH_ENABLE( patch_no );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void h4tl_read_start_2()
{
    struct h4tl_env_tag * env = &H4TL_ENV[H4TL_TYPE_AHI];
    //Initialize External Interface in reception mode state
    env->rx_state = H4TL_STATE_RX_START;

    //Set the External Interface environment to message type 1 byte reception
    env->ext_if->read( &( env->rx_buf[RX_TMP_BUFF_SIZE - 1] ), H4TL_LOGICAL_CHANNEL_LEN, ( rwip_eif_callback ) H4TL_RX_DONE, env );

#if DEEP_SLEEP
    {
#if ((BLE_HOST_PRESENT) && (!BLE_EMB_PRESENT))
        uint8_t i;
        bool prevent_sleep = false;

        // check if one of transport layer is not in IDLE mode
        for( i = 0 ; i < H4TL_TYPE_MAX ; i++ ) {
            if( h4tl_env[i].rx_state != H4TL_STATE_RX_START ) {
                prevent_sleep = true;
                break;
            }
        }

        if( !prevent_sleep )
#endif // ((BLE_HOST_PRESENT) && (!BLE_EMB_PRESENT))
        {
            // No HCI reception is ongoing, so allow going to sleep
            rwip_prevent_sleep_clear( RW_TL_RX_ONGOING );
        }
    }
#endif
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

