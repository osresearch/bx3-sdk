/**
  ******************************************************************************
  * @file   :   main.c
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
#include "app.h"
#include "bxd_spim.h"
#include "bxs_spi.h"
#include "bx_pm.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
s32 user_service_id;

uint8_t iic_data[3] = {0x66, 0x02, 0x04};
uint8_t iic_readbuf[3] = {0x01, 0x02, 0x03};
uint8_t lis3_data[2] = {0x8f, 0x00};

uint8_t lis3_rx_data[2] = {0x01, 0x02};
uint8_t lis3_rx_data2[2] = {0x01, 0x02};


void LIS3DSH_write_reg( int reg, int data )
{
    lis3_data[0] = SET_WRITE_SINGLE_CMD( reg );
    lis3_data[1] = data;


    bx_call( bxs_spim0_id(), BXM_WRITE, ( uint32_t )lis3_data, 2 );

}

int LIS3DSH_read_reg( int reg )
{
    lis3_data[0] = SET_READ_SINGLE_CMD( reg );
    lis3_data[1] = 0xff;
    bx_call( bxs_spim0_id(), BXM_WRITE, ( uint32_t )lis3_data, 1 );
    bx_call( bxs_spim0_id(), BXM_READ, ( uint32_t )lis3_rx_data, 2 );

    return lis3_rx_data[1];

}

int twoComplToInt16( int twoComplValue )
{
    int int16Value = 0;
    /* conversion */
    if( twoComplValue > 32768 ) {
        int16Value = -( ( ( ~twoComplValue ) & 0xFFFF ) + 1 );
    } else {
        int16Value = twoComplValue;
    }

    return int16Value;

}


/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    user_service_id = bx_register( &svc );

    bxs_spim_register();

    uint8_t device_id;
    int intRegValue;

    bx_call( bxs_spim0_id(), BXM_OPEN, 0, 0 );
    bx_set( bxs_spim0_id(), BXP_SPEED, 100000, 0 );
    bx_set( bxs_spim0_id(), BXP_DATA_BIT, BX_SPI_DATA_BIT_8B, 0 );
    bx_set( bxs_spim0_id(), BXP_SPIM_USE_CS_NUM, 0x01, 0 );
    bx_set( bxs_spim0_id(), BXP_SPIM_CS1_PIN, 3, 0 );

    device_id = LIS3DSH_read_reg( ADD_REG_WHO_AM_I );
    bx_logln( "device_id:%d\r\n", device_id );
    if( device_id == UC_WHO_AM_I_DEFAULT_VALUE ) {
        bx_logln( "device_id:%d\r\n", device_id );
        LIS3DSH_write_reg( ADD_REG_CTRL_4, UC_ADD_REG_CTRL_4_CFG_VALUE );
        intRegValue = LIS3DSH_read_reg( ADD_REG_CTRL_4 );
        if( intRegValue != UC_ADD_REG_CTRL_4_CFG_VALUE ) {
            bx_logln( "intRegValue is %d\r\n", intRegValue );
        }
        bx_repeat( user_service_id, BXM_SPIM_SENSOR_TEST, 0, 0, 2000 );
    } else {
        bx_logln( "device get failed\r\n" );
    }

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 id, u32 msg, u32 param0, u32 param1 )
{
    int intValueMgX, intValueMgY, intValueMgZ;
    switch( msg ) {
        case BXM_SPIM_SENSOR_TEST:

            intValueMgX = ( ( LIS3DSH_read_reg( ADD_REG_OUT_X_H ) << 8 ) |   LIS3DSH_read_reg( ADD_REG_OUT_X_L ) );
            intValueMgY = ( ( LIS3DSH_read_reg( ADD_REG_OUT_Y_H ) << 8 ) | LIS3DSH_read_reg( ADD_REG_OUT_Y_L ) );
            intValueMgZ = ( ( LIS3DSH_read_reg( ADD_REG_OUT_Z_H ) << 8 ) | LIS3DSH_read_reg( ADD_REG_OUT_Z_L ) );

            intValueMgX = twoComplToInt16( intValueMgX );
            intValueMgX = intValueMgX * SENS_2G_RANGE_MG_PER_DIGIT;

            intValueMgY = twoComplToInt16( intValueMgY );
            intValueMgY = intValueMgY * SENS_2G_RANGE_MG_PER_DIGIT;

            intValueMgZ = twoComplToInt16( intValueMgZ );
            intValueMgZ = intValueMgZ * SENS_2G_RANGE_MG_PER_DIGIT;
            bx_log( "X=%6d Y=%6d Z=%6d \r\n", intValueMgX, intValueMgY, intValueMgZ );
            break;

        default:
            break;
    }
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



