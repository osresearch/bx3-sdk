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
#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "rwip_task.h"
#include "co_bt.h"
#include "ke_task.h"
#include "gapc_task.h"
#include "gapm_task.h"
#include "gattc_task.h"
#include "co_error.h"
#include "ke_timer.h"
#include "bx_kernel_timer.h"
#include "bx_kernel.h"
#include "app_dis.h"
/* config --------------------------------------------------------------------*/
#define APP_DEVICE_NAME_MAX_LEN         (18)
#define APP_IDX_MAX                     (1)

#define SPI_FIFO_DEPTH  2

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
/// States of APP task
enum appm_state_def {
    /// Initialization state
    APP_INIT,
    /// Database create state
    APP_CREATE_DB,
    /// Ready State
    APP_READY,
    /// Advertising state
    APP_ADVERTISING,
    /// Connected state
    APP_CONNECTED,
    /// Number of defined states.
    APP_STATE_MAX
};

struct app_env_tag {
    /// Connection handle
    uint16_t conhdl;
    /// Connection Index
    uint8_t  conidx;

    /// Last initialized profile
    uint8_t next_svc;

    /// Bonding status
    bool bonded;

    /// Device Name length
    uint8_t dev_name_len;
    /// Device Name
    uint8_t dev_name[APP_DEVICE_NAME_MAX_LEN];

    /// Local device IRK( Identity Resolving Key)
    uint8_t loc_irk[16];

    /// Secure Connections on current link
    bool sec_con_enabled;

    /// Counter used to generate IRK
    uint8_t rand_cnt;
};

typedef void ( *add_svc_func_t )( void );

enum bx_msg_user {
    BXM_USER_FIRST = BXM_FIRST_USER_MSG,

    BXM_USER_TIM0_INTR,
    BXM_USER_TRANSMIT_DATA,
    BXM_USER_RECEIVE_DATA_END,
};

enum user_spi_state {
    SPI_STA_NONE,
    SPI_STA_DEVICE_ID,
    SPI_STA_REG,
    SPI_STA_XYZ_R,
};

enum user_xyz_state {
    XYZ_STA_NONE,
    XYZ_STA_X_R_H,
    XYZ_STA_X_R_L,
    XYZ_STA_Y_R_H,
    XYZ_STA_Y_R_L,
    XYZ_STA_Z_R_H,
    XYZ_STA_Z_R_L,

};

struct user_service {
    s32 id;
    bool m_lock;
    u8 spi_state;
    u8 xyz_state;
};

/* exported variables --------------------------------------------------------*/
extern struct app_env_tag app_env;
extern const struct ke_state_handler appm_default_handler;
extern ke_state_t app_state[APP_IDX_MAX];
extern uint8_t m_tx_len ;
extern uint8_t m_rx_len ;
extern uint8_t * m_p_tx_buff ;
extern uint8_t * m_p_rx_buff ;


extern struct user_service us_svc;
/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void app_init( void );
void app_ble_init( void );
void app_on_ble_init( void );
bool app_add_svc( void );
void app_set_dev_cfg( struct gapm_set_dev_config_cmd * );
void app_on_ble_ready( void );
void app_on_ble_disconnect( void );
void app_on_ble_connect_fail( void );
uint8_t app_get_dev_name( uint8_t * name );
bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 );

#ifdef __cplusplus
}
#endif

#endif /* __USER_APP_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
