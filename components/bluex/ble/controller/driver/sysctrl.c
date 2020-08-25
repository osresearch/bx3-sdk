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
#include "sysctrl.h"
#include "rf_reg_settings.h"
#include "reg_sysc_cpu.h"
#include "reg_sysc_cpu_apollo_00.h"
#include "awo_apollo_00.h"
#include "plf.h"
#include "clk_gate.h"
#include "log.h"
#include "compiler_flag.h"
#include "ll.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static bool pwr_pwm_2 = false;

io_mngt_t io_mngt = {
    .active_ie = 0x3,
#if (defined(DEBUGGER_ATTACHED)&&(DEBUGGER_ATTACHED==1))
    .deep_sleep_ie = 0x3,
#endif
};

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
void sysctrl_pwr_3v2_drv_capability_maintain( bool enable )
{
    pwr_pwm_2 = enable;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION bool sysctrl_pwr_pwm_2_sleep_en_get()
{
    return pwr_pwm_2;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void sysctrl_io_config_mask( uint32_t mask, uint32_t config )
{
    GLOBAL_INT_DISABLE();
    if( config & NORMAL_MODE_IE ) {
        io_mngt.active_ie |= mask;
    } else {
        io_mngt.active_ie &= ~mask;
    }
    if( config & SLEEP_MODE_IE ) {
        io_mngt.deep_sleep_ie |= mask;
    } else {
        io_mngt.deep_sleep_ie &= ~mask;
    }
    if( config & UTILITY_IO_EN ) {
        io_mngt.util_io_mask |= mask;
    } else {
        io_mngt.util_io_mask &= ~mask;
    }
    if( config & SLEEP_RET_OUT_EN ) {
        io_mngt.util_io_ret_dir |= mask;
    } else {
        io_mngt.util_io_ret_dir &= ~mask;
    }
    if( config & SLEEP_RET_OUT_H ) {
        io_mngt.util_io_ret_val |= mask;
    } else {
        io_mngt.util_io_ret_val &= ~mask;
    }

    sysc_awo_gpio_ie_set( io_mngt.active_ie );
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void sysctrl_io_config( uint8_t num, uint32_t config )
{
    sysctrl_io_config_mask( 1 << num, config );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_awo_clk_gate_init()
{
    ble_clk_gate_awo( BLE_AWO_CLKG_CLR_MDM_RX_DIV );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_awo_modem_clk_init()
{
    sysc_awo_clk_sel_ble_mdm_rx_sw_setf( 1 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_awo_pd_onoff_sw( uint16_t sel, uint8_t sw )
{
    uint32_t pd_state;
    uint32_t pd_state_ori;

    if( sw == PD_POWER_ON ) {
        pd_state_ori = sysc_awo_reg_pd_onoff_get();
        pd_state = ( pd_state_ori & 0xFFFF ) | ( sel << 16 );
        sysc_awo_reg_pd_onoff_set( pd_state );
    } else if( sw == PD_POWER_DOWN ) {
        pd_state_ori = sysc_awo_reg_pd_onoff_get();
        pd_state = ( pd_state_ori & 0xFFFF0000 ) | sel;
        sysc_awo_reg_pd_onoff_set( pd_state );
        sysc_awo_o_sram_retention_req_setf( ~( sel & 0x7f ) );
    } else {
        BX_ASSERT( ( ( sw == PD_POWER_ON ) || ( sw == PD_POWER_DOWN ) ) );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_awo_power_domain_ctrl_init()
{
    sysctrl_awo_pd_onoff_sw( PD_PER | PD_BLE_MAC, PD_POWER_DOWN );
    sysctrl_awo_pd_onoff_sw( PD_PER | PD_BLE_MAC | PD_SRAM0 | PD_SRAM1 | PD_SRAM2 | PD_SRAM3 | PD_SRAM4 | PD_SRAM5 | PD_SRAM6, PD_POWER_ON );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_awo_set_sram_retention_vdd()
{
#if ((VDD_SRAM_SLEEP_MILLIVOLT >= 600) && (VDD_SRAM_SLEEP_MILLIVOLT <= 950)\
        && !(VDD_SRAM_SLEEP_MILLIVOLT % 50))
    uint8_t vdd_awo_sram = ( VDD_SRAM_SLEEP_MILLIVOLT - 600 ) / 50;
    sysc_awo_o_sram_retention_vdd_setf( vdd_awo_sram );
#else
#error "Error VDD_SRAM_SLEEP_MILIVOLT!!!";
#endif

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void sysctrl_io_init()
{
    sysc_awo_gpio_ps_set( 0x0 );
    sysc_awo_gpio_pe_set( 0x3 );
    sysc_awo_gpio_ie_set( 0x3 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_awo_init()
{
    sysctrl_awo_clk_gate_init();
    sysctrl_awo_modem_clk_init();
    sysctrl_awo_power_domain_ctrl_init();
    sysc_awo_o_ldo_setup_time_setf( 0xc0 );
    sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
    sysctrl_awo_set_sram_retention_vdd();
    sysc_awo_pwr_pwm_ctrl_set( 0x100 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_close_32m_rc()
{
    sysc_awo_dr_16m_rcosc_en_setf( 1 );
    sysc_awo_reg_16m_rcosc_en_setf( 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_close_32m_xtal()
{
    sysc_awo_o_16m_xtal_en_setf( 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_32k_clk_init()
{
    sysc_awo_o_32k_xtal_en_setf( 1 );
    BX_DELAY_US( 60 * 1000 );
    sysc_awo_o_ana_32k_selxtal_setf( 1 );
    BX_DELAY_US( 150 );
    sysc_awo_o_32k_rcosc_en_setf( 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void sysctrl_set_ahb_apb_blemac_clk()
{
    ble_clk_gate_awo( BLE_AWO_CLKG_CLR_HBUS_DIV_16M | BLE_AWO_CLKG_CLR_HBUS_DIV_PLL );
    switch( AHB_CLK ) {
        case CRYSTAL_CLK:
            sysc_awo_o_clk_sel_hbus0_setf( 1 );
            sysc_awo_clk_sel_ble_mac_setf( 1 );
            sysc_awo_clk_div_ble_mac_para0_m1_setf( 1 );
            break;
        case CRYSTAL_CLK/2:
            sysc_awo_clk_div_hbus_para_m1_setf( 0 );
            sysc_awo_o_clk_sel_hbus1_setf( 0 );
            ble_clk_gate_awo( BLE_AWO_CLKG_SET_HBUS_DIV_16M );
            sysc_awo_o_clk_sel_hbus0_setf( 2 );
            sysc_awo_clk_sel_ble_mac_setf( 0 );
            break;
        case 96000000:
            reg_set_pll( PLL_96M );
            reg_pll_enable( 1 );
            reg_wait_pll_stable();
            sysc_awo_o_clk_sel_hbus1_setf( 2 );
            ble_clk_gate_awo( BLE_AWO_CLKG_SET_HBUS_DIV_PLL );
            sysc_awo_o_clk_sel_hbus0_setf( 2 );
            sysc_awo_clk_sel_ble_mac_setf( 1 );
            sysc_awo_clk_div_ble_mac_para0_m1_setf( 5 );
            break;
        default:
            LOG( LOG_LVL_ERROR, "ahb freq not implemented in sw" );
            BX_ASSERT( 0 );
            break;
    }
    sysc_awo_clk_div_pbus_para_m1_setf( 0 );
    sysc_awo_clkgen_awo_signal_1_set( 0x3 );
    sysc_cpu_ble_freq0_setf( 16 );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

