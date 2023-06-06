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
#include "rf_power_set.h"
#include "rf_temp_adjust.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
extern temp_mode_t temp_mode;

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
void refresh_rf_param_with_ro_dcoff( uint32_t ro )
{
    if(ro <= 28)
    {
        RF_REG_e = 0x46FF648B;
    }
    else if((ro >= 29) && (ro <= 40))
    {
        RF_REG_e = 0x46FF6494;
    }
    else if((ro >= 41) && (ro <= 49))
    {
        RF_REG_e = 0x46FF649D;
    }
    else if(ro >= 50)
    {
        RF_REG_e = 0x46FF64A6;
    }
}

void refresh_rf_param_with_ro_dcon( uint32_t ro )
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            break;
        case MODE_BELOW0:
            if(ro <= 25)
            {
                RF_REG_e = 0x46FF77C9;
            }
            else if((ro >= 26) && (ro <= 34))
            {
                RF_REG_e = 0x46FF77D1;
            }
            else if((ro >= 35) && (ro <= 43))
            {
                RF_REG_e = 0x46FF77DA;
            }
            else if(ro >= 44)
            {
                RF_REG_e = 0x46FF77DB;
            }
        break;
        case MODE_NORMAL:
            //
        case MODE_OVER50:
            if(ro <= 22)
            {
                RF_REG_e = 0x46FF6489;
            }
            else if((ro >= 23) && (ro <= 34))
            {
                RF_REG_e = 0x46FF648B;
            }
            else if((ro >= 35) && (ro <= 40))
            {
                RF_REG_e = 0x46FF6495;
            }
            else if(ro >= 41)
            {
                RF_REG_e = 0x46FF649D;
            }
        break;
        default: break;
    }
}


void refresh_rf_param_with_ro( uint32_t ro )
{
    //4.2V
#ifdef RF_18_8_4V2_DCOFF_RF3V3_8dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
#ifdef RF_18_8_4V2_DCOFF_RF3V3_4dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
#ifdef RF_18_8_4V2_DCOFF_RF3V3_2dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
#ifdef RF_18_8_4V2_DCOFF_RF1V8_2dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
#ifdef RF_18_8_4V2_DCON_RF3V3_8dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCON_RF3V3_4dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCON_RF3V3_N2dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_2dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_0dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N2dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N5dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N10dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N15dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N20dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N30dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif

    //3.3V
#ifdef RF_18_8_3V3_DCOFF_RF3V3_8dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
#ifdef RF_18_8_3V3_DCOFF_RF3V3_4dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
#ifdef RF_18_8_3V3_DCOFF_RF3V3_2dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
#ifdef RF_18_8_3V3_DCOFF_RF1V8_2dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
#ifdef RF_18_8_3V3_DCON_RF3V3_8dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCON_RF3V3_4dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCON_RF3V3_N2dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_2dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_0dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N2dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N5dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N10dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N15dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N20dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N30dBm
    refresh_rf_param_with_ro_dcon(ro);
#endif

    //custom ------------------------------------------------------
    //2416 - 3.3V 32M
#ifdef RF_18_8_3V3_32M_DCOFF_RF3V3_SINGLE_3dBm
    refresh_rf_param_with_ro_dcoff(ro);
#endif
    //custom ------------------------------------------------------
}






/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
