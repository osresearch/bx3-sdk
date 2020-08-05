/** @}*/

/**
  ******************************************************************************
  * @file   :   .h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_DMAC_H__
#define __APP_DMAC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "periph_common.h"
#include "apollo_00_ble_reg.h"
#include "reg_dmac.h"
#include "co_utils.h"
#include "dmac_typedef.h"
#include "periph_error.h"

/* exported define -----------------------------------------------------------*/
#define DMAC_CHANNEL_NUM        6

/* exported types ------------------------------------------------------------*/
enum dw_dmac_device_chn {
    Dmac_Qspi_Tx    = 0,    
    Dmac_Qspi_Rx, // 0x1
    Dmac_SpiM0_Tx, // 0x2
    Dmac_SpiM0_Rx, // 0x3
    Dmac_SpiM1_Tx, // 0x4
    Dmac_SpiM1_Rx, // 0x5
    Dmac_SpiS_Tx, // 0x6
    Dmac_SpiS_Rx, // 0x7
    Dmac_Uart0_Tx, // 0x8
    Dmac_Uart0_Rx, // 0x9
    Dmac_Uart1_Tx, // 0xa
    Dmac_Uart1_Rx, // 0xb
    Dmac_Iic0_Tx, // 0xc
    Dmac_Iic0_Rx, // 0xd
    Dmac_Iic1_Tx, // 0xe
    Dmac_Iic1_Rx, // 0xf
};

enum dmac_sys_stat_config
{
    DMAC_INIT,
    DMAC_UNINIT,
    DMAC_TRANSFER_START,
    DMAC_TRANSFER_DONE,
};

typedef struct
{
    uint32_t size;
    void (*callback)(void *);
    void *callback_param;
}dmac_ch_env_t;

typedef struct
{
    dmac_ch_env_t *ch;
    uint8_t ch_num;
    uint8_t ch_stat;
}dmac_env_t;

typedef struct
{
    periph_inst_t inst;            /**< Peripheral common instance for DMAC.   */
    dmac_env_t env;                /**< DMAC operating environment.            */
    ble_reg_dmac_t *reg;               /**< DMAC register base address.            */
    uint8_t idx;                   /**< DMAC instance index.                   */
}app_dmac_inst_t;

typedef struct
{
    void (*callback)(void *);      /**< callback function pointer.             */
    void *callback_param;          /**< parameter pass to callback function.   */
    uint8_t *src;                  /**< source address.                        */
    uint8_t *dst;                  /**< destination address.                   */
    uint32_t length;               /**< transfer length,count by src_tr_width. */
    uint32_t src_tr_width:3,       /**< source transfer width.                 */
            dst_tr_width:3,        /**< destination transfer width.            */
            src_msize:3,           /**< source burst size.                     */
            dst_msize:3,           /**< destination burst size.                */
            tt_fc:3,               /**< transfer type and flow control.        */
            src_per:4,             /**< source hardware handshake.             */
            dst_per:4,             /**< destination hardware handshake.        */
            int_en:1;              /**< interrupt enable.                      */
}app_dmac_transfer_param_t;

/* exported variables --------------------------------------------------------*/
extern dmac_ch_env_t g_dmac_ch_env[DMAC_CHANNEL_NUM];

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define DMAC_INSTANCE(id)                                   \
{                                                           \
    .inst = {.init_func = app_dmac_init,},                  \
    .reg = (ble_reg_dmac_t *)REG_DMAC##id##_BASE,               \
    .env = {.ch = g_dmac_ch_env, .ch_num =DMAC_CHANNEL_NUM,}, \
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_qspi_rx_handshake_enum(uint8_t idx)
{
    return Dmac_Qspi_Rx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_qspi_tx_handshake_enum(uint8_t idx)
{
    return Dmac_Qspi_Tx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_uart_rx_handshake_enum(uint8_t idx)
{
    return idx ? Dmac_Uart1_Rx : Dmac_Uart0_Rx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_uart_tx_handshake_enum(uint8_t idx)
{
    return idx ? Dmac_Uart1_Tx : Dmac_Uart0_Tx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_spi_master_rx_handshake_enum(uint8_t idx)
{
    return idx ? Dmac_SpiM1_Rx : Dmac_SpiM0_Rx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_spi_master_tx_handshake_enum(uint8_t idx)
{
    return idx ? Dmac_SpiM1_Tx : Dmac_SpiM0_Tx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_spi_slave_rx_handshake_enum(uint8_t idx)
{
    return Dmac_SpiS_Rx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_spi_slave_tx_handshake_enum(uint8_t idx)
{
    return Dmac_SpiS_Tx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_iic_rx_handshake_enum(uint8_t idx)
{
    return idx ? Dmac_Iic1_Rx : Dmac_Iic0_Rx;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t dmac_iic_tx_handshake_enum(uint8_t idx)
{
    return idx ? Dmac_Iic1_Tx :Dmac_Iic0_Tx;
}

/* exported functions --------------------------------------------------------*/
uint16_t        dmac_get_max_block_transfer_size(void);
uint8_t         dmac_get_burst_transaction_size_enum(uint16_t msize);

periph_err_t    app_dmac_init(periph_inst_handle_t hdl);
periph_err_t    app_dmac_uninit(periph_inst_handle_t hdl);
periph_err_t    app_dmac_start(periph_inst_handle_t hdl,app_dmac_transfer_param_t *param,uint8_t *channel_idx);
periph_err_t    app_dmac_transfer_cancel(periph_inst_handle_t hdl,uint8_t ch_idx,uint32_t *remaining_size);
periph_err_t    app_dmac_transfer_wait(periph_inst_handle_t hdl,uint8_t ch_idx);
void            app_dmac_isr(app_dmac_inst_t *inst);

#ifdef __cplusplus
}
#endif

#endif /* __APP_DMAC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
