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
#if ( RF_PARAM == 2 )
    if( ( ro >= 0 ) && ( ro <= 28 ) ) {

        set_vco_buff_others( 0x78f, 0x78e, 0x78e );
        set_vco_buff_aa55( 0x811, 0x810, 0x810 );

        hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage  = 0;
        hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage  = 1;
        hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_TX         = 2;
        hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX  = 2;
        hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX         = 2;
        hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX  = 2;
    }
    if( ( ro >= 29 ) && ( ro <= 40 ) ) { 

        set_vco_buff_others( 0x78f, 0x78e, 0x78e );
        set_vco_buff_aa55( 0x811, 0x810, 0x810 );

        hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage  = 0;
        hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage  = 1;
        hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_TX         = 3;
        hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX  = 1;
        hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX         = 2;
        hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX  = 2;
    }
    if( ( ro >= 41 ) && ( ro <= 52 ) ) { 

        set_vco_buff_others( 0x78f, 0x78e, 0x78e );
        set_vco_buff_aa55( 0x811, 0x810, 0x810 );

        hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage  = 0;
        hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage  = 1;
        hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 2;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_TX         = 3;
        hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX  = 5;
        hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 7;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX         = 3;
        hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX  = 2;
    }
    enable_vco_value( false );
    
#elif ( RF_PARAM == 3 )
    if( ro <= 28 ) { 
        set_vco_buff_others( 0x78f, 0x78e, 0x78e );
        set_vco_buff_aa55( 0x811, 0x810, 0x810 );
        hwp_rf_reg->rf_reg_e.VCO_Current_for_TX         = 3;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX         = 2;

        if( MAIN_CLOCK > 32000000 ) {
            hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
        }

    }
    if( ( ro >= 29 ) && ( ro <= 40 ) ) { 
        set_vco_buff_others( 0x78f, 0x78e, 0x78e );
        set_vco_buff_aa55( 0x811, 0x810, 0x810 );
        hwp_rf_reg->rf_reg_e.VCO_Current_for_TX         = 4;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX         = 2;

        if( MAIN_CLOCK > 32000000 ) {
            hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
        }
    }
    if( ( ro >= 41 ) && ( ro <= 46 ) ) {
        set_vco_buff_others( 0x810, 0x78f, 0x78f );
        set_vco_buff_aa55( 0x812, 0x811, 0x811 );
        hwp_rf_reg->rf_reg_e.VCO_Current_for_TX         = 4;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX         = 3;
    }
    if( ( ro >= 47 ) && ( ro <= 52 ) ) {
        set_vco_buff_others( 0x810, 0x78f, 0x78f );
        set_vco_buff_aa55( 0x812, 0x811, 0x811 );
        hwp_rf_reg->rf_reg_e.VCO_Current_for_TX         = 5;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX         = 4;
    }
    if( ro >= 53 ) {
        set_vco_buff_others( 0x810, 0x78f, 0x78f );
        set_vco_buff_aa55( 0x812, 0x811, 0x811 );
        hwp_rf_reg->rf_reg_e.VCO_Current_for_TX         = 5;
        hwp_rf_reg->rf_reg_e.VCO_Current_for_RX         = 4;
    }
    enable_vco_value( false );
	
#elif (RF_PARAM == 1)

#endif /* ( RF_PARAM == 2 ) */
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
