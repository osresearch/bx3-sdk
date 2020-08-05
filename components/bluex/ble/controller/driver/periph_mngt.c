
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
#include <stddef.h>
#include "periph_mngt.h"
#include "log.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
periph_inst_handle_t periph_domain_recovery_buf[PERIPH_DOMAIN_MAX];
periph_inst_handle_t cpu_domain_recovery_buf[CPU_DOMAIN_MAX];

periph_domain_stat_t periph_domain_stat;
cpu_domain_stat_t cpu_domain_stat;

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bool is_all_zero( uint8_t * src, uint32_t size )
{
    while( size-- ) {
        if( src[size] ) {
            return false;
        }
    }
    return true;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool periph_domain_busy( void )
{
    return is_all_zero( ( uint8_t * )&periph_domain_stat, sizeof( periph_domain_stat ) ) ? false : true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool cpu_domain_busy( void )
{
    return is_all_zero( ( uint8_t * )&cpu_domain_stat, sizeof( cpu_domain_stat ) ) ? false : true;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
