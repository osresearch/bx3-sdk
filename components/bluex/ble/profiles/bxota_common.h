/**
 ****************************************************************************************
 *
 * @file bxota_common.h
 *
 * @brief Header File - Apollo BLE OTA common types.
 *
 * Copyright (C) Apollo 2015-2016
 *
 * 
 ****************************************************************************************
 */

#ifndef BXOTA_COMMON_H_
#define BXOTA_COMMON_H_
/**
 ****************************************************************************************
 * @addtogroup BXOTA Apollo BLE OTA Profile
 * @ingroup PROFILE
 * @brief Apollo BLE OTA Profile
 *
 * The Apollo BLE OTA Profile is used to update the software run on a server by transmitting
 * a new software binary over the air from a authenticated client.
 *
 * This file contains all definitions that are common for the server and the client parts
 * of the profile.
 *****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "rwble_hl_config.h"

/*
 * DEFINES
 ****************************************************************************************
 */

#define BXOTA_ATT_DATA_MAX_LENGTH (ATT_DEFAULT_MTU - 3)
#define BXOTA_ACK_MAP_SIZE (ATT_DEFAULT_MTU - 2)
/*
 * ENUMERATIONS
 ****************************************************************************************
 */

enum bxota_ctrl_pkt_type
{
    OTA_START_REQ,
    OTA_START_RSP,
    OTA_NEW_BLOCK_CMD,
    OTA_IMAGE_TRANSFER_FINISH_CMD,
};

enum bxota_firmware_destination_type
{
    LOCAL_FLASH,
    SERIAL_UART,
};

enum bxota_start_cfm_status
{
    OTA_REQ_ACCEPTED,
    OTA_REQ_REJECTED,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct __attribute__((packed))
{
    uint16_t segment_data_max_length;
    uint32_t image_content_crc32;
    uint32_t image_content_legnth;
}bxota_start_req_t;

typedef struct __attribute__((packed))
{
    uint8_t status;
    uint8_t ack_map_size;
}bxota_start_rsp_t;

typedef struct __attribute__((packed))
{
    uint16_t block_id;
}bxota_new_block_cmd_t;

typedef struct __attribute__((packed))
{
    uint8_t type;
    union __attribute__((packed)){
        bxota_start_req_t start_req;
        bxota_start_rsp_t start_rsp;
        bxota_new_block_cmd_t new_block;
    }u;
}bxota_ctrl_t;

typedef struct __attribute__((packed))
{
    uint8_t segment_id;
    uint8_t data[BXOTA_ATT_DATA_MAX_LENGTH - sizeof(uint8_t)];
}bxota_data_att_rx_t;

typedef struct __attribute__((packed))
{
    uint8_t ack_map[BXOTA_ACK_MAP_SIZE];
}bxota_data_att_read_t;

/// }@ BXOTA_COMMON

#endif // BXOTA_COMMON_H_

