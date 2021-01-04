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
#include "queued_async_framework.h"
#include "log.h"
#include <string.h>

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint16_t queued_data_size( queued_async_framework_t * inst )
{
    uint16_t size = bx_ring_queue_element_size( inst->rq );
    if( inst->common_callback == NULL ) {
        size -= sizeof( queued_async_callback_t );
    }
    return size;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void copy_to_queue( uint8_t * dest, uint16_t element_size, va_list * param_list )
{
    void * data = va_arg( *param_list, void * );
    queued_async_callback_t cb = va_arg( *param_list, queued_async_callback_t );
    uint16_t data_size;
    if( NULL == cb ) {
        data_size = element_size;
    } else {
        data_size = element_size - sizeof( queued_async_callback_t );
        queued_async_callback_t * cb_buf = ( queued_async_callback_t * )&dest[data_size];
        *cb_buf = cb;
    }
    memcpy( dest, data, data_size );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint16_t priority_queued_data_size( priority_queued_async_framework_t * inst, bool high_priority )
{
    uint16_t size = bx_ring_queue_element_size( inst->rq[high_priority ? 1 : 0] );
    if( inst->common_callback == NULL ) {
        size -= sizeof( queued_async_callback_t );
    }
    return size;
}

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void * queued_async_process_get_current( queued_async_framework_t * inst )
{
    return bx_ring_queue_glance( inst->rq, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint16_t queued_async_process_get_amount( queued_async_framework_t * inst )
{
    return bx_ring_queue_amount( inst->rq );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool queued_async_process_start( queued_async_framework_t * inst, void * data, queued_async_callback_t cb )
{
    BX_ASSERT( cb && inst->common_callback == NULL || cb == NULL && inst->common_callback );
    bool empty = bx_ring_queue_empty( inst->rq );
    if( bx_ring_queue_full( inst->rq ) ) {
        LOG( LOG_LVL_ERROR, "async process queue full,inst:%x\n", inst );
        return false;
    }
    bx_enqueue_specific( inst->rq, copy_to_queue, data, cb );
    if( empty ) {
        inst->pre_process( queued_async_process_get_current( inst ) );
    }
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void queued_async_process_end( queued_async_framework_t * inst, void * cb_dummy, uint8_t cb_status )
{
    void * old = bx_dequeue( inst->rq );
    bool empty = bx_ring_queue_empty( inst->rq );
    queued_async_callback_t callback;
    if( inst->common_callback ) {
        callback = inst->common_callback;
    } else {
        uint8_t * buf = old;
        queued_async_callback_t * cb_buf = ( queued_async_callback_t * )&buf[queued_data_size( inst )];
        callback = *cb_buf;
    }
    callback( old, cb_dummy, cb_status );
    if( !empty ) {
        inst->pre_process( queued_async_process_get_current( inst ) );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void * priority_queued_async_process_get_current( priority_queued_async_framework_t * inst )
{
    return bx_ring_queue_glance( inst->rq[inst->current_high_priority ? 1 : 0], 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint16_t priority_queued_async_process_get_amount( priority_queued_async_framework_t * inst, bool high_priority )
{
    return bx_ring_queue_amount( inst->rq[high_priority ? 1 : 0] );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool priority_queued_async_process_start( priority_queued_async_framework_t * inst, bool high_priority, void * data, queued_async_callback_t cb )
{
    BX_ASSERT( cb && inst->common_callback == NULL || cb == NULL && inst->common_callback );
    bool empty = bx_ring_queue_empty( inst->rq[0] ) && bx_ring_queue_empty( inst->rq[1] );
    bool full = high_priority && bx_ring_queue_full( inst->rq[1] ) || high_priority == false && bx_ring_queue_full( inst->rq[0] );
    if( full ) {
        return false;
    }
    bx_enqueue_specific( inst->rq[high_priority ? 1 : 0], copy_to_queue, data, cb );
    if( empty ) {
        inst->current_high_priority = high_priority;
        inst->pre_process( priority_queued_async_process_get_current( inst ) );
    }
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void priority_queued_async_process_end( priority_queued_async_framework_t * inst, void * cb_dummy, uint8_t cb_status )
{
    void * old = bx_dequeue( inst->rq[inst->current_high_priority ? 1 : 0] );
    bool empty[2] = {
        [0] = bx_ring_queue_empty( inst->rq[0] ),
        [1] = bx_ring_queue_empty( inst->rq[1] )
    };
    queued_async_callback_t callback;
    if( inst->common_callback ) {
        callback = inst->common_callback;
    } else {
        uint8_t * buf = old;
        queued_async_callback_t * cb_buf = ( queued_async_callback_t * )&buf[priority_queued_data_size( inst, inst->current_high_priority )];
        callback = *cb_buf;
    }
    callback( old, cb_dummy, cb_status );
    if( !empty[1] ) {
        inst->current_high_priority = true;
        inst->pre_process( priority_queued_async_process_get_current( inst ) );
    } else if( !empty[0] ) {
        inst->current_high_priority = false;
        inst->pre_process( priority_queued_async_process_get_current( inst ) );
    }
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/




