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
#ifndef __APOLLO_00_REG_GPIO_H__
#define __APOLLO_00_REG_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"


/* exported types ------------------------------------------------------------*/
typedef struct {
    __IO uint32_t OD;                   /* !< output data                               0x0000 */
    __IO uint32_t DIR;                  /* !< Direction                                 0x0004 */
         uint32_t reserved0[10];        /* !< wait description                          0x0008 */
    __IO uint32_t IE;                   /* !< interrupt enable                          0x0030 */
    __IO uint32_t IM;                   /* !< interrupt mask                            0x0034 */
    __IO uint32_t IT;                   /* !< interrupt type                            0x0038 */
    __IO uint32_t IP;                   /* !< Interrupt polarity                        0x003C */
    __I  uint32_t IS;                   /* !< Interrupt status                          0x0040 */
    __I  uint32_t RIS;                  /* !< Raw Interrupt status                      0x0044 */
    __IO uint32_t DE;                   /* !< Debounce enable                           0x0048 */
    __O  uint32_t EOI;                  /* !< End of Interrupt Register                 0x004C */
    __I  uint32_t ID;                   /* !< input data                                0x0050 */
         uint32_t reserved1[3];         /* !< wait description                          0x0054 */
    __IO uint32_t LSSE;                 /* !< Level-sensitive synchronization enable    0x0060 */
         uint32_t reserved2[1];         /* !< wait description                          0x0064 */
    __IO uint32_t IBE;                  /* !< Interrupt both edge                       0x0068 */
    __I  uint32_t VER;                  /* !< Component Version                         0x006C */
} reg_gpio_t;

/* exported variables --------------------------------------------------------*/

/* bit definition ------------------------------------------------------------*/


/* value type ----------------------------------------------------------------*/

/***************  type definition for gpio pin (gpio_pin_type)  ***************/
#define GPIO_PIN_NONE                                       ((uint32_t)0x00000000U)             /* None Pin selected */
#define GPIO_PIN_0                                          ((uint32_t)0x00000001U)             /* Pin 0 selected    */
#define GPIO_PIN_1                                          ((uint32_t)0x00000002U)             /* Pin 1 selected    */
#define GPIO_PIN_2                                          ((uint32_t)0x00000004U)             /* Pin 2 selected    */
#define GPIO_PIN_3                                          ((uint32_t)0x00000008U)             /* Pin 3 selected    */
#define GPIO_PIN_4                                          ((uint32_t)0x00000010U)             /* Pin 4 selected    */
#define GPIO_PIN_5                                          ((uint32_t)0x00000020U)             /* Pin 5 selected    */
#define GPIO_PIN_6                                          ((uint32_t)0x00000040U)             /* Pin 6 selected    */
#define GPIO_PIN_7                                          ((uint32_t)0x00000080U)             /* Pin 7 selected    */
#define GPIO_PIN_8                                          ((uint32_t)0x00000100U)             /* Pin 8 selected    */
#define GPIO_PIN_9                                          ((uint32_t)0x00000200U)             /* Pin 9 selected    */
#define GPIO_PIN_10                                         ((uint32_t)0x00000400U)             /* Pin 10 selected   */
#define GPIO_PIN_11                                         ((uint32_t)0x00000800U)             /* Pin 11 selected   */
#define GPIO_PIN_12                                         ((uint32_t)0x00001000U)             /* Pin 12 selected   */
#define GPIO_PIN_13                                         ((uint32_t)0x00002000U)             /* Pin 13 selected   */
#define GPIO_PIN_14                                         ((uint32_t)0x00004000U)             /* Pin 14 selected   */
#define GPIO_PIN_15                                         ((uint32_t)0x00008000U)             /* Pin 15 selected   */
#define GPIO_PIN_16                                         ((uint32_t)0x00010000U)             /* Pin 16 selected   */
#define GPIO_PIN_17                                         ((uint32_t)0x00020000U)             /* Pin 17 selected   */
#define GPIO_PIN_18                                         ((uint32_t)0x00040000U)             /* Pin 18 selected   */
#define GPIO_PIN_19                                         ((uint32_t)0x00080000U)             /* Pin 19 selected   */
#define GPIO_PIN_20                                         ((uint32_t)0x00100000U)             /* Pin 20 selected   */
#define GPIO_PIN_21                                         ((uint32_t)0x00200000U)             /* Pin 21 selected   */
#define GPIO_PIN_22                                         ((uint32_t)0x00400000U)             /* Pin 22 selected   */
#define GPIO_PIN_23                                         ((uint32_t)0x00800000U)             /* Pin 23 selected   */
#define GPIO_PIN_24                                         ((uint32_t)0x01000000U)             /* Pin 24 selected   */
#define GPIO_PIN_25                                         ((uint32_t)0x02000000U)             /* Pin 25 selected   */
#define GPIO_PIN_26                                         ((uint32_t)0x04000000U)             /* Pin 26 selected   */
#define GPIO_PIN_27                                         ((uint32_t)0x08000000U)             /* Pin 27 selected   */
#define GPIO_PIN_28                                         ((uint32_t)0x10000000U)             /* Pin 28 selected   */
#define GPIO_PIN_29                                         ((uint32_t)0x20000000U)             /* Pin 29 selected   */
#define GPIO_PIN_30                                         ((uint32_t)0x40000000U)             /* Pin 30 selected   */
#define GPIO_PIN_31                                         ((uint32_t)0x80000000U)             /* Pin 31 selected   */
#define GPIO_PIN_ALL                                        ((uint32_t)0xFFFFFFFFU)             /* All pins selected */

#define GPIO_PAD_MASK                                       ((uint32_t)0x3FFFFFFFU)             /* Input Enable Mask */
#define IS_GPIO_PAD(pad)                                    ( ( (pad) & GPIO_PAD_MASK ) > 0 )

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_GPIO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

