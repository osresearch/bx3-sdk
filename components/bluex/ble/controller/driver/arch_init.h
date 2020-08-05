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
#ifndef __ARCH_INIT_H__
#define __ARCH_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "rwip.h"
#include "app_qspi.h"

/* exported define -----------------------------------------------------------*/
#define BOOTINIT_FLAG       0x3399

/* exported types ------------------------------------------------------------*/
typedef struct{
    uint32_t ota_base;
    uint32_t data_base;
}app_info_t;

typedef struct
{
    uint8_t cmd;
    uint8_t quad_bit_offset:4,
            status_length:2;
}quad_status_rw_t;

typedef struct

{
    quad_status_rw_t read;
    quad_status_rw_t write;
}quad_enable_config_t;

typedef struct{
    uint16_t total_size_64k;
    multi_read_param_t multi_read_param;
    quad_enable_config_t quad_enable_config;
}flash_info_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define set_scb_vtor(val)       \
        do{                     \
            __DMB();            \
            SCB->VTOR = val;    \
            __DSB();            \
        }while(0)
/* exported functions --------------------------------------------------------*/

void mpu_enable_for_xip_region(void);
void mpu_disable_for_xip_region(void);

void cache_config(void) ;
void cache_enable(void);
void cache_disable(void);

void soc_init(void);

const struct rwip_eif_api * serial_eif_get(void);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_INIT_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
