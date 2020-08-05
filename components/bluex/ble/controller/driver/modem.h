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
#ifndef __MODEM_H__
#define __MODEM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "reg_ble_mdm.h"
#include <stdbool.h>

/* exported define -----------------------------------------------------------*/
#define VCO_VALUE_INVALID	0xFFFFFFFF

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void set_vco_buff_aa55(uint32_t param2 , uint32_t param3 , uint32_t param4);
void set_vco_buff_others(uint32_t param2 , uint32_t param3 , uint32_t param4);
void enable_vco_value(bool is_aa55);
void set_deriv_calib_0(uint8_t select);


void modem_init(void);
void modem_vcocali_start(void);
void modem_vcocali(void);
void modem_dev_calib_in_main(void);

#ifdef __cplusplus
}
#endif

#endif /* __MODEM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
