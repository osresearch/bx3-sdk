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
#include "bx_drv_wdt.h"

/* includes ------------------------------------------------------------------*/

/* private define ------------------------------------------------------------*/
#define CHECK_HANDLE(hdl)                                   \
do{                                                         \
    if( (hdl) != BX_WDT ) {                                 \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

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
bx_err_t bx_drv_wdt_set_mode( void * hdl, u8 mode )
{
    CHECK_HANDLE( hdl );
    reg_wdt_t * BX_WDTx = ( reg_wdt_t * )hdl;

    BX_FIELD_WR( BX_WDTx->CTRL, WDT_CTRL_RMOD, mode );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_wdt_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_wdt_t * BX_WDTx = ( reg_wdt_t * )hdl;

    BX_CPU->SRST |= CPU_SRST_CLR_WDT_N;
    BX_CPU->SRST |= CPU_SRST_SET_WDT_N;

    BX_CPU->CLKG1 |= CPU_CLKG1_SET_WDT;

    BX_CLR_BIT( BX_WDTx->CTRL, WDT_CTRL_EN );

    BX_MODIFY_REG( BX_WDT->CTRL, WDT_CTRL_RST_PULSE_LEN, WDT_CTRL_RST_PULSE_LEN_T_4_PCLK_CYCLES );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_wdt_close( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_CPU->CLKG1 |= CPU_CLKG1_CLR_WDT;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_wdt_start( void * hdl, u32 time )
{
    CHECK_HANDLE( hdl );
    reg_wdt_t * BX_WDTx = ( reg_wdt_t * )hdl;

    BX_MODIFY_REG( BX_WDTx->TR, WDT_TR_PERIOD, time );
    BX_SET_BIT( BX_WDTx->CTRL, WDT_CTRL_EN );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_wdt_stop( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_wdt_t * BX_WDTx = ( reg_wdt_t * )hdl;

    BX_CLR_BIT( BX_WDTx->CTRL, WDT_CTRL_EN );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_wdt_feed( void * hdl )
{
    CHECK_HANDLE( hdl );
    
    BX_MODIFY_REG( BX_WDT->CR, WDT_CR_VAL, 0X76 );

    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



