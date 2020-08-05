/**
 ****************************************************************************************
 *
 * @file bxotas.h
 *
 * @brief Header file - Apollo BLE OTA Server.
 *
 * Copyright (C) Apollo Micro 2015-2016
 *
 *
 ****************************************************************************************
 */
 #ifndef BXOTA_H_
 #define BXOTA_H_

/**
 ****************************************************************************************
 * @addtogroup BXOTAS Apollo BLE OTA Server
 * @ingroup BXOTA
 * @brief Apollo BLE OTA Server
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#if (BLE_BXOTA_SERVER)

#include "ke_task.h"
#include "prf_types.h"
#include "prf_utils.h"
#include "bxota_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define BXOTAS_IDX_MAX 1
#define BLOCK_4K_SECTOR         0x1000

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
typedef enum
{
    BXOTAS_IDLE,
    BXOTAS_REQ,
    BXOTAS_BUSY,
    BXOTAS_STATE_MAX,
}bxotas_stat_t;

enum bxotas_att_db_handles
{
    BXOTAS_IDX_SVC,

    BXOTAS_IDX_CTRL_CHAR,
    BXOTAS_IDX_CTRL_VAL,
    BXOTAS_IDX_CTRL_IND_CFG,

    BXOTAS_IDX_DATA_CHAR,
    BXOTAS_IDX_DATA_VAL,

    BXOTAS_IDX_NB
};
 



/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

struct bxotas_env_tag
{
    prf_env_t prf_env;
    uint32_t ota_image_content_size;
    uint32_t ota_image_full_size;
    uint32_t ota_image_content_crc32;
    
    uint16_t start_hdl;
    uint16_t segment_data_length;
    uint16_t current_block;
    ke_state_t state[BXOTAS_IDX_MAX];
    uint8_t conidx;
    uint8_t firmware_dest;
    bxota_data_att_read_t ack;
};


/*
 * GLOBAL FUNCTION DECLARATIONS
 ****************************************************************************************
 */

void bxotas_image_validation(struct bxotas_env_tag *bxotas_env);

void bxotas_erase_flash(uint32_t offset,uint32_t image_limit);

void bxotas_flash_cleanup_for_ota(struct bxotas_env_tag *bxotas_env);

void bxotas_program_flash(struct bxotas_env_tag *bxotas_env,uint16_t segment_id,uint8_t const *data,uint16_t length);
/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler bxotas_default_handler;

#endif //BLE_BXOTA_SERVER

/// @} BXOTAS

 #endif // BXOTA_H_
 
