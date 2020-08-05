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
#ifndef __BX_KERNEL_TIMER_H__
#define __BX_KERNEL_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "rwip_task.h"
#include "bx_type_def.h"
#include "bx_kernel.h"

/* config  -------------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

enum bx_kernel_timer_msg {
    BKT_DUMMY_MSG = TASK_FIRST_MSG(TASK_ID_KERNEL_TIMER),
    
    BKT_MSG_CREAT_TIMER,
    
    BKT_MSG_FIRST,
    BKT_MSG_END = ( BKT_MSG_FIRST + BXKE_DELAY_MSG_CONFIG_MAX_COUNT - 1 ),
    
    BKT_MSG_MAX,
    BKT_MSG_NONE = 0xFF,
};



/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

//index ´Ó0¿ªÊ¼
#define BKT_ID_TO_INDEX( id )                           ( ( id ) - BKT_MSG_FIRST )
#define BKT_INDEX_TO_ID( index )                        ( (index) + BKT_MSG_FIRST )

/* exported functions --------------------------------------------------------*/
void    bx_kernel_timer_init(void);

u16     bx_kernel_timer_creat(u32 time, s32 repeat);

void    bx_kernel_timer_stop(u16 id);
bool    bx_kernel_timer_is_active(u16 id);
u32     bx_kernel_timer_id_to_array_index( u16 id );

void    bx_kernel_timer_timeout_callback(u16 id, bool end_of_repeat);
void    bx_kernel_timer_add_shell_cmd(void);



#ifdef __cplusplus
}
#endif

#endif /* __BX_KERNEL_TIMER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
