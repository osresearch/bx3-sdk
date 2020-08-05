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
#include "periph_lock.h"
#include "ll.h"
#include "compiler_flag.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION bool periph_lock( periph_lock_t * periph_lock )
{
    bool retval = false;
    GLOBAL_INT_DISABLE();
    if( *periph_lock == false ) {
        *periph_lock = true;
        retval = true;
    }
    GLOBAL_INT_RESTORE();
    return retval;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION bool periph_unlock( periph_lock_t * periph_lock )
{
    bool retval = false;
    GLOBAL_INT_DISABLE();
    if( *periph_lock == true ) {
        *periph_lock = false;
        retval = true;
    }
    GLOBAL_INT_RESTORE();
    return retval;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION bool periph_lock_state_get( periph_lock_t * periph_lock )
{
    return *periph_lock;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

