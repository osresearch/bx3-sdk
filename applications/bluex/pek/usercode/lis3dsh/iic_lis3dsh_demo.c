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

#include <lis3dsh_reg.h>
#include "iic_demo.h"
#include "bx_shell.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
static lis3dsh_data_t data;


/* private variables ---------------------------------------------------------*/



/*============================= private function =============================*/

static void platform_init( void )
{
    iic_init();
}

static int32_t platform_read( void * handle, uint8_t reg, uint8_t * bufp,
                              uint16_t len )
{
    iic_read_buff( LIS3DSH_I2C_ADD_L, reg, bufp, len );
    bxsh_log( "rd data 0x%02x -> %u\t:", reg,len );
    for( uint32_t i = 0; i < len; i++ ) {
        bxsh_log( "%02x ", bufp[i] );
    }
    bxsh_logln( "" );
    return 0;
}

static int32_t platform_write( void * handle, uint8_t reg, uint8_t * bufp,
                               uint16_t len )
{
    bxsh_log( "wr data 0x%02x -> %u\t:", reg,len );
    for( uint32_t i = 0; i < len; i++ ) {
        bxsh_log( "%02x ", bufp[i] );
    }
    bxsh_logln( "" );
    iic_write_buff( LIS3DSH_I2C_ADD_L, reg, bufp, len );
    return 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :基于LIS3DSH模块做的测试，其中vdd3.3V供电，CS脚通过跳线接VDD，即使用I2C通讯，
             SD0引脚通过跳线接GND，即I2C的slave地址接GND
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void lis3dsh_read_data_polling( void )
{
    lis3dsh_pin_int1_route_t int1_route;
    lis3dsh_all_sources_t all_sources;
    lis3dsh_bus_mode_t bus_mode;
    lis3dsh_status_var_t status;
    stmdev_ctx_t dev_ctx;
    lis3dsh_id_t id;
    lis3dsh_md_t md;

    /* Initialize mems driver interface */
    dev_ctx.write_reg = platform_write;
    dev_ctx.read_reg = platform_read;
    dev_ctx.handle = NULL;

    /* Init test platform */
    platform_init();

    /* Check device ID */
    lis3dsh_id_get( &dev_ctx, &id );
    if ( id.whoami != LIS3DSH_ID )
        while( 1 );

    /* Restore default configuration */
    lis3dsh_init_set( &dev_ctx, LIS3DSH_RESET );
//    do {
//        lis3dsh_status_get( &dev_ctx, &status );
//    } while ( status.sw_reset );

    /* Set bdu and if_inc racomended for driver usage */
    lis3dsh_init_set( &dev_ctx, LIS3DSH_DRV_RDY );

    /* Select bus interface */
    bus_mode = LIS3DSH_SEL_BY_HW;
    lis3dsh_bus_mode_set( &dev_ctx, &bus_mode );

    /* Set Output Data Rate */
    lis3dsh_mode_get( &dev_ctx, &md );
    md.fs =  LIS3DSH_4g;
    md.odr = LIS3DSH_25Hz;
    lis3dsh_mode_set( &dev_ctx, &md );

    /* Configure inerrupt pins */
    lis3dsh_pin_int1_route_get( &dev_ctx, &int1_route );
    int1_route.drdy_xl   = PROPERTY_DISABLE;
    lis3dsh_pin_int1_route_get( &dev_ctx, &int1_route );

    /* Read samples in polling mode (no int). */
    while( 1 ) {
        /* Read output only if new values are available */
        lis3dsh_all_sources_get( &dev_ctx, &all_sources );
        if ( all_sources.drdy_xl ) {

            lis3dsh_data_get( &dev_ctx, &md, &data );

            /* print sensor data  */
            bxsh_logln( "Acceleration [mg]:\t%4.2f\t%4.2f\t%4.2f",
                          data.xl.mg[0], data.xl.mg[1], data.xl.mg[2] );
            break;
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void local_lis3_cmd_handler( char argc, char * argv )
{
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: help [options]" );
            bxsh_logln( "options:" );
            bxsh_logln( "\t get \t: get data " );
        } else if ( !strcmp( "get", &argv[argv[1]] ) ) {
            lis3dsh_read_data_polling();
        } else {
            bxsh_option_unsupport( &argv[argv[0]] );
        }
    } else {
        bxsh_arg_err( &argv[argv[0]] );
    }
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void iic_lis3dsh_add_shell_cmd( void )
{
    bxsh_add_cmd( "lis3", local_lis3_cmd_handler, "lis3 test" );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
