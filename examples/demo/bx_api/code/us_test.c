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
#include "us_test.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct us_test_service {
    s32 id;
    //add you environment variables
    u32 timeout;
    
    struct test_property_type my_prop;
    
    u16 wide;
    u16 high;
    char name[16];
};
/* private variables ---------------------------------------------------------*/
static struct us_test_service test_svc = {0};
/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
#define GET_TEST_SERVICE_BY_ID( p_svc, svc_id )             \
do{                                                         \
    if( ( svc_id ) == test_svc.id ) {                       \
        p_svc = &test_svc;                                  \
    } else {                                                \
        return BX_ERR_NOTSUP;                               \
    }                                                       \
}while(0)

#define CHECK_TEST_SVC_PARAM( param )                       \
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
static bx_err_t test_msg_handle( s32 svc_id, u32 msg, u32 param0, u32 param1 )
{
    struct us_test_service * p_svc;
    GET_TEST_SERVICE_BY_ID( p_svc, svc_id );

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
static bx_err_t test_property_set( s32 svc_id, u32 property, u32 param0, u32 param1 )
{
    struct us_test_service * p_svc;
    GET_TEST_SERVICE_BY_ID( p_svc, svc_id );

    switch( property ) {
        //add your case
        case BXP_TIMEOUT: {
            p_svc->timeout = param0;
            return BX_OK;
        }
        
        case USP_TEST_MY_PROPERTY: {
            p_svc->my_prop = *( struct test_property_type * )param0;
            return BX_OK;
        }
        
        case USP_TEST_WIDE: {
            p_svc->wide = param0;
            return BX_OK;
        }
        
        case USP_TEST_HIGH: {
            p_svc->high = param0;
            return BX_OK;
        }
        
        case USP_TEST_NAME: {
            strcpy( p_svc->name,(char *)param0 );
            return BX_OK;
        }

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
static bx_err_t test_property_get( s32 svc_id, u32 property, u32 param0, u32 param1 )
{
    struct us_test_service * p_svc;
    GET_TEST_SERVICE_BY_ID( p_svc, svc_id );

    switch( property ) {
        //add your cases
        
        case BXP_TIMEOUT:{
            CHECK_TEST_SVC_PARAM(param0);
            *(u32 *)param0 = p_svc->timeout;
            return BX_OK;
        }
            
        case BXP_VERSION: {
            CHECK_TEST_SVC_PARAM(param0);
            memcpy( (u8 *)param0,"v1.0.0",7);
            return BX_OK;
        }

        case USP_TEST_MY_PROPERTY: {
            *( struct test_property_type * )param0 = p_svc->my_prop;
            return BX_OK;
        }
                
        case USP_TEST_WIDE: {
            *(u16 *)param0 = p_svc->wide;
            return BX_OK;
        }
        
        case USP_TEST_HIGH: {
            *(u16 *)param0 = p_svc->high ;
            return BX_OK;
        }
        
        case USP_TEST_NAME: {
            strcpy( (char *)param0,p_svc->name );
            return BX_OK;
        }
        default: {
            return BX_ERR_NOTSUP;
        }
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
bool us_test_register( void )
{
    struct bx_service svc;
    svc.name = "test service";
    svc.msg_handle_func = test_msg_handle;
    svc.prop_get_func = test_property_get;
    svc.prop_set_func = test_property_set;
    test_svc.id = bx_register( &svc );
    if( test_svc.id == -1 ) {
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
s32 us_test_id( void )
{
    return test_svc.id;
}

/*========================= end of exported function =========================*/

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



