/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  * 此文档尚未做完整，比如enable的时候，需要判断是否已经被前面的使能过，如果被使
  * 能，需要先disable相应功能，然后再重新使能，但现在还没做
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* includes ------------------------------------------------------------------*/
#include "bx_drv_io_mux.h"

/* includes ------------------------------------------------------------------*/

/* private define ------------------------------------------------------------*/

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
bx_err_t bx_drv_iomux_set_all_default( void )
{
    *( u32 * )0x20132020 = 0;
    *( u32 * )0x20132024 = 0;
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
* @note    :enable 尚为把前面的使能去除，容易发生bug，以后再修复
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_iomux_af_enable( u8 enable_type )
{
    switch( enable_type ) {
        case QSPI_EN0:
            *( u32 * )0x20132020 |= ( 0x01UL << 0 );
            break;
        case QSPI_EN1:
            *( u32 * )0x20132020 |= ( 0x01UL << 1 );
            break;
        case QSPI_EN2:
            *( u32 * )0x20132020 |= ( 0x01UL << 2 );
            break;
        case QSPI_EN3:
            *( u32 * )0x20132020 |= ( 0x01UL << 3 );
            break;

        case GPIO00_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 9 );
            break;

        case GPIO01_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 10 );
            break;

        case SPIM0_CS1_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 5 );
            break;

        case SPIM0_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 4 );
            break;

        case SPIM1_CS1_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 7 );
            break;

        case SPIM1_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 6 );
            break;

        case GPIO14_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 11 );
            break;

        case GPIO15_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 12 );
            break;

        case SPIS_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 8 );
            break;

        case RFIF_EN:
            *( u32 * )0x20132020 |= ( 0x01UL << 13 );
            break;

        case BLE_MAC_DBG_EN0:
        case BLE_MAC_DBG_EN1:
        case BLE_MAC_DBG_EN2:
        case BLE_MAC_DBG_EN3:
        case BLE_MAC_DBG_EN4:
        case BLE_MAC_DBG_EN5:
        case BLE_MAC_DBG_EN6:
        case BLE_MAC_DBG_EN7:
            *( u32 * )0x20132020 |= ( 0x01UL << ( 16 + enable_type - BLE_MAC_DBG_EN0 ) );
            break;

        case FUNC_IO_EN00:
        case FUNC_IO_EN01:
        case FUNC_IO_EN02:
        case FUNC_IO_EN03:
        case FUNC_IO_EN04:
        case FUNC_IO_EN05:
        case FUNC_IO_EN06:
        case FUNC_IO_EN07:
        case FUNC_IO_EN08:
        case FUNC_IO_EN09:
        case FUNC_IO_EN10:
        case FUNC_IO_EN11:
        case FUNC_IO_EN12:
        case FUNC_IO_EN13:
        case FUNC_IO_EN14:
        case FUNC_IO_EN15:
        case FUNC_IO_EN16:
        case FUNC_IO_EN17:
        case FUNC_IO_EN18:
        case FUNC_IO_EN19:
        case FUNC_IO_EN20:
        case FUNC_IO_EN21:
            *( u32 * )0x20132024 |= ( 0x01UL << ( enable_type - FUNC_IO_EN00 ) );
            break;

        default:
            return BX_ERR_INVAL;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_iomux_af_disable( u8 enable_type )
{
    switch( enable_type ) {
        case QSPI_EN0:
            *( u32 * )0x20132020 &= ~( 0x01UL << 0 );
            break;
        case QSPI_EN1:
            *( u32 * )0x20132020 &= ~( 0x01UL << 1 );
            break;
        case QSPI_EN2:
            *( u32 * )0x20132020 &= ~( 0x01UL << 2 );
            break;
        case QSPI_EN3:
            *( u32 * )0x20132020 &= ~( 0x01UL << 3 );
            break;

        case GPIO00_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 9 );
            break;

        case GPIO01_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 10 );
            break;

        case SPIM0_CS1_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 5 );
            break;

        case SPIM0_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 4 );
            break;

        case SPIM1_CS1_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 7 );
            break;

        case SPIM1_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 6 );
            break;

        case GPIO14_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 11 );
            break;

        case GPIO15_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 12 );
            break;

        case SPIS_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 8 );
            break;

        case RFIF_EN:
            *( u32 * )0x20132020 &= ~( 0x01UL << 13 );
            break;

        case BLE_MAC_DBG_EN0:
        case BLE_MAC_DBG_EN1:
        case BLE_MAC_DBG_EN2:
        case BLE_MAC_DBG_EN3:
        case BLE_MAC_DBG_EN4:
        case BLE_MAC_DBG_EN5:
        case BLE_MAC_DBG_EN6:
        case BLE_MAC_DBG_EN7:
            *( u32 * )0x20132020 &= ~( 0x01UL << ( 16 + enable_type - BLE_MAC_DBG_EN0 ) );
            break;

        case FUNC_IO_EN00:
        case FUNC_IO_EN01:
        case FUNC_IO_EN02:
        case FUNC_IO_EN03:
        case FUNC_IO_EN04:
        case FUNC_IO_EN05:
        case FUNC_IO_EN06:
        case FUNC_IO_EN07:
        case FUNC_IO_EN08:
        case FUNC_IO_EN09:
        case FUNC_IO_EN10:
        case FUNC_IO_EN11:
        case FUNC_IO_EN12:
        case FUNC_IO_EN13:
        case FUNC_IO_EN14:
        case FUNC_IO_EN15:
        case FUNC_IO_EN16:
        case FUNC_IO_EN17:
        case FUNC_IO_EN18:
        case FUNC_IO_EN19:
        case FUNC_IO_EN20:
        case FUNC_IO_EN21:
            *( u32 * )0x20132024 &= ~( 0x01UL << ( enable_type - FUNC_IO_EN00 ) );
            break;

        default:
            return BX_ERR_INVAL;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t set_general_io( u8 pin_num, u8 type )
{
    switch( pin_num ) {
        case 0:
            bx_drv_iomux_af_enable( GPIO00_EN );
            break;
        case 1:
            bx_drv_iomux_af_enable( GPIO01_EN );
            break;

        case 2:
            bx_drv_iomux_af_disable( FUNC_IO_EN00 );
            bx_drv_iomux_af_disable( SPIM0_CS1_EN );
            break;

        case 3:
            bx_drv_iomux_af_disable( FUNC_IO_EN01 );
            bx_drv_iomux_af_disable( SPIM0_EN );
            bx_drv_iomux_af_disable( SPIS_EN );
            break;

        case 4:
            bx_drv_iomux_af_disable( FUNC_IO_EN02 );
            bx_drv_iomux_af_disable( SPIM0_EN );
            bx_drv_iomux_af_disable( SPIS_EN );
            break;

        case 5:
            bx_drv_iomux_af_disable( FUNC_IO_EN03 );
            bx_drv_iomux_af_disable( SPIM0_EN );
            bx_drv_iomux_af_disable( SPIS_EN );
            break;

        case 6:
            bx_drv_iomux_af_disable( FUNC_IO_EN04 );
            bx_drv_iomux_af_disable( SPIM0_EN );
            bx_drv_iomux_af_disable( SPIS_EN );
            break;

        case 7:
            bx_drv_iomux_af_disable( FUNC_IO_EN05 );
            bx_drv_iomux_af_disable( BLE_MAC_DBG_EN0 );
            bx_drv_iomux_af_disable( SPIM1_CS1_EN );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;

        case 8:
            bx_drv_iomux_af_disable( SPIM1_EN );
            bx_drv_iomux_af_disable( BLE_MAC_DBG_EN1 );
            bx_drv_iomux_af_disable( FUNC_IO_EN06 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 9:
            bx_drv_iomux_af_disable( SPIM1_EN );
            bx_drv_iomux_af_disable( BLE_MAC_DBG_EN2 );
            bx_drv_iomux_af_disable( FUNC_IO_EN07 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 10:
            bx_drv_iomux_af_disable( SPIM1_EN );
            bx_drv_iomux_af_disable( BLE_MAC_DBG_EN3 );
            bx_drv_iomux_af_disable( FUNC_IO_EN08 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 11:
            bx_drv_iomux_af_disable( SPIM1_EN );
            bx_drv_iomux_af_disable( BLE_MAC_DBG_EN4 );
            bx_drv_iomux_af_disable( FUNC_IO_EN09 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;

        /* 根据《pin_share.docx》，GPIO14_EN\GPIO15_EN 实际对应 P12 P13 */
        case 12:
            bx_drv_iomux_af_enable( GPIO14_EN );
            break;
        case 13:
            bx_drv_iomux_af_enable( GPIO15_EN );
            break;
        case 14:
            bx_drv_iomux_af_disable( BLE_MAC_DBG_EN7 );
            bx_drv_iomux_af_disable( FUNC_IO_EN12 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;

        case 15:
            bx_drv_iomux_af_disable( FUNC_IO_EN13 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;

        case 16:
            bx_drv_iomux_af_disable( FUNC_IO_EN14 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;

        case 17:
            bx_drv_iomux_af_disable( FUNC_IO_EN15 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 18:
            bx_drv_iomux_af_disable( FUNC_IO_EN16 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 19:
            bx_drv_iomux_af_disable( FUNC_IO_EN17 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 20:
            bx_drv_iomux_af_disable( FUNC_IO_EN18 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 21:
            bx_drv_iomux_af_disable( FUNC_IO_EN19 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 22:
            bx_drv_iomux_af_disable( FUNC_IO_EN20 );
            bx_drv_iomux_af_disable( RFIF_EN );
            break;
        case 23:
            bx_drv_iomux_af_disable( FUNC_IO_EN21 );
            break;

        case 24:
        case 25:
        case 26:
            bx_drv_iomux_af_disable( QSPI_EN0 );
            break;

        case 27:
            bx_drv_iomux_af_disable( QSPI_EN1 );
            break;

        case 28:
            bx_drv_iomux_af_disable( QSPI_EN2 );
            break;

        case 29:
            bx_drv_iomux_af_disable( QSPI_EN3 );
            break;

        case 30:
        case 31:
            break;


        default:
            return BX_ERR_INVAL;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t set_func_io_pin( u8 pin_num, u8 pin_type )
{
    if( pin_num > 23 || pin_num < 2 ) {
        return BX_ERR_INVAL;
    }

    u32 value = pin_type - BX_PIN_TYPE_UART0_TX;
    u8 af_enable = pin_num - 2 + FUNC_IO_EN00;
    bx_drv_iomux_af_enable( af_enable );

    u32 addr = 0x20132030 + ( pin_num / 8 ) * 4;

    *( u32 * ) addr |= value << ( ( ( pin_num - 2 ) % 8 ) * 4 );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_iomux_set_pin_type( u8 pin_num, u8 pin_type )
{
    switch( pin_type ) {
        case BX_PIN_TYPE_GENERAL_IO:
            return set_general_io( pin_num, pin_type );

//        case BX_PIN_TYPE_QSPI_NCS:
//        case BX_PIN_TYPE_QSPI_CLK:
//        case BX_PIN_TYPE_QSPI_DATA0:
//        case BX_PIN_TYPE_QSPI_DATA1:
//        case BX_PIN_TYPE_QSPI_DATA2:
//        case BX_PIN_TYPE_QSPI_DATA3:
//            return set_qspi_pin( pin_num, type );

//        case BX_PIN_TYPE_SWCK:
//        case BX_PIN_TYPE_SWD:
//            return set_debug_pin( pin_num, type );

//        case BX_PIN_TYPE_SPIM0_CS1:
//        case BX_PIN_TYPE_SPIM0_CS0:
//        case BX_PIN_TYPE_SPIM0_CLK:
//        case BX_PIN_TYPE_SPIM0_MISO:
//        case BX_PIN_TYPE_SPIM0_MOSI:
//            return set_spim0_pin( pin_num, type );

//        case BX_PIN_TYPE_SPIM1_CS1:
//        case BX_PIN_TYPE_SPIM1_CS0:
//        case BX_PIN_TYPE_SPIM1_CLK:
//        case BX_PIN_TYPE_SPIM1_MISO:
//        case BX_PIN_TYPE_SPIM1_MOSI:
//            return set_spim1_pin( pin_num, type );

//        case BX_PIN_TYPE_SPIS_CS:
//        case BX_PIN_TYPE_SPIS_CLK:
//        case BX_PIN_TYPE_SPIS_MISO:
//        case BX_PIN_TYPE_SPIS_MOSI:
//            return set_spis_pin( pin_num, type );


//        case BX_PIN_TYPE_BLE_MAC_DBG0:
//        case BX_PIN_TYPE_BLE_MAC_DBG1:
//        case BX_PIN_TYPE_BLE_MAC_DBG2:
//        case BX_PIN_TYPE_BLE_MAC_DBG3:
//        case BX_PIN_TYPE_BLE_MAC_DBG4:
//        case BX_PIN_TYPE_BLE_MAC_DBG5:
//        case BX_PIN_TYPE_BLE_MAC_DBG6:
//        case BX_PIN_TYPE_BLE_MAC_DBG7:
//            return set_ble_mac_dbg_pin( pin_num, type );

//        case BX_PIN_TYPE_RFIF_CLK:
//        case BX_PIN_TYPE_RFIF_RX0:
//        case BX_PIN_TYPE_RFIF_RX1:
//        case BX_PIN_TYPE_RFIF_TX0:
//        case BX_PIN_TYPE_RFIF_TX1:
//        case BX_PIN_TYPE_RFIF_TX2:
//        case BX_PIN_TYPE_RFIF_TX3:
//        case BX_PIN_TYPE_RFIF_TX4:
//        case BX_PIN_TYPE_RFIF_TX5:
//        case BX_PIN_TYPE_RFIF_TX6:
//        case BX_PIN_TYPE_RFIF_TX7:
//        case BX_PIN_TYPE_RFIF_TX8:
//        case BX_PIN_TYPE_RFIF_TX9:
//        case BX_PIN_TYPE_RFIF_TX10:
//        case BX_PIN_TYPE_RFIF_TX11:
//            return set_rfif_pin( pin_num, type );

        case BX_PIN_TYPE_UART0_TX:
        case BX_PIN_TYPE_UART0_RX:
        case BX_PIN_TYPE_UART0_CTS:
        case BX_PIN_TYPE_UART0_RTS:
        case BX_PIN_TYPE_UART1_TX:
        case BX_PIN_TYPE_UART1_RX:
        case BX_PIN_TYPE_IIC0_SCL:
        case BX_PIN_TYPE_IIC0_SDA:
        case BX_PIN_TYPE_IIC1_SCL:
        case BX_PIN_TYPE_IIC1_SDA:
        case BX_PIN_TYPE_PWM0:
        case BX_PIN_TYPE_PWM1:
        case BX_PIN_TYPE_PWM2:
        case BX_PIN_TYPE_PWM3:
        case BX_PIN_TYPE_PWM4:
            return set_func_io_pin( pin_num, pin_type );

        default:
            return BX_ERR_INVAL;
    }
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



