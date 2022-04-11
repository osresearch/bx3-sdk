/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) .
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_SVC_TP_H__
#define __USER_SVC_TP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
/* config --------------------------------------------------------------------*/
#define TP_RST_PIN                      7
#define TP_INT_PIN                      22
#define TP_SCL_PIN                      3
#define TP_SDA_PIN                      5
#define TP_CHIP_ADDR                    0x2a
/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

enum usm_tp_def {
    USM_TP_FIRST = BXM_FIRST_USER_MSG,
    // for action
    USM_TP_ACT_RESET,
    USM_TP_ACT_GET_ID,
    USM_TP_ACT_UPDATE_SOFTWARE,
    USM_TP_ACT_UPDATE_GUESTURE,
    USM_TP_ACT_UPDATE_POSITION,
    USM_TP_ACT_UPDATA_ALL_DATA,
    
    //for event
    USM_TP_EVT_INTR,
    
    
    //for public 
    USM_TP_PBL_RESET_DONE,
    USM_TP_PBL_SOFTWARE_UPDATED,
    USM_TP_PBL_GUESTURED_UPDATED,
    USM_TP_PBL_POSITION_UPDATED,
    USM_TP_PBL_ALL_DATA_UPDATED,
    
    
    USM_TP_MAX,
};

enum usp_tp_def {
    USP_TP_FIRST = BXP_FIRST_USER_PROP,
    
};

enum uss_tp_def {
    tp_sta_none,
    tp_sta_closed,
    tp_sta_ready,
    tp_sta_busy,
    tp_sta_err,
};

#pragma anon_unions
struct us_tp_data {
    u8  id;
    u8  guesture;
    u8  fg_num;
    u16 pos_x       : 12;//11:0
    u16 state       : 4;//15:12
    u16 pos_y       : 12;
    u16 reserved_2  : 4;
};

struct us_tp_service {
    s32 id;
    u8  state;
    u8  err_code;
    struct us_tp_data * pdata;
};



/* exported variables --------------------------------------------------------*/
extern struct us_tp_service tp_svc;
/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/
void        us_tp_init( void );
bool        us_tp_register( void );
s32         us_tp_id( void );

bx_err_t    us_tp_err_occurred( u32 msg );

#ifdef __cplusplus
}
#endif

#endif /* __USER_SVC_TP_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
