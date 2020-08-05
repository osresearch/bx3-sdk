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
/* config -------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "rwip_config.h"
#include "patch.h"
#include "ke_task.h"
#include "rwip_task.h"
#include "task_id_patch.h"
#include "prf.h"
#include "log.h"

/* private define ------------------------------------------------------------*/
#define GET_TASK_FROM_ID_PATCH_ADDR                     0x8040
#define GET_ID_FROM_TASK_PATCH_ADDR                     0x7ea8

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

ke_task_id_t GET_TASK_FROM_ID_PATCH( ke_msg_id_t id );
ke_task_id_t GET_ID_FROM_TASK_PATCH( ke_msg_id_t task );

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
ke_task_id_t gapm_get_id_from_task_patch( ke_msg_id_t task )
{
    ke_task_id_t id = TASK_ID_INVALID;
    uint8_t idx = KE_IDX_GET( task );
    task = KE_TYPE_GET( task );
    switch( task ) {
        case TASK_GAPM:
            id = TASK_ID_GAPM;
            break;
        case TASK_GAPC:
            id = TASK_ID_GAPC;
            break;
        case TASK_GATTM:
            id = TASK_ID_GATTM;
            break;
        case TASK_GATTC:
            id = TASK_ID_GATTC;
            break;
        case TASK_L2CC:
            id = TASK_ID_L2CC;
            break;
#if (AHI_TL_SUPPORT)
        case TASK_AHI:
            id = TASK_ID_AHI;
            break;
#endif // (AHI_TL_SUPPORT)
#if(LOCAL_NVDS == 0)
        case TASK_NVDS:
            id = TASK_ID_NVDS;
            break;
#endif
#ifdef BLE_AUDIO_AM0_TASK
        case TASK_AM0:
            id = TASK_ID_AM0;
            break;
#endif // BLE_AUDIO_AM0_TASK
        default: {
#if (BLE_PROFILES)
            // check if profile manager is able to retrieve the task id
            id = prf_get_id_from_task( task );
#endif // (BLE_PROFILES)
        }
        break;
    }

    return KE_BUILD_ID( id, idx );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
ke_task_id_t gapm_get_task_from_id_patch( ke_msg_id_t id )
{
    ke_task_id_t task = TASK_NONE;
    uint8_t idx = KE_IDX_GET( id );
    id = KE_TYPE_GET( id );
    switch( id ) {
        case TASK_ID_GAPM:
            task = TASK_GAPM;
            break;
        case TASK_ID_GAPC:
            task = TASK_GAPC;
            break;
        case TASK_ID_GATTM:
            task = TASK_GATTM;
            break;
        case TASK_ID_GATTC:
            task = TASK_GATTC;
            break;
        case TASK_ID_L2CC:
            task = TASK_L2CC;
            break;
#if (AHI_TL_SUPPORT)
        case TASK_ID_AHI:
            task = TASK_AHI;
            break;
#endif
        
#if(LOCAL_NVDS == 0)
        case TASK_ID_NVDS:
            task = TASK_NVDS;
            break;
#endif
        
#ifdef BLE_AUDIO_AM0_TASK
        case TASK_ID_AM0:
            task = TASK_AM0;
            break;
#endif
        
        default: {
#if (BLE_PROFILES)
            // check if profile manager is able to retrieve the task number
            task = prf_get_task_from_id( id );
#endif
            
        }
        break;
    }

    return ( ke_task_check( KE_BUILD_ID( task, idx ) ) );
};
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_task_id_patch()
{
    uint8_t patch_no[2];
    uint32_t code[2];
    if( patch_alloc( &patch_no[0] ) == false ) {
        BX_ASSERT( 0 );
    }
    code[0] = cal_patch_bl( GET_TASK_FROM_ID_PATCH_ADDR, ( uint32_t )GET_TASK_FROM_ID_PATCH - 1 );
    patch_entrance_exit_addr( patch_no[0], GET_TASK_FROM_ID_PATCH_ADDR, code[0] );
    PATCH_ENABLE( patch_no[0] );
    if( patch_alloc( &patch_no[1] ) == false ) {
        BX_ASSERT( 0 );
    }
    code[1] = cal_patch_bl( GET_ID_FROM_TASK_PATCH_ADDR, ( uint32_t )GET_ID_FROM_TASK_PATCH - 1 );
    patch_entrance_exit_addr( patch_no[1], GET_ID_FROM_TASK_PATCH_ADDR, code[1] );
    PATCH_ENABLE( patch_no[1] );
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
