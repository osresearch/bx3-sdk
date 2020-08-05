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
#ifndef __BX_SOFTWARE_TIMER_H__
#define __BX_SOFTWARE_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "rwip_task.h"

/* exported paras ------------------------------------------------------------*/
#define BX_SOFTWARE_TIMER_CONFIG_COUNT_MAX              10

/* exported types ------------------------------------------------------------*/

typedef enum {
    SFTIM_DUMMY_MSG = TASK_FIRST_MSG(TASK_ID_TIMER),
    
    SFTIM_MSG_CREAT_TIMER,
    
    SFTIM_MSG_TIM_FIRST,
    SFTIM_MSG_TIM_END = ( SFTIM_MSG_TIM_FIRST + BX_SOFTWARE_TIMER_CONFIG_COUNT_MAX ),
    
    SFTIM_MSG_MAX = (SFTIM_DUMMY_MSG + BX_SOFTWARE_TIMER_CONFIG_COUNT_MAX)
}timer_msg_e;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/
void     sftim_init(void);
uint16_t sftim_creat(uint32_t time_10ms,bool periodic);
void     sftim_stop(uint16_t timer_id);
bool     sftim_is_active(uint16_t timer_id);

void     sftim_timeout_callback(uint16_t timer_id);

void     sftim_add_shell_cmd(void);

#ifdef __cplusplus
}
#endif

#endif /* __BX_SOFTWARE_TIMER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
