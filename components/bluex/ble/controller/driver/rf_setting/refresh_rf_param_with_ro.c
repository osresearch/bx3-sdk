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
#include "bx_config.h"
#include "modem.h"
#include "rf_reg_typedef.h"

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
void refresh_rf_param_with_ro( uint32_t ro )
{
	if(ro <= 28)//binG12
    {
    	hwp_rf_reg->rf_reg_e.VCO_Current_for_TX			= 3;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX			= 2;
    }
    if((ro >=29) && (ro <= 40)) //bin34AB
    {
		hwp_rf_reg->rf_reg_e.VCO_Current_for_TX			= 4;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX			= 2;
    }
    if((ro >= 41) && (ro <= 46)) //binCD
    {
    	hwp_rf_reg->rf_reg_e.VCO_Current_for_TX			= 4;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX			= 3;
    }
    if((ro >= 47) && (ro <= 52)) //binEF
    {
    	hwp_rf_reg->rf_reg_e.VCO_Current_for_TX			= 5;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX			= 4;
    }
    if(ro >= 53)//binN/A
    {
    	hwp_rf_reg->rf_reg_e.VCO_Current_for_TX			= 5;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX			= 4;
    }
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
