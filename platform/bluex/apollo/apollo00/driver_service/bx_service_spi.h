/**
  ******************************************************************************
  * @file   :   .h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BX_SERVICE_SPI_H__
#define __BX_SERVICE_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
struct bx_spim_txrx_config {
    u8 *    tx_buff;
    u32     tx_len;
    u8 *    rx_buff;
    u32     rx_len;
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/



enum bx_property_spim {
    BXP_SPIM_FIRST = BXP_FIRST_USER_PROP,
    
    BXP_SPIM_CS1_PIN,
    BXP_SPIM_USE_CS_NUM,
};

enum bx_msg_spim{
    BXM_SPIM_FIRST = BXM_FIRST_USER_MSG,
    
    BXM_SPIM_TXRX_START,
	BXM_SPIM_SENSOR_TEST,
};
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t    bxs_spim_register( void );
s32         bxs_spim0_id( void );
s32         bxs_spim1_id( void );


#ifdef __cplusplus
}
#endif

#endif /* __BX_SERVICE_SPI_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
