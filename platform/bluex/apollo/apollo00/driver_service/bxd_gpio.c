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

#include "bxd_gpio.h"
#include "io_ctrl.h"
#include "sysctrl.h"
#include "bx_pcb_config.h"
#include "bx_dbg.h"
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
static u8 pin_intr_mode[32] = { 0 };
static gpio_intr_cb interrupt_callback = NULL;
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
bx_err_t bxd_gpio_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    static bool is_open = false;
    if( ! is_open ) {
        BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
        io_init();
        is_open = true;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_close( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_PER->CLKG1 &= ~PER_CLKG1_SET_GPIO;
    BX_PER->CLKG1 |= PER_CLKG1_CLR_GPIO;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_read( void * hdl, u32 * pin_value )
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
bx_err_t bxd_gpio_write( void * hdl, u8 pin_num, u8 is_high )
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
bx_err_t bxd_gpio_toggle( void * hdl, u8 pin_num )
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

        case BX_GPIO_MODE_NO_IT:
            break;

        default:
            return BX_ERR_INVAL;
    }

    if ( mode == BX_GPIO_MODE_NO_IT ) {
        BX_GPIOA->IE &= ~( pin_mask );
        BX_GPIOA->IM |= pin_mask;
    } else {
        BX_GPIOA->IE |= pin_mask;
        BX_GPIOA->IM &= ~( pin_mask );
    }

    pin_intr_mode[pin_num] = mode;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_clr_intr( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_GPIOA->EOI = 0xFFFFFFFF;
    BX_AWO->EICLR = 0x3F;

    NVIC_ClearPendingIRQ( GPIO_IRQn );
    NVIC_ClearPendingIRQ( EXT_INTR_IRQn );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_enable_intr( void * hdl )
{
    CHECK_HANDLE( hdl );

    NVIC_EnableIRQ( GPIO_IRQn );
    NVIC_EnableIRQ( EXT_INTR_IRQn );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_disable_intr( void * hdl )
{
    CHECK_HANDLE( hdl );

    NVIC_DisableIRQ( GPIO_IRQn );
    NVIC_DisableIRQ( EXT_INTR_IRQn );

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

    sysctrl_io_config_mask( 1 << pin_num, EXTERNAL_INTR_IO );

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

        case BX_GPIO_MODE_NO_EIT:
            break;

        default:
            return BX_ERR_INVAL;
    }
    if( mode == BX_GPIO_MODE_NO_EIT ) {
        BX_AWO->EICFG &= ~( 0x01UL << index );
        BX_AWO->EICFG &= ~( 0x01UL << ( index + 20 ) );
    } else {
        u32 pin_mask =  0x01UL << pin_num;

        BX_AWO-> GPIOIE |= ( pin_mask );
        BX_AWO-> GPIOIS |= ( pin_mask );

        //中断失能
        BX_AWO->EICFG &= ~( 0x01UL << index );
        //中断源选择
        BX_AWO->EICFG |= ( 0x01UL << ( index + 20 ) );
        //设置中断触发模式
        //注意 &= ~ 的操作实际上是设置触发模式为高电平触发，若引脚此时刚好为高，会触发一次中断
        //    BX_AWO->EICFG &= ~( 0x3 << ( 8 + index * 2 ) );
        //    BX_AWO->EICFG |= trigger_mode << ( 8 + index * 2 );
        //此设置方式则不会存在上面的风险
        u32 value = BX_AWO->EICFG;
        value &= ~( 0x3 << ( 8 + index * 2 ) );
        value |= trigger_mode << ( 8 + index * 2 );
        BX_AWO->EICFG = value;

        //清空因设置中断触发模式导致的可能的中断
        BX_AWO->EICLR |= ( 0x01UL << index );
        //中断使能
        BX_AWO->EICFG |= ( 0x01UL << index );
    }

    pin_intr_mode[pin_num] = mode;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_disable_ext_intr( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );

    u8 index = ext_int_idx_get( pin_num );
    if( index == 0xFF ) {
        return BX_ERR_PERM;
    }
    BX_AWO->EICFG &= ~( 0x01UL << index );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_enable_ext_intr( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );

    u8 index = ext_int_idx_get( pin_num );
    if( index == 0xFF ) {
        return BX_ERR_PERM;
    }
    BX_AWO->EICLR |= ( 0x01UL << index );
    BX_AWO->EICFG |= ( 0x01UL << index );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_set_mode( void * hdl, u8 pin_num, u8 mode )
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
        
        case BX_GPIO_MODE_NO_IT:
        case BX_GPIO_MODE_IT_LOW:
        case BX_GPIO_MODE_IT_HIGH:
        case BX_GPIO_MODE_IT_RISING:
        case BX_GPIO_MODE_IT_FALLING:
        case BX_GPIO_MODE_IT_RISING_FALLING:
            return gpio_set_it_mode( hdl, pin_num, mode );

        case BX_GPIO_MODE_NO_EIT:
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
bx_err_t bxd_gpio_set_pull( void * hdl, u8 pin_num, u8 pull )
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
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_gpio_set_intr_callback( void * hdl, gpio_intr_cb cb )
{
    CHECK_HANDLE( hdl );

    interrupt_callback =  cb;

    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u32 ext_int_stat_2_pin_state( u32 ext_int_stat )
{
    u32 ret = 0;
    u32 temp = 0;
    for( u32 i = 0; i < 5; i++ ) {
        if( ext_int_stat & ( 0x01 << i ) ) {
            switch( i ) {
                case 0:
                    temp = 0x01 << 15;
                    break;

                case 1:
                    temp = 0x01 << 16;
                    break;

                case 2:
                    temp = 0x01 << 17;
                    break;

                case 3:
                    temp = 0x01 << 22;
                    break;

                case 4:
                    temp = 0x01 << 23;
                    break;

                default:
                    break;
            }
        }
        ret |= temp;
    }
    return ret;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u8 get_reason( u8 pin_num )
{
    switch( pin_intr_mode[pin_num] ) {
        case BX_GPIO_MODE_IT_LOW:
        case BX_GPIO_MODE_EIT_LOW:
            return BX_GPIO_INTR_LOW;

        case BX_GPIO_MODE_IT_HIGH:
        case BX_GPIO_MODE_EIT_HIGH:
            return BX_GPIO_INTR_HIGH;

        case BX_GPIO_MODE_IT_RISING:
        case BX_GPIO_MODE_EIT_RISING:
            return BX_GPIO_INTR_RISING;

        case BX_GPIO_MODE_IT_FALLING:
        case BX_GPIO_MODE_EIT_FALLING:
            return BX_GPIO_INTR_FALLING;

        case BX_GPIO_MODE_IT_RISING_FALLING:
        case BX_GPIO_MODE_EIT_RISING_FALLING:
            return BX_GPIO_INTR_RISING_FALLING;

        default :
            return BX_GPIO_INTR_NONE;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void GPIO_IRQHandler( void )
{
    uint32_t int_stat = BX_GPIOA->IS;
    BX_GPIOA->EOI |= int_stat;
    bx_logln("BXM_GPIO_INTR");
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void EXT_INTR_IRQHandler( void )
{
    uint32_t ext_int_stat = BX_FIELD_RD( BX_AWO->EIVAL, AWO_EIVAL_VAL ) ;
    BX_AWO->EICLR |= ext_int_stat;
    u32 pin_state = ext_int_stat_2_pin_state( ext_int_stat );
    if( interrupt_callback != NULL ) {
        for( u8 i = 0; i < 32; i++ ) {
            if( pin_state & ( 0x1 << i ) ) {
                u8 reason = get_reason( i );
                if( reason != BX_GPIO_INTR_NONE ) {
                    interrupt_callback( BX_GPIOA, i, reason );
                } else {
                    //something error
                }
            }
        }
    }
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



