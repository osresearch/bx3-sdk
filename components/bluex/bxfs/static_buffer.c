
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
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/

#include "co_math.h"
#include "static_buffer.h"
#include "log.h"
#include "string.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static bool array_buf_hdl_sanity_check( static_buffer_t * buf_hdl, uint8_t * ptr );

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
void * array_buf_element_get( static_buffer_t * buf_hdl, uint16_t idx )
{
    BX_ASSERT( buf_hdl->buf_length > idx );
    if( buf_hdl->ref_cnt[idx] ) {
        return &buf_hdl->buf[buf_hdl->element_size * idx];
    } else {
        return NULL;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint16_t array_buf_idx_get( static_buffer_t * buf_hdl, void * ptr )
{
    BX_ASSERT( array_buf_hdl_sanity_check( buf_hdl, ptr ) );
    return ( ( uint8_t * )ptr - buf_hdl->buf ) / buf_hdl->element_size;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void * array_buf_alloc_idx( static_buffer_t * buf_hdl, uint16_t idx )
{
    BX_ASSERT( buf_hdl->ref_cnt[idx] == 0 );
    ++buf_hdl->ref_cnt[idx];
    --buf_hdl->remaining_size;
    return &buf_hdl->buf[idx * buf_hdl->element_size];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void * array_buf_calloc_idx( static_buffer_t * buf_hdl, uint16_t idx )
{
    void * ptr = array_buf_alloc_idx( buf_hdl, idx );
    if( ptr ) {
        memset( ptr, 0, buf_hdl->element_size );
    }
    return ptr;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void * array_buf_alloc( static_buffer_t * buf_hdl )
{
    uint16_t i;
    for( i = 0; i < buf_hdl->buf_length; ++i ) {
        if( buf_hdl->ref_cnt[i] == 0 ) {
            return array_buf_alloc_idx( buf_hdl, i );
        }
    }
    return NULL;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void * array_buf_calloc( static_buffer_t * buf_hdl )
{
    void * ptr = array_buf_alloc( buf_hdl );
    if( ptr ) {
        memset( ptr, 0, buf_hdl->element_size );
    }
    return ptr;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t array_buf_retain( static_buffer_t * buf_hdl, void * ptr )
{
    BX_ASSERT( array_buf_hdl_sanity_check( buf_hdl, ( uint8_t * )ptr ) );
    uint16_t i = ( ( uint8_t * )ptr - buf_hdl->buf ) / buf_hdl->element_size;
    BX_ASSERT( buf_hdl->ref_cnt[i] );
    return ++buf_hdl->ref_cnt[i];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t array_buf_ref_cnt( static_buffer_t * buf_hdl, void * ptr )
{
    BX_ASSERT( array_buf_hdl_sanity_check( buf_hdl, ( uint8_t * )ptr ) );
    uint16_t i = ( ( uint8_t * )ptr - buf_hdl->buf ) / buf_hdl->element_size;
    return buf_hdl->ref_cnt[i];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bool array_buf_hdl_sanity_check( static_buffer_t * buf_hdl, uint8_t * ptr )
{
    if( ( ptr - buf_hdl->buf ) % buf_hdl->element_size ) {
        return false;
    }
    if( ptr < buf_hdl->buf || ptr >= &buf_hdl->buf[buf_hdl->buf_length * buf_hdl->element_size] ) {
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
uint16_t array_buf_available_size( static_buffer_t * buf_hdl )
{
    return buf_hdl->remaining_size;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint16_t array_buf_element_size( static_buffer_t * buf_hdl )
{
    return buf_hdl->element_size;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool array_buf_has_element( static_buffer_t * buf_hdl, void * ptr )
{
    bool state = false;
    if( array_buf_hdl_sanity_check( buf_hdl, ptr ) ) { // addr in buf range
        uint16_t i = ( ( uint8_t * )ptr - buf_hdl->buf ) / buf_hdl->element_size;
        if( buf_hdl->ref_cnt[i] ) {
            state = true;
        }
    }
    return state;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool array_buf_release( static_buffer_t * buf_hdl, void * ptr )
{
    BX_ASSERT( array_buf_hdl_sanity_check( buf_hdl, ptr ) );
    uint16_t i = ( ( uint8_t * )ptr - buf_hdl->buf ) / buf_hdl->element_size;
    BX_ASSERT( buf_hdl->ref_cnt[i] );
    if( --buf_hdl->ref_cnt[i] == 0 ) {
        ++buf_hdl->remaining_size;
        return true;
    } else {
        return false;
    }
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
