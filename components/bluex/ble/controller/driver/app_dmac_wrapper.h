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
#ifndef __APP_DMAC_WRAPPER_H__
#define __APP_DMAC_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "app_dmac.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void            app_dmac_init_wrapper(void);
void            app_dmac_uninit_wrapper(void);

periph_err_t    app_dmac_start_wrapper(app_dmac_transfer_param_t *param,uint8_t *ch_idx);
periph_err_t    app_dmac_transfer_cancel_wrapper(uint8_t ch_idx,uint32_t *remaining_size);
periph_err_t    app_dmac_transfer_wait_wrapper(uint8_t ch_idx);


#ifdef __cplusplus
}
#endif

#endif /* __APP_DMAC_WRAPPER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
