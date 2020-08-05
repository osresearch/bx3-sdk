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
#include "bx_config.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "bxfs.h"
#include "flash.h"
#include "nvds_typedef.h"
#include "bx_dbg.h"

/* private define ------------------------------------------------------------*/
#define NVDS_DIR_KEY        65534
#define BD_ADDR_OFFSET      0x2000

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
bxfs_dir_t nvds_dir;

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t nvds_init()
{
    bxfs_mkdir( &nvds_dir, ROOT_DIR, NVDS_DIR_KEY );
    return NVDS_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t nvds_get( uint8_t tag, nvds_tag_len_t * lengthPtr, uint8_t * buf )
{
    BX_ASSERT( tag );
    switch( tag ) {
        case NVDS_TAG_BD_ADDRESS: {
            if( *lengthPtr < NVDS_LEN_BD_ADDRESS ) {
                return NVDS_LENGTH_OUT_OF_RANGE;
            }
            *lengthPtr = NVDS_LEN_BD_ADDRESS;
            periph_err_t error = flash_multi_read( BD_ADDR_OFFSET, NVDS_LEN_BD_ADDRESS, buf );
			bool is_use_default_mac_addr = true;
			for(uint32_t i=0;i<NVDS_LEN_BD_ADDRESS;i++){
				if( buf[i]!=0xFF ){
					is_use_default_mac_addr = false;
					break;
				}
			}
			if( is_use_default_mac_addr ){
				uint8_t addr[] = BX_MAC_ADDR;
				memcpy(buf,addr,NVDS_LEN_BD_ADDRESS);
			}
            BX_ASSERT( error == PERIPH_NO_ERROR );
        }
        break;
        case NVDS_TAG_DEVICE_NAME:
            if( *lengthPtr < sizeof( BX_DEV_NAME ) ) {
                return NVDS_LENGTH_OUT_OF_RANGE;
            }
            //*lengthPtr = sizeof( BX_DEV_NAME );
            *lengthPtr = strlen( BX_DEV_NAME );
            memcpy(buf,BX_DEV_NAME,sizeof(BX_DEV_NAME));
            break;
        case NVDS_TAG_EXT_WAKEUP_TIME:
            if( *lengthPtr < NVDS_LEN_EXT_WAKEUP_TIME ) {
                return NVDS_LENGTH_OUT_OF_RANGE;
            }
            *lengthPtr = NVDS_LEN_EXT_WAKEUP_TIME;
            buf[0] = ( uint8_t )BLE_SOFT_WAKEUP_TIME;
            buf[1] = ( uint8_t )( BLE_SOFT_WAKEUP_TIME >> 8 );
            break;
        case NVDS_TAG_OSC_WAKEUP_TIME:
        case NVDS_TAG_RM_WAKEUP_TIME:
            if( *lengthPtr < sizeof( uint16_t ) ) {
                return NVDS_LENGTH_OUT_OF_RANGE;
            }
            *lengthPtr = NVDS_LEN_OSC_WAKEUP_TIME;
            buf[0] = ( uint8_t )BLE_WAKEUP_TIME;
            buf[1] = ( uint8_t )( BLE_WAKEUP_TIME >> 8 );
            break;
        case NVDS_TAG_SLEEP_ENABLE:
            buf[0] = DEEP_SLEEP_ENABLE;
            break;
        case NVDS_TAG_EXT_WAKEUP_ENABLE:
            buf[0] = EXT_WAKE_UP_ENABLE;
            break;
        case NVDS_TAG_LPCLK_DRIFT:
            if( *lengthPtr < NVDS_LEN_LPCLK_DRIFT ) {
                return NVDS_LENGTH_OUT_OF_RANGE;
            }
            *lengthPtr = NVDS_LEN_LPCLK_DRIFT;
            buf[0] = ( uint8_t )LPCLK_DRIFT_MAX;
            buf[1] = ( uint8_t )( LPCLK_DRIFT_MAX >> 8 );
            break;
        default: {
            uint16_t length = *lengthPtr;
            if( bxfs_read( nvds_dir, tag, buf, &length ) != BXFS_NO_ERROR ) {
                return NVDS_FAIL;
            }
            *lengthPtr = ( uint8_t )length;
        }
        break;
    }
    return NVDS_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t nvds_del( uint8_t tag )
{
    BX_ASSERT( tag );
    uint8_t retval = NVDS_OK;
    switch( tag ) {
        case NVDS_TAG_BD_ADDRESS:
        case NVDS_TAG_DEVICE_NAME:
        case NVDS_TAG_EXT_WAKEUP_TIME:
        case NVDS_TAG_OSC_WAKEUP_TIME:
        case NVDS_TAG_RM_WAKEUP_TIME:
        case NVDS_TAG_SLEEP_ENABLE:
        case NVDS_TAG_EXT_WAKEUP_ENABLE:
        case NVDS_TAG_LPCLK_DRIFT:
            retval = NVDS_PARAM_LOCKED;
            break;
        default:
            if( bxfs_del_record( nvds_dir, tag ) != BXFS_NO_ERROR ) {
                retval = NVDS_FAIL;
            }
            break;
    }
    return retval;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t nvds_put( uint8_t tag, nvds_tag_len_t length, uint8_t * buf )
{
    BX_ASSERT( tag );
    uint8_t retval = NVDS_OK;
    switch( tag ) {
        case NVDS_TAG_BD_ADDRESS:
        case NVDS_TAG_DEVICE_NAME:
        case NVDS_TAG_EXT_WAKEUP_TIME:
        case NVDS_TAG_OSC_WAKEUP_TIME:
        case NVDS_TAG_RM_WAKEUP_TIME:
        case NVDS_TAG_SLEEP_ENABLE:
        case NVDS_TAG_EXT_WAKEUP_ENABLE:
        case NVDS_TAG_LPCLK_DRIFT:
            retval = NVDS_PARAM_LOCKED;
            break;
        default:
            if( bxfs_write( nvds_dir, tag, buf, length ) != BXFS_NO_ERROR ) {
                retval = NVDS_FAIL;
            }
            break;
    }
    return retval;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void nvds_write_through( void )
{
    ( void )bxfs_write_through();
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

