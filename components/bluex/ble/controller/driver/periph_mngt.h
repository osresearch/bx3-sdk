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
#ifndef __PERIPH_MNGT_H__
#define __PERIPH_MNGT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "periph_common.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

enum periph_domain_dev
{
    PERIPH_DOMAIN_UART0,
    PERIPH_DOMAIN_UART1,
    PERIPH_DOMAIN_SPIM0,
    PERIPH_DOMAIN_SPIM1,
    PERIPH_DOMAIN_SPIS,
    PERIPH_DOMAIN_IIC0,
    PERIPH_DOMAIN_IIC1,
    PERIPH_DOMAIN_PWM,
    PERIPH_DOMAIN_GPIO,
    PERIPH_DOMAIN_MAX,
};

enum cpu_domain_dev
{
    CPU_DOMAIN_DMAC,
    CPU_DOMAIN_TIMER0,
    CPU_DOMAIN_TIMER1,
    CPU_DOMAIN_HWECC,
    CPU_DOMAIN_ADC_CTRL,
    CPU_DOMAIN_WDT,
    CPU_DOMAIN_MAX,
};

typedef struct
{
    bool uart0_tx;
    bool uart0_rx;
    bool uart1_tx;
    bool uart1_rx;
    bool spim0;
    bool spim1;
    bool spis;
    bool iic0;
    bool iic1;
    bool pwm;
}periph_domain_stat_t;


typedef struct
{
    bool dmac;
    bool timer0;
    bool timer1;
    bool hwecc;
    bool adc_ctrl;
}cpu_domain_stat_t;

/* exported variables --------------------------------------------------------*/
extern periph_domain_stat_t periph_domain_stat;
extern cpu_domain_stat_t cpu_domain_stat;
extern periph_inst_handle_t periph_domain_recovery_buf[PERIPH_DOMAIN_MAX];
extern periph_inst_handle_t cpu_domain_recovery_buf[CPU_DOMAIN_MAX];

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool periph_domain_busy(void);
bool cpu_domain_busy(void);

#ifdef __cplusplus
}
#endif

#endif /* __PERIPH_MNGT_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
