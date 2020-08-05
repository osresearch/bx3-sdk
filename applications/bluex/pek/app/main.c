/**
  ******************************************************************************
  * @file   :   main.c
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
/* config ------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include <stdio.h>

/* include platform config  exp:apollo00 apollo01 */
//#include "apolloxx_cfg.h"


/* include board config  exp:EVK DVK */
//#include "board_cfg.h"


/* include component config exp:os fs ble */
//#include "component_cfg.h"


/* include device config exp: sensor module */
//#include "device_cfg.h"


/* include user.h */

#include "apollo_00_reg.h"
#include "bx_shell.h"

#include "led_demo.h"
#include "gpio_demo.h"
#include "pwm_demo.h"
#include "timer_demo.h"
#include "rtc_demo.h"

#include "iic_demo.h"
#include "wdt_demo.h"
#include "spim_demo.h"
#include "adc_demo.h"

#include "iic_lis3dsh_demo.h"
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
void init()
{
    __DMB();
    SCB->VTOR = APOLLO_00_VTOR_BASE;
    __DSB();

    //clk config

    //all clk enable
    BX_AWO->LCC |= AWO_LCC_32M_XTAL_EN;
    BX_AWO->LCC |= AWO_LCC_32K_XTAL_EN;
    BX_AWO->LCC |= AWO_LCC_32K_RCOSC_EN;
    BX_AWO->LCC |= AWO_LCC_REG_32M_RC_OSC_EN;

    //use 32m xtal 32K XTAL
    BX_MODIFY_REG( BX_AWO->LCC, AWO_LCC_32M_SRC_SEL, AWO_LCC_32M_SRC_SEL_T_XTAL );
    BX_MODIFY_REG( BX_AWO->LCC, AWO_LCC_32K_SRC_SEL, AWO_LCC_32K_SRC_SEL_T_XTAL );

    // set hbus clk = 32M XTAL
    BX_AWO->LCC |= AWO_LCC_32M_XTAL_EN;
    BX_MODIFY_REG( BX_AWO->LCC, AWO_LCC_32M_SRC_SEL, AWO_LCC_32M_SRC_SEL_T_XTAL );
    BX_MODIFY_REG( BX_AWO->MISC, AWO_MISC_CS_HBUS0, AWO_MISC_CS_HBUS0_T_32M );

    // set pbus clk = 32M/(15+1) = 2M
    BX_MODIFY_REG( BX_AWO->MISC, AWO_MISC_APB_CDP, 0XF );
    BX_AWO->CLKG1 |= AWO_CLKG1_APB_CDP_UP;

    // set ble mac clk = hbus clk
    BX_AWO->CLKG |= AWO_CLKG_CLR_BLE_MAC_DIV;
    BX_MODIFY_REG( BX_AWO->CLKG2, AWO_CLKG2_BLE_MAC_CS, AWO_CLKG2_BLE_MAC_CS_T_HBUS_CLK );
    BX_AWO->CLKG |= AWO_CLKG_SET_BLE_MAC_DIV;

    // set ble mdm clk = 32M clk
    BX_MODIFY_REG( BX_AWO->CLKG2, AWO_CLKG2_BLE_MDM_RX_SW_CS, AWO_CLKG2_BLE_MDM_RX_SW_CS_T_32M );

    __enable_irq();
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int main( void )
{
    init();

    bxsh_init();

    /* add user cmd */

    led_add_shell_cmd();
    gpio_add_shell_cmd();
    pwm_add_shell_cmd();
    tim_add_shell_cmd();
    rtc_add_shell_cmd();

    iic_add_shell_cmd();
    wdt_add_shell_cmd();
    spim_add_shell_cmd();

    iic_lis3dsh_add_shell_cmd();
    
    /* end of add user cmd */

    while( 1 ) {
        bxsh_run();
    }
}


/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



