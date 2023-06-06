/**
  ******************************************************************************
  * @file   :   bx_iic_type_def.h
  * @version:
  * @author :
  * @brief  :   Define common iic types for different MCU
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BX_IIC_TYPE_DEF_H__
#define __BX_IIC_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported types ------------------------------------------------------------*/

enum bx_iic_mode{
    BX_IIC_MODE_MASTER,
    BX_IIC_MODE_SLAVE,
    BX_IIC_MODE_MAX,
};

enum bx_iic_speed{
    //100kHz
    BX_IIC_SPEED_STANDARD,
    //400kHz
    BX_IIC_SPEED_FAST,
    //1000kHz
    BX_IIC_SPEED_HIGHEST,
    
    BX_IIC_SPEED_MAX,
};

enum bx_iic_addr_bit {
    BX_IIC_ADDR_BIT_7B,
    BX_IIC_ADDR_BIT_10B,
    BX_IIC_ADDR_BIT_MAX,
};


typedef enum
{
    IIC_STATE_RESET      = 0x0, /* not yet init */
    IIC_STATE_READY      = 0x1, /* ready for use */
    IIC_STATE_WRITE      = 0x2, /* tx going */
    IIC_STATE_READ       = 0x3, /* rx going */
    IIC_STATE_TIMEOUT    = 0x4, /* timeout */
}bxd_iic_state_t;


typedef struct
{
    uint8_t                         *p_tx_buff;
    uint32_t                        tx_size;
    uint8_t                         *p_rx_buff;
    uint32_t                        rx_size;
    bxd_iic_state_t                 state;
    uint8_t                        error_detect;

    void (* tx_cplt_cb)(void *);
    void (* rx_cplt_cb)(void *);
}bxd_iic_env_t;
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __BX_IIC_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

