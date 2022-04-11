/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) .
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* includes ------------------------------------------------------------------*/

#include "bx_kernel.h"
#include "us_xxx.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct us_xxx_service {
    s32 id;
    //add your environment variables
};
/* private variables ---------------------------------------------------------*/
static struct us_xxx_service xxx_svc = {0};
/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
#define GET_XXX_SERVICE_BY_ID( p_svc, svc_id )              \
do{                                                         \
    if( ( svc_id ) == xxx_svc.id ) {                        \
        p_svc = &xxx_svc;                                   \
    } else {                                                \
        return BX_ERR_NOTSUP;                               \
    }                                                       \
}while(0)

#define CHECK_XXX_SVC_PARAM( param )                        \
do{                                                         \
    if( param == NULL ) {                                   \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t xxx_msg_handle( s32 svc_id, u32 msg, u32 param0, u32 param1 )
{
    struct us_xxx_service * p_svc;
    GET_XXX_SERVICE_BY_ID( p_svc, svc_id );

    switch( msg ) {
        case BXM_OPEN: {
            //add your code

            return BX_OK;
        }

        case BXM_CLOSE: {
            //add your code

            return BX_OK;
        }

        //add your case


        default: {
            return BX_ERR_NOTSUP;
        }
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t xxx_property_set( s32 svc_id, u32 property, u32 param0, u32 param1 )
{
    struct us_xxx_service * p_svc;
    GET_XXX_SERVICE_BY_ID( p_svc, svc_id );

    switch( property ) {
        //add your case


        default: {
            return BX_ERR_NOTSUP;
        }
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t xxx_property_get( s32 svc_id, u32 property, u32 param0, u32 param1 )
{
    struct us_xxx_service * p_svc;
    GET_XXX_SERVICE_BY_ID( p_svc, svc_id );

    switch( property ) {
        //add your case


        default:
            return BX_ERR_NOTSUP;
    }
}


/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool us_xxx_register( void )
{
    struct bx_service svc;
    svc.name = "xxx service";
    svc.msg_handle_func = xxx_msg_handle;
    svc.prop_get_func = xxx_property_get;
    svc.prop_set_func = xxx_property_set;
    xxx_svc.id = bx_register( &svc );
    if( xxx_svc.id == -1 ) {
        return false;
    }
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 us_xxx_id( void )
{
    return xxx_svc.id;
}

/*========================= end of exported function =========================*/


/******************** (C) COPYRIGHT ****************************END OF FILE****/



