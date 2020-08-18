/**
  ******************************************************************************
  * @file   :   .c
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

/* includes ------------------------------------------------------------------*/

#include "bx_drv_gpio.h"

/* private define ------------------------------------------------------------*/
#define CHECK_HANDLE(hdl)                                   \
do{                                                         \
    if( (hdl) != BX_GPIOA ) {                               \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)


#define CHECK_PIN_NUM(pin_num)                              \
do{                                                         \
    if( (pin_num) > 31 ) {                                  \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_MODE(mode)                                    \
do{                                                         \
    if( (mode) >= BX_GPIO_MODE_MAX ) {                      \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_PULL(pull)                                    \
do{                                                         \
    if( (pull) >= BX_GPIO_PULL_MAX ) {                      \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_AF_TYPE(type)                                 \
do{                                                         \
    if( (type) >= BX_GPIO_AFT_MAX ) {                       \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)
/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/


/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_open( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_close( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_PER->CLKG1 |= PER_CLKG1_CLR_GPIO;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_read( void * hdl, u32 * pin_value )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( pin_value );

    * pin_value = BX_GPIOA->ID;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_write( void * hdl, u8 pin_num, u8 is_high )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );

    if( is_high > 0 ) {
        BX_GPIOA->OD |= ( 0x01UL << pin_num );
    } else {
        BX_GPIOA->OD &= ~( 0x01UL << pin_num );
    }

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_toggle( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );

    //异或操作包括读写改3个操作，容易出现bug，并且此类bug较难复现
    //BX_GPIOA->OD ^= ( 0x01UL << pin_num );

    if( BX_GPIOA->OD & ( 0x01UL << pin_num ) ) {
        BX_GPIOA->OD &= ~( 0x01UL << pin_num );
    } else {
        BX_GPIOA->OD |= ( 0x01UL << pin_num );
    }

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t gpio_set_it_mode( void * hdl, u8 pin_num, u8 mode )
{
    u32 pin_mask =  0x01UL << pin_num;
    if( pin_num >= 2 ) {
        BX_AWO-> GPIOIE |= ( pin_mask );
        BX_AWO-> GPIOIS |= ( pin_mask );
    }
    switch( mode ) {
        case BX_GPIO_MODE_IT_LOW:
            BX_GPIOA->IT &= ~( pin_mask );
            BX_GPIOA->IP &= ~( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_HIGH:
            BX_GPIOA->IT &= ~( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_RISING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_FALLING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP &= ~( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_RISING_FALLING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE |= ( pin_mask );
            break;

        default:
            return BX_ERR_INVAL;
    }
    BX_GPIOA->IE |= pin_mask;
    BX_GPIOA->IM &= ~( pin_mask );

    NVIC_ClearPendingIRQ( GPIO_IRQn );
    NVIC_EnableIRQ( GPIO_IRQn );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint8_t ext_int_idx_get( uint8_t pin_num )
{
    uint8_t idx = 0xff;
    switch( pin_num ) {
        case 15:
            idx = 0;
            break;
        case 16:
            idx = 1;
            break;
        case 17:
            idx = 2;
            break;
        case 22:
            idx = 3;
            break;
        case 23:
            idx = 4;
            break;
    }
    return idx;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t gpio_set_eit_mode( void * hdl, u8 pin_num, u8 mode )
{
    u8 index = ext_int_idx_get( pin_num );
    if( index == 0xFF ) {
        return BX_ERR_PERM;
    }

    u32 trigger_mode = 0;

    switch( mode ) {
        case BX_GPIO_MODE_EIT_LOW:
            trigger_mode = 0;
            break;

        case BX_GPIO_MODE_EIT_HIGH:
            trigger_mode = 1;
            break;

        case BX_GPIO_MODE_EIT_RISING:
            trigger_mode = 2;
            break;

        case BX_GPIO_MODE_EIT_FALLING:
            trigger_mode = 3;
            break;

        case BX_GPIO_MODE_EIT_RISING_FALLING:
            return BX_ERR_NOTSUP;

        default:
            return BX_ERR_INVAL;
    }

    u32 pin_mask =  0x01UL << pin_num;

    BX_AWO-> GPIOIE |= ( pin_mask );
    BX_AWO-> GPIOIS |= ( pin_mask );

    //清中断
    BX_AWO->EICLR |= ( 0x01UL << index );
    //先失能
    BX_AWO->EICFG &= ~( 0x01UL << index );
    //作为外部中断源
    BX_AWO->EICFG |= ( 0x01UL << ( index + 20 ) );
    //设置触发模式
    BX_AWO->EICFG |= trigger_mode << ( 8 + index * 2 );
    //使能外部中断
    BX_AWO->EICFG |= ( 0x01UL << index );

    NVIC_ClearPendingIRQ( EXT_INTR_IRQn );
    NVIC_EnableIRQ( EXT_INTR_IRQn );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_set_mode( void * hdl, u8 pin_num, u8 mode )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    CHECK_MODE( mode );

    u32 pin_mask =  0x01UL << pin_num;
    switch( mode ) {
        case BX_GPIO_MODE_INPUT:
            BX_GPIOA->DIR &= ~( pin_mask );
            BX_AWO->GPIOIS |= ( pin_mask );
            BX_AWO->GPIOIE |= ( pin_mask );
            break;

        case BX_GPIO_MODE_OUTPUT:
            BX_GPIOA->DIR |= ( pin_mask );
            break;

        case BX_GPIO_MODE_IT_LOW:
        case BX_GPIO_MODE_IT_HIGH:
        case BX_GPIO_MODE_IT_RISING:
        case BX_GPIO_MODE_IT_FALLING:
        case BX_GPIO_MODE_IT_RISING_FALLING:
            return gpio_set_it_mode( hdl, pin_num, mode );


        case BX_GPIO_MODE_EIT_LOW:
        case BX_GPIO_MODE_EIT_HIGH:
        case BX_GPIO_MODE_EIT_RISING:
        case BX_GPIO_MODE_EIT_FALLING:
        case BX_GPIO_MODE_EIT_RISING_FALLING:
            return gpio_set_eit_mode( hdl, pin_num, mode );

        default:
            return BX_ERR_INVAL;
    };
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_set_pull( void * hdl, u8 pin_num, u8 pull )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    CHECK_PULL( pull );

    switch( pull ) {
        case BX_GPIO_PULLUP:
            BX_AWO->GPIOPE |= ( 0x01 << pin_num );
            BX_AWO->GPIOPS |= ( 0x01 << pin_num );
            break;

        case BX_GPIO_PULLDOWN:
            BX_AWO->GPIOPE |= ( 0x01 << pin_num );
            BX_AWO->GPIOPS &= ~( 0x01 << pin_num );
            break;

        case BX_GPIO_NOPULL:
            BX_AWO->GPIOPE &= ~( 0x01 << pin_num );
            break;

        default:
            return BX_ERR_INVAL;
    }

    return BX_OK;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



