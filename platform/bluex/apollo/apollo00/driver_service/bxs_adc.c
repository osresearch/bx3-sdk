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
#include "bxs_adc.h"
#include "bxd_adc.h"
#include "bx_pm.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bxs_adc {
    s32 id;
    void * handle;
};
/* private variables ---------------------------------------------------------*/
struct bxs_adc adc_svc = {0};
/* exported variables --------------------------------------------------------*/

/* private define ------------------------------------------------------------*/
#define GET_ADC_SERVICE_BY_ID( p_svc, svc_id )                  \
do{                                                             \
    if( ( svc_id ) == adc_svc.id ) {                            \
        p_svc = &adc_svc;                                       \
    } else {                                                    \
        return BX_ERR_NOTSUP;                                   \
    }                                                           \
}while(0)

/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t adc_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bxs_adc * p_svc;
    GET_ADC_SERVICE_BY_ID( p_svc, id );

    bx_err_t bx_err = BX_OK;
    switch( msg ) {
        case BXM_OPEN: {
            bx_pm_lock( BX_PM_ADC );
            return bxd_adc_open( p_svc->handle );
        }


        case BXM_CLOSE: {
            bx_pm_unlock( BX_PM_ADC );
            return bxd_adc_close( p_svc->handle );
        }

        case BXM_ADC_VOLT: {
            u32 value;
            bx_err = bxd_adc_get_volt( p_svc->handle, param0, &value );
            bx_public( id, BXM_ADV_VOLT_DATA_UPDATE, param0, value );
            break;
        }


        case BXM_ADC_BATTERY: {
            u32 value;
            bx_err = bxd_adc_get_battery( p_svc->handle, &value );
            bx_public( id, BXM_ADV_BAT_DATA_UPDATE, value, param1 );
            break;
        }

        case BXM_ADC_TEMPERATURE: {
            u32 value;
            bx_err = bxd_adc_get_chip_temperature( p_svc->handle, &value );
            bx_public( id, BXM_ADV_TEMP_DATA_UPDATE, value, param1 );
            break;
        }

        default:
            return BX_ERR_NOTSUP;
    }
    return bx_err;
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t adc_property_set( s32 id, u32 property, u32 param0, u32 param1 )
{
    return BX_ERR_NOTSUP;
//    struct bx_adc_service * p_svc;
//    GET_ADC_SERVICE_BY_ID( p_svc, id );
//
//    switch( property ) {
//        default:
//            return BX_ERR_NOTSUP;
//    }
//    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t adc_property_get( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bxs_adc * p_svc;
    GET_ADC_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_VALUE:
            return bxd_adc_get_value( p_svc->handle, param0, ( int32_t * )param1 );

        case BXP_ADC_VOLT:
            return bxd_adc_get_volt( p_svc->handle, param0, ( u32 * )param1 );

        case BXP_ADC_BATTERY:
            return bxd_adc_get_battery( p_svc->handle, ( u32 * )param0 );

        case BXP_ADC_TEMPERATURE:
            return bxd_adc_get_chip_temperature( p_svc->handle, ( u32 * )param0 );

        default:
            return BX_ERR_NOTSUP;
    }
//    return BX_OK;
}


/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bxs_adc_register( void )
{
    struct bx_service svc;
    svc.name = "adc service";
    svc.msg_handle_func = adc_msg_handle;
    svc.prop_get_func = adc_property_get;
    svc.prop_set_func = adc_property_set;
    adc_svc.id = bx_register( &svc );
    if( adc_svc.id == -1 ) {
        return false;
    }

    adc_svc.handle = BX_ADC;
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_adc_id( void )
{
    return adc_svc.id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



