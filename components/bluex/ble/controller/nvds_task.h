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
#ifndef __NVDS_TASK_H__
#define __NVDS_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "rwip_config.h"
#include "rwip_task.h"
#include "task_id_patch.h"

/* exported types ------------------------------------------------------------*/

enum nvds_state_id {
    NVDS_EMPTY,
    NVDS_READY,
    NVDS_STATE_MAX,
};

enum nvds_msg_id {
    NVDS_SET_DATA_CMD = TASK_FIRST_MSG( TASK_ID_NVDS ),
    NVDS_DATA_PUT_IND,
};

struct nvds_set_data_cmd {
    uint16_t length;
    uint8_t nvds[];
};

struct nvds_data_put_ind {
    uint16_t length;
    uint8_t tag_name;
    uint8_t data[];
};

/* exported variables --------------------------------------------------------*/

/* bit definition ------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/
#define NVDS_IDX_MAX 1

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void nvds_task_init( void );
void nvds_data_put_ind_send( uint8_t name, uint8_t * data, uint16_t length );

#ifdef __cplusplus
}
#endif

#endif /* __NVDS_TASK_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
