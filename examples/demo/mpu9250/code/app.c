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
#include "ble.h"
#include "bx_pm.h"
#include "bxd_iic.h"
#include "mpu9250_iic.h"
#include "plf.h"
#include "bxd_gpio.h"
#include "i2c_bus.h"
#include "sc7a20.h"
//#include "mpu_dmp_useapi.h"

#include "app_dis.h"
#include "mpu9250.h"
/* private define ------------------------------------------------------------*/

uint32_t m_len_sent;
uint32_t m_cnt_10ms;
uint8_t m_data_array[250];

/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );

struct bx_spim_txrx_config * spim_data;

typedef struct {
    uint8_t mode : 4;
    uint8_t resolution : 1;
} mpu_magn_config_t;
typedef struct {
    uint8_t clkout_en       : 1; // When this bit is equal to 1, a reference clock output is provided at the CLKOUT pin. When this bit is equal to 0, the clock output is disabled. For further information regarding CLKOUT, please refer to the MPU-9150 Product Specification document.
    uint8_t i2c_bypass_en   : 1; // When this bit is equal to 1 and I2C_MST_EN (Register 106 bit[5]) is equal to 0, the host application processor will be able to directly access the auxiliary I2C bus of the MPU-9150. When this bit is equal to 0, the host application processor will not be able to directly access the auxiliary I2C bus of the MPU-9150 regardless of the state of I2C_MST_EN (Register 106 bit[5]).
    uint8_t fsync_int_en    : 1; // When equal to 0, this bit disables the FSYNC pin from causing an interrupt to the host processor. When equal to 1, this bit enables the FSYNC pin to be used as an interrupt to the host processor.
    uint8_t fsync_int_level : 1; // When this bit is equal to 0, the logic level for the FSYNC pin (when used as an interrupt to the host processor) is active high. When this bit is equal to 1, the logic level for the FSYNC pin (when used as an interrupt to the host processor) is active low.
    uint8_t int_rd_clear    : 1; // When this bit is equal to 0, interrupt status bits are cleared only by reading INT_STATUS (Register 58). When this bit is equal to 1, interrupt status bits are cleared on any read operation.
    uint8_t latch_int_en    : 1; // When this bit is equal to 0, the INT pin emits a 50us long pulse. When this bit is equal to 1, the INT pin is held high until the interrupt is cleared.
    uint8_t int_open        : 1; // When this bit is equal to 0, the INT pin is configured as push-pull. When this bit is equal to 1, the INT pin is configured as open drain.
    uint8_t int_level       : 1; // When this bit is equal to 0, the logic level for the INT pin is active high. When this bit is equal to 1, the logic level for the INT pin is active low.
} mpu_int_pin_cfg_t;
/* private variables ---------------------------------------------------------*/
uint8_t user_scan_rsp_data[] = {
    0x08,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    'B', 'X', '-', 'S', 'D', 'K', '3'
};

// GAP - Advertisement data (max size = (28) bytes)
uint8_t user_adv_data[] = {
    0x08,// length of this data
    GAP_AD_TYPE_SHORTENED_NAME,//type of this data
    'B', 'X', '-', 'S', 'D', 'K', '3'
};


static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    ( appm_add_svc_func_t )app_dis_add_dis
};

extern s32 user_service_id;
/* exported variables --------------------------------------------------------*/
uint8_t iic_data[3] = {0x22, 0x02, 0x04};
uint8_t iic_readbuf[3] = {0x01, 0x02, 0x03};
uint8_t iic_readbuf1[3] = {0x01, 0x02, 0x03};
uint8_t lis3_data[2] = {0x8f, 0x00};

uint8_t lis3_rx_data[2] = {0x01, 0x02};
uint8_t lis3_rx_data2[2] = {0x01, 0x02};


/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_set_dev_cfg( struct gapm_set_dev_config_cmd * cmd )
{
    cmd->operation = GAPM_SET_DEV_CONFIG;
    cmd->role      = GAP_ROLE_PERIPHERAL;
    cmd->pairing_mode = GAPM_PAIRING_LEGACY;
    cmd->sugg_max_tx_octets = BLE_MAX_OCTETS;
    cmd->sugg_max_tx_time   = BLE_MAX_TIME;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool app_add_svc( void )
{
    bool more_svc = false;
    if ( app_env.next_svc != sizeof( appm_add_svc_func_list ) / sizeof( appm_add_svc_func_t ) ) {
        appm_add_svc_func_list[app_env.next_svc]();
        app_env.next_svc++;
        more_svc = true;
    }
    return more_svc;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_init( void )
{
    app_dis_init();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_ready( void )
{
    struct gapm_start_advertise_cmd adv_data;
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

    ble_advertising_start( &adv_data );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_disconnect( void )
{
    struct gapm_start_advertise_cmd adv_data;
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

    ble_advertising_start( &adv_data );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    /*-----------iic----------------*/
    //设置按键中断来CLOSE iic
//    bx_pm_lock( BX_PM_GPIO );
//    bxd_gpio_open( BX_GPIOA );
////    bx_drv_gpio_set_mode( BX_GPIOA, 15, BX_GPIO_MODE_INPUT );
////    bx_drv_gpio_set_mode( BX_GPIOA, 15, BX_GPIO_MODE_IT_FALLING );
////    bx_drv_gpio_set_mode( BX_GPIOA, 17, BX_GPIO_MODE_INPUT );
////    bx_drv_gpio_set_mode( BX_GPIOA, 17, BX_GPIO_MODE_IT_FALLING );

//    bxd_gpio_set_mode( BX_GPIOA, 5, BX_GPIO_MODE_OUTPUT );
//    bxd_gpio_write( BX_GPIOA, 5, 1 );

//    //初始dmp
//    mpu_dmp_init();
    //初始化iic
    IIC_Init();
//    i2c_bus_init();
//    BX_DELAY_US(100000);
    bx_logln( "iic init finish\r\n" );

//    sc7a20_readid();

//    //初始化MPU9250
//    uint8_t reset_value = 7;
//    bx_drv_iic_write( BX_IIC0, 0xd1, 0x86, ( uint8_t * )&reset_value, 3 ); //复位gyro,accelerometer temperature sensor
//    bx_drv_iic_write( BX_IIC0, 0xd1, 0x6B, ( uint8_t * )0x00, 3 ); //使用内部20MHz晶振
//    // Enable magnetometer使能磁力计
//    mpu_magn_config_t  magnetometer_config;
//    magnetometer_config.mode = SINGLE_MEASUREMENT_MODE;
//    magnetometer_config.resolution = 1;
//    //先读出INT Pin/Bypass寄存器的值
//    mpu_int_pin_cfg_t bypass_config;
//    bx_drv_iic_read( BX_IIC0, 0xd1, 0x37, ( uint8_t * )&bypass_config, 1 );
//    //修改bypass_en位为1
//    bypass_config.i2c_bypass_en = 1;
//    //修改后再写回INT Pin/Bypass 寄存器
//    bx_drv_iic_write( BX_IIC0, 0xd1, 0x37, ( uint8_t * )&bypass_config, 3 );
//    //写INT Pin / Bypass
//    bx_drv_iic_write( BX_IIC0, 0x19, 0x0A, ( uint8_t * )&magnetometer_config, 3 );

//    //初始dmp
//    mpu_dmp_init();
//    MPU9250_Init();
    bxd_iic_read( BX_IIC0, 0xd1, 0x75, iic_readbuf, 1 ); //读取MPU9250的设备ID
//      i2c_bus_read(0xd1,0x75,iic_readbuf,1);
//    bxd_iic_read( BX_IIC0, 0x19, 0x00, iic_readbuf1, 3 ); //读取AK8963的设备ID
//    bxd_iic_write( BX_IIC0, 0x19, 0x0A, AK8963_data, 3 ); //AK8963每次读完以后都需要重新设置为单次测量模式，否则数据不会更新
    if( iic_readbuf[0] == MPU9250_WHO_AM_I_DEFAULT_VALUE  ) {
        bx_log( "A&G device ID=%02x\r\n", iic_readbuf[0] ); //MPU9250的设备ID
        if( iic_readbuf1[0] == AK8963_WHO_AM_I_DEFAULT_VALUE ) {
            bx_log( "M device ID=%02x\r\n", iic_readbuf1[0] );  //AK8963的设备ID
        }

        bxd_iic_write( BX_IIC0, 0xd1, I2C_SLV0_EN, iic_data, 3 );
        bxd_iic_read( BX_IIC0, 0xd1, I2C_SLV0_EN, iic_readbuf, 3 );
        if( iic_readbuf[0] == 0x22 ) {
            bx_log( "set success\r\n" );
            while( true ) {
                //三轴陀螺仪传感器数据读取
//                bx_log( "Gyroscope Data:\r\n" );
//                MPU_Get_Gyroscope( &gx, &gy, &gz );
//                bx_log( "GYRO_XOUT=%d\r\n", gx );
//                bx_log( "GYRO_YOUT=%d\r\n", gy );
//                bx_log( "GYRO_ZOUT=%d\r\n", gz );
//                //三轴加速度传感器数据读取输出
//                bx_log( "Accelerometer Data:\r\n" );
//                MPU_Get_Accelerometer( &ax, &ay, &az );
//                bx_log( "ACCEL_XOUT=%d\r\n", ax );
//                bx_log( "ACCEL_YOUT=%d\r\n", ay );
//                bx_log( "ACCEL_ZOUT=%d\r\n", az );

//                //AK8963三轴传感器磁力计数据读取
//                bx_log( "MagValue:\r\n" );
//                MPU_Get_Magnetometer( &mx, &my, &mz );
//                bx_log( "AK8963_Mag_XOUT=%d\r\n", mx );
//                bx_log( "AK8963_Mag_YOUT=%d\r\n", my );
//                bx_log( "AK8963_Mag_ZOUT=%d\r\n", mz );

//                //温度值读取
//                bx_log( "Temperature:\r\n" );
//                temp = MPU_Get_Temperature();
//                bx_log( "Temperature=%f\r\n", temp );
//                  extern void mpu9250_Start(void);
                mpu9250_Start();

//                //姿态角获取
//                if(dmp_getdata(&pitch,&roll,&yaw)==0)
//                {
//                  bx_logln("pitch=%f\r\n",pitch);
//                  bx_logln("roll=%f\r\n",roll);
//                  bx_logln("yaw=%f\r\n",yaw);
//                }else
//                {
//                  bx_logln("dmp data get failed\r\n");
//                }

//                BX_DELAY_US( 1000000 );
            }
        } else {
            bx_log( "A&G device get failed\r\n" );
        }
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//u32 n = 0;
//void GPIO_IRQHandler( void )
//{
//    uint32_t int_stat = BX_GPIOA->IS;
//    BX_GPIOA->EOI |= int_stat;

//    n++;
//    if( n % 2 == 1 ) {
//        bxd_iic_close( BX_IIC0 );
//        bx_logln( "CLOSE IIC" );
//    } else {
//        bxd_iic_open( BX_IIC0 );
//        bx_logln( "OPEN IIC" );
//    }
//}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



