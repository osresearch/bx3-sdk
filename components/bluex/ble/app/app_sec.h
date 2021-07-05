/**
 ****************************************************************************************
 *
 * @file app_sec.h
 *
 * @brief Application Security Entry Point
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP_SEC
 * @{
 ****************************************************************************************
 */

#ifndef APP_SEC_H_
#define APP_SEC_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"


#include <stdint.h>          // Standard Integer Definition
#include "bx_type_def.h"
/*
 * DEFINES
 ****************************************************************************************
 */
#define APP_SEC_OFFSET              0x802000
#define FLASH_SIZE                  256
#define APP_SEC_BOND_STATE_OFFSET   16
#define APP_SEC_BD_ADDR_OFFSET      32
#define APP_SEC_MOUSE_NTF_OFFSET    48
#define APP_SEC_LTK_OFFSET          64
#define APP_SEC_PEER_IRK_OFFSET     96

#define CONN_INTERVAL_MIN   10//20//40//  // Unit:1.25ms
#define CONN_INTERVAL_MAX   40//40//20//40//   // Unit:1.25ms
#define SLAVE_LATENCY       24//20//48//10//
#define CONN_TIMEOUT        600//1100//500//1500//800// //unit:10ms

/*
 * STRUCTURES DEFINITIONS
 ****************************************************************************************
 */

struct app_sec_env_tag {
    // Bond status
    bool bonded;
    u8 sec_ltk[32];
    u8 peer_irk[32];
    u8 bdaddr[8];
};



/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

/// Application Security Environment
extern struct app_sec_env_tag app_sec_env;

/// Table of message handlers
extern const struct ke_state_handler app_sec_table_handler;

extern char mouse_ntf[];
/*
 * GLOBAL FUNCTIONS DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize the Application Security Module
 ****************************************************************************************
 */
void app_sec_init(void);
bool app_sec_get_bond_status( void );

#if (NVDS_SUPPORT)
/**
 ****************************************************************************************
 * @brief Remove all bond data stored in NVDS
 ****************************************************************************************
 */
void app_sec_remove_bond(void);
#endif //(NVDS_SUPPORT)

/**
 ****************************************************************************************
 * @brief Send a security request to the peer device. This function is used to require the
 * central to start the encryption with a LTK that would have shared during a previous
 * bond procedure.
 *
 * @param[in]   - conidx: Connection Index
 ****************************************************************************************
 */
void app_sec_send_security_req(uint8_t conidx);

//#endif //(BLE_APP_SEC)

#endif // APP_SEC_H_

/// @} APP_SEC
