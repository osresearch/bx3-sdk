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
#include "bx_kernel.h"
#include "bx_service_gpio.h"
#include "bx_drv_gpio.h"
#include "bx_pm.h"
/* config --------------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bx_gpio_service {
    s32 id;
    void * handle;
};

/* private variables ---------------------------------------------------------*/
static struct bx_gpio_service gpioa_svc = { 0 };

/* exported variables --------------------------------------------------------*/

/* private define ------------------------------------------------------------*/
#define GET_GPIO_SERVICE_BY_ID( p_svc, svc_id )             \
do{                                                         \
    if( ( svc_id ) == gpioa_svc.id ) {                      \
        p_svc = &gpioa_svc;                                 \
    }else{                                                  \
        return BX_ERR_NOTSUP;                               \
    }                                                       \
}while(0)

/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t gpio_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bx_gpio_service * p_svc;
    GET_GPIO_SERVICE_BY_ID( p_svc, id );

    switch( msg ) {
        case BXM_OPEN : {
            bx_pm_lock( BX_PM_GPIO );
            return bx_drv_gpio_open( p_svc->handle );
        }

        case BXM_CLOSE : {
            bx_pm_unlock( BX_PM_GPIO );
            return bx_drv_gpio_close( p_svc->handle );
        }

        case BXM_READ :
            return bx_drv_gpio_read( p_svc->handle, ( u32 * )param0 );

        case BXM_WRITE :
            return bx_drv_gpio_write( p_svc->handle, param0, param1 );

        case BXM_TOGGLE:
            return bx_drv_gpio_toggle( p_svc->handle, param0 );

        default:
            return BX_ERR_NOTSUP;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t gpio_property_set( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bx_gpio_service * p_svc;
    GET_GPIO_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_MODE:
            bx_drv_gpio_set_mode( p_svc->handle, param0, param1 );
            break;

        case BXP_GPIO_PULL:
            bx_drv_gpio_set_pull( p_svc->handle, param0, param1 );
            break;

        default:
            return BX_ERR_NOTSUP;
    }
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t gpio_property_get( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bx_gpio_service * p_svc;
    GET_GPIO_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_HANDLE:
            *( u32 * )param0 = ( u32 )( p_svc->handle );
            break;

        default:
            return BX_ERR_NOTSUP;

    }
    return BX_OK;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxs_gpio_register( void )
{
    memset( &gpioa_svc, 0, sizeof( struct bx_gpio_service ) );
    struct bx_service svc;
    svc.name = "gpioa service";
    svc.msg_handle_func = gpio_msg_handle;
    svc.prop_get_func = gpio_property_get;
    svc.prop_set_func = gpio_property_set;
    gpioa_svc.id = bx_register( &svc );
    if( gpioa_svc.id == -1 ) {
        return BX_ERR_NOMEM;
    }

    gpioa_svc.handle = BX_GPIOA;

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_gpio_a_id( void )
{
    return gpioa_svc.id;
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
void GPIO_IRQHandler( void )
{
    uint32_t int_stat = BX_GPIOA->IS;
    BX_GPIOA->EOI |= int_stat;
    bx_public( gpioa_svc.id, BXM_GPIO_INTR, int_stat, 0 );
}
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
void EXT_INTR_IRQHandler( void )
{
    uint8_t ext_int_stat = BX_FIELD_RD( BX_AWO->EIVAL, AWO_EIVAL_VAL ) ;
    BX_AWO->EICLR |= ext_int_stat;
    u32 pin_state = ext_int_stat_2_pin_state( ext_int_stat );

    bx_public( gpioa_svc.id, BXM_GPIO_EXT_INTR, pin_state, 0 );
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



