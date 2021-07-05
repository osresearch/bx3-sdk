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
#include "bxs_iic.h"
#include "bxd_iic.h"
#include "bx_pm.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bxs_iic {
    s32 id;
    void * handle;

    u8 addr;
    u8 reg;
    u8 lock;
};
/* private variables ---------------------------------------------------------*/
static struct bxs_iic iic0_svc = { 0 };
static struct bxs_iic iic1_svc = { 0 };
/* exported variables --------------------------------------------------------*/


/* private define ------------------------------------------------------------*/
#define GET_IIC_SERVICE_BY_ID( p_svc, svc_id )                  \
do{                                                             \
    if( ( svc_id ) == iic0_svc.id ) {                           \
        p_svc = &iic0_svc;                                      \
    } else if( ( svc_id ) == iic1_svc.id ) {                    \
        p_svc = &iic1_svc;                                      \
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
static bx_err_t iic_svc_read_action( struct bxs_iic * p_svc, u8 * buff, u32 len )
{
    if( p_svc->lock ) {
        return BX_ERR_BUSY;
    }
    p_svc->lock = true;
    bx_err_t err = bxd_iic_read( p_svc->handle, p_svc->addr, p_svc->reg, buff, len );
    p_svc->lock = false;

    bx_public( p_svc->id, BXM_READ_DONE, p_svc->addr, p_svc->reg );
    return err;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t iic_svc_write_action( struct bxs_iic * p_svc, u8 * buff, u32 len )
{
    if( p_svc->lock ) {
        return BX_ERR_BUSY;
    }

    p_svc->lock = true;
    bx_err_t err = bxd_iic_write( p_svc->handle, p_svc->addr, p_svc->reg, buff, len );
    p_svc->lock = false;

    bx_public( p_svc->id, BXM_READ_DONE, p_svc->addr, p_svc->reg );

    return err;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t iic_svc_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bxs_iic * p_svc;
    GET_IIC_SERVICE_BY_ID( p_svc, id );

    switch( msg ) {
        case BXM_OPEN: {
            bx_pm_lock( BX_PM_IIC );
            return bxd_iic_open( p_svc->handle );
        }

        case BXM_CLOSE: {
            bx_pm_unlock( BX_PM_IIC );
            return bxd_iic_close( p_svc->handle );
        }

        case BXM_READ:
            return iic_svc_read_action( p_svc, ( u8 * )param0, param1 );

        case BXM_WRITE:
            return iic_svc_write_action( p_svc, ( u8 * )param0, param1 );

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
static bx_err_t iic_svc_property_set( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bxs_iic * p_svc;
    GET_IIC_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_HANDLE:
            p_svc->handle = ( reg_iic_t * )param0;
            break;

        case BXP_MODE:
            return bxd_iic_set_mode( p_svc->handle, param0 );

        case BXP_SPEED:
            return bxd_iic_set_speed( p_svc->handle, param0 );

        case BXP_ADDR_BIT:
            return bxd_iic_set_addr_bit( p_svc->handle, param0 );

        case BXP_ADDR:
            p_svc->addr = param0;
            break;

        case BXP_SUB_ADDR:
            p_svc->reg = param0;
            break;

        case BXP_IIC_PIN_SDA:
            return bxd_iic_set_sda( p_svc->handle, param0 );

        case BXP_IIC_PIN_SCL:
            return bxd_iic_set_scl( p_svc->handle, param0 );


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
static bx_err_t iic_svc_property_get( s32 id, u32 property, u32 param0, u32 param1 )
{
    return BX_ERR_NOTSUP;
//    switch( property ) {
//
//        case BXP_IIC_PIN_SDA:
//            break;
//
//        case BXP_IIC_PIN_SCL:
//            break;

//        case BXP_IIC_SPEED:
//            break;
//
//        case BXP_IIC_ADDR_BIT:
//            break;

//        default:
//            return BX_ERR_NOTSUP;
//    }
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
bx_err_t bxs_iic_register( void )
{
    struct bx_service svc;
    svc.name = "iic0 service";
    svc.msg_handle_func = iic_svc_msg_handle;
    svc.prop_get_func = iic_svc_property_get;
    svc.prop_set_func = iic_svc_property_set;
    iic0_svc.id = bx_register( &svc );
    if( iic0_svc.id == -1 ) {
        return BX_ERR_NOMEM;
    }
    iic0_svc.handle = BX_IIC0;

    svc.name = "iic1 service";
    svc.msg_handle_func = iic_svc_msg_handle;
    svc.prop_get_func = iic_svc_property_get;
    svc.prop_set_func = iic_svc_property_set;
    iic1_svc.id = bx_register( &svc );
    if( iic1_svc.id == -1 ) {
        return BX_ERR_NOMEM;
    }
    iic1_svc.handle = BX_IIC1;
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_iic0_id( void )
{
    return iic0_svc.id;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_iic1_id( void )
{
    return iic1_svc.id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



