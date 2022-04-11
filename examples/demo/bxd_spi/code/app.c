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
#include "bx_pm.h"
#include "plf.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/



/*============================= private function =============================*/
uint8_t iic_data[3] = {0x66, 0x02, 0x04};
uint8_t iic_readbuf[3] = {0x01, 0x02, 0x03};
uint8_t lis3_data[2] = {0x8f, 0x00};

uint8_t lis3_rx_data[2] = {0x01, 0x02};
uint8_t lis3_rx_data2[2] = {0x01, 0x02};


void LIS3DSH_write_reg( int reg, int data )
{
    lis3_data[0] = SET_WRITE_SINGLE_CMD( reg );
    lis3_data[1] = data;


    bxd_spim_write( BX_SPIM0, ( u8 * )lis3_data, 2 );
}

int LIS3DSH_read_reg( int reg )
{
    lis3_data[0] = SET_READ_SINGLE_CMD( reg );
    lis3_data[1] = 0xff;

    bxd_spim_write( BX_SPIM0, ( u8 * )lis3_data, 1 );
    bxd_spim_read( BX_SPIM0, ( u8 * )lis3_rx_data, 2 );

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
    uint8_t device_id;
    int intRegValue;

    bx_pm_lock( BX_PM_SPIM );
    bxd_spim_open( BX_SPIM0 );
    bxd_spim_set_speed( BX_SPIM0, 100000 );
    bxd_spim_set_data_bit( BX_SPIM0, BX_SPI_DATA_BIT_8B );
    bxd_spim_use_cs( BX_SPIM0, 0x01 );
    bxd_spim_set_cs1_pin( BX_SPIM0, 3 );

    device_id = LIS3DSH_read_reg( ADD_REG_WHO_AM_I );
    bx_logln( "device_id:%d\r\n", device_id );
    if( device_id == UC_WHO_AM_I_DEFAULT_VALUE ) {
        bx_logln( "device_id:%d\r\n", device_id );
        LIS3DSH_write_reg( ADD_REG_CTRL_4, UC_ADD_REG_CTRL_4_CFG_VALUE );
        intRegValue = LIS3DSH_read_reg( ADD_REG_CTRL_4 );
        if( intRegValue != UC_ADD_REG_CTRL_4_CFG_VALUE ) {
            bx_logln( "intRegValue is %d\r\n", intRegValue );
        }
        bx_dwork( read_lis3dsh, NULL, 2000, BX_FOREVER );
    } else {
        bx_logln( "device get failed\r\n" );
    }
}

void read_lis3dsh( void * arg )
{
    int intValueMgX, intValueMgY, intValueMgZ;
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
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



