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
#ifndef __APP_HWECC_WRAPPER_H__
#define __APP_HWECC_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "app_hwecc.h"

/* exported define -----------------------------------------------------------*/
typedef void (*ecc_cb_t)(void *);

/* exported types ------------------------------------------------------------*/
typedef struct{
    ecc_in_t in;                   /**< input data for ecc.        */
    ecc_out_t out;                 /**< ecc output buffer.         */
    ecc_cb_t cb;                   /**< callback function pointer. */
    void *dummy;                   /**< callback parameter.        */
}ecc_queue_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void            app_hwecc_init_wrapper(void);
void            app_hwecc_uninit_wrapper(void);

periph_err_t    app_hwecc_calculate_wrapper(ecc_queue_t *param);

#ifdef __cplusplus
}
#endif

#endif /* __APP_HWECC_WRAPPER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

