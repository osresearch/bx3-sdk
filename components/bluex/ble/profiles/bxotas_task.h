/**
 ****************************************************************************************
 *
 * @file bxotas_task.h
 *
 * @brief Header file - BXOTASTASK.
 *
 * Copyright (C) Apollo 2015-2016
 *
 *
 ****************************************************************************************
 */

#ifndef BXOTAS_TASK_H_
#define BXOTAS_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup BXOTASTASK Task
 * @ingroup BXOTAS
 * @brief Apollo BLE OTA Server Task
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "rwip_task.h" // Task definitions
#include "prf_types.h"
#include "bxota_common.h"

enum bxotas_msg_id
{
    BXOTAS_FIRMWARE_DEST_CMD = TASK_FIRST_MSG(TASK_ID_BXOTAS),
    BXOTAS_START_REQ_IND,
    BXOTAS_START_CFM,
    BXOTAS_NEW_BLOCK_IND,
    BXOTAS_DATA_RX_IND,
    BXOTAS_FINISH_IND,
};

struct bxotas_firmware_dest_cmd
{
    uint8_t firmware_dest;
};

struct bxotas_start_req_ind
{
    uint8_t conidx;
    uint16_t segment_data_max_length;
};

struct bxotas_start_cfm
{
    uint8_t status;
};

struct bxotas_new_block_ind
{
    uint16_t block_id;
};

struct bxotas_data_rx_ind
{
    uint8_t segment_id;
    uint8_t data_length;
    uint8_t data[];
};


/// }@ BXOTASTASK
#endif // BXOTAS_TASK_H_

