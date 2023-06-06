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
#include "bx_pm.h"
#include "bxd_iic.h"
#include "plf.h"
/* private define ------------------------------------------------------------*/
#define IIC_SLAVE_SCL_PIN       2
#define IIC_SLAVE_SDA_PIN       15
#define IIC_SLAVE_ADDR          0x30
#define IIC_READ_LENGTH_MAX     32
/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
uint8_t iic_slave_read_buf[IIC_READ_LENGTH_MAX] = {0};
uint16_t iic_slave_read_len = IIC_READ_LENGTH_MAX;


/*============================= private function =============================*/
void iic_slave_read_callback(void *param);
void iic_slave_read_callback(void *param)
{
    bxd_iic_slave_intr_read(BX_IIC1, iic_slave_read_buf, iic_slave_read_len, iic_slave_read_callback);
    LOG_RAW("iic_slave_rxdata_check = \r\n");
    for(uint32_t i = 1 ; i < (iic_slave_read_len + 1); i++)
    {
        LOG_RAW("0x%x ", iic_slave_read_buf[i - 1]);
        if(i%8 == 0)
            LOG_RAW("\r\n");
    }
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
    bxd_iic_open(BX_IIC1);
    bxd_iic_set_scl(BX_IIC1, IIC_SLAVE_SCL_PIN);
    bxd_iic_set_sda(BX_IIC1, IIC_SLAVE_SDA_PIN);
    bxd_iic_set_speed(BX_IIC1, BX_IIC_SPEED_STANDARD);
    bxd_iic_set_addr_bit(BX_IIC1, BX_IIC_ADDR_BIT_7B);
    bxd_iic_set_mode(BX_IIC1, BX_IIC_MODE_SLAVE);
    bxd_iic_set_slave_addr(BX_IIC1, IIC_SLAVE_ADDR);
    bxd_iic_slave_intr_read(BX_IIC1, iic_slave_read_buf, iic_slave_read_len, iic_slave_read_callback);
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



