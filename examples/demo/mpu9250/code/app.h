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

#define MPU9250_WHO_AM_I_DEFAULT_VALUE		0x71
#define AK8963_WHO_AM_I_DEFAULT_VALUE     0x48
#define I2C_SLV0_EN					0x27
/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
/// States of APP task
enum appm_state_def
{
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

enum magn_op_mode {
	POWER_DOWN_MODE = 0,   				// Power to almost all internal circuits is turned off.
	SINGLE_MEASUREMENT_MODE,       		// Sensor is measured, and after sensor measurement and signal processing is finished, measurement data is stored to measurement data registers (HXL to HZH), then AK8963 transits to power-down mode automatically.
	CONTINUOUS_MEASUREMENT_8Hz_MODE,      //  Sensor is measured periodically at 8Hz
	EXTERNAL_TRIGGER_MODE = 4,       	// When external trigger measurement mode is set, AK89xx waits for trigger input. When a pulse is input from TRG pin, sensor measurement is started on the rising edge of TRG pin.
	CONTINUOUS_MEASUREMENT_100Hz_MODE = 6,  //  Sensor is measured periodically at 100Hz
	SELF_TEST_MODE = 8,					// Self-test mode is used to check if the sensor is working normally
	FUSE_ROM_ACCESS_MODE = 0xFF			// Fuse ROM access mode is used to read Fuse ROM data. Sensitivity adjustment data for each axis is stored in fuse ROM.
};

struct app_env_tag
{
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

/* exported variables --------------------------------------------------------*/
extern struct app_env_tag app_env;
extern const struct ke_state_handler appm_default_handler;
extern ke_state_t app_state[APP_IDX_MAX];

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

#ifdef __cplusplus
}
#endif

#endif /* __USER_APP_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
