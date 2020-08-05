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
#ifndef __REG_GPIO_H__
#define __REG_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/


typedef struct
{
    volatile uint32_t GPIO_SWPORTA_DR;
    volatile uint32_t GPIO_SWPORTA_DDR;
    volatile uint32_t reserved0[10];
    volatile uint32_t GPIO_INTEN;
    volatile uint32_t GPIO_INTMASK;
    volatile uint32_t GPIO_INTTYPE_LEVEL;
    volatile uint32_t GPIO_INT_POLARITY;
    volatile uint32_t GPIO_INTSTATUS;
    volatile uint32_t GPIO_RAW_INTSTATUS;
    volatile uint32_t GPIO_DEBOUNCE;
    volatile uint32_t GPIO_PORTA_EOI;
    volatile uint32_t GPIO_EXT_PORTA;
    volatile uint32_t reserved1[3];
    volatile uint32_t GPIO_LS_SYNC;
    volatile uint32_t reserved2[1];
    volatile uint32_t GPIO_INT_BOTHEDGE;
    volatile uint32_t GPIO_VER_ID_CODE;
}ble_reg_gpio_t;

enum GPIO_GPIO_SWPORTA_DR_FIELD
{
    GPIO_PORT_A_DATA_REGISTER_MASK = (int)0xffffffff,
    GPIO_PORT_A_DATA_REGISTER_POS = 0,
};

enum GPIO_GPIO_SWPORTA_DDR_FIELD
{
    GPIO_PORT_A_DATA_DIRECTION_REGISTER_MASK = (int)0xffffffff,
    GPIO_PORT_A_DATA_DIRECTION_REGISTER_POS = 0,
};

enum GPIO_GPIO_INTEN_FIELD
{
    GPIO_INTERRUPT_ENABLE_MASK = (int)0xffffffff,
    GPIO_INTERRUPT_ENABLE_POS = 0,
};

enum GPIO_GPIO_INTMASK_FIELD
{
    GPIO_INT_MASK_MASK = (int)0xffffffff,
    GPIO_INT_MASK_POS = 0,
};

enum GPIO_GPIO_INTTYPE_LEVEL_FIELD
{
    GPIO_INT_LEVEL_MASK = (int)0xffffffff,
    GPIO_INT_LEVEL_POS = 0,
};

enum GPIO_GPIO_INT_POLARITY_FIELD
{
    GPIO_INT_POLARITY_MASK = (int)0xffffffff,
    GPIO_INT_POLARITY_POS = 0,
};

enum GPIO_GPIO_INTSTATUS_FIELD
{
    GPIO_INT_STATUS_MASK = (int)0xffffffff,
    GPIO_INT_STATUS_POS = 0,
};

enum GPIO_GPIO_RAW_INTSTATUS_FIELD
{
    GPIO_RAW_INT_STATUS_MASK = (int)0xffffffff,
    GPIO_RAW_INT_STATUS_POS = 0,
};

enum GPIO_GPIO_DEBOUNCE_FIELD
{
    GPIO_DEBOUNCE_ENABLE_MASK = (int)0xffffffff,
    GPIO_DEBOUNCE_ENABLE_POS = 0,
};

enum GPIO_GPIO_PORTA_EOI_FIELD
{
    GPIO_INT_CLEAR_MASK = (int)0xffffffff,
    GPIO_INT_CLEAR_POS = 0,
};

enum GPIO_GPIO_EXT_PORTA_FIELD
{
    GPIO_EXT_PORTA_MASK = (int)0xffffffff,
    GPIO_EXT_PORTA_POS = 0,
};

enum GPIO_GPIO_LS_SYNC_FIELD
{
    GPIO_SYNC_LEVEL_MASK = 0x1,
    GPIO_SYNC_LEVEL_POS = 0,
};

enum GPIO_GPIO_INT_BOTHEDGE_FIELD
{
    GPIO_INT_BOTH_EDGE_MASK = (int)0xffffffff,
    GPIO_INT_BOTH_EDGE_POS = 0,
};

enum GPIO_GPIO_VER_ID_CODE_FIELD
{
    GPIO_GPIO_VER_ID_MASK = (int)0xffffffff,
    GPIO_GPIO_VER_ID_POS = 0,
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __REG_GPIO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
