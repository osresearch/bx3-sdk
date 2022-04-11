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
#ifndef __USER_SERVICE_DISPLAY_H__
#define __USER_SERVICE_DISPLAY_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
enum user_property_DISPLAY {
    USP_DISPLAY_FIRST = BXP_FIRST_USER_PROP,
    
    USP_PIC_START_PONIT,
    USP_PIC_SIZE,
    
    USP_PIC_BUFF,
    
};

enum user_msg_DISPLAY{
    USM_DISPLAY_FIRST = BXM_FIRST_USER_MSG,
    
    USM_LDC_CMD_WRITE,
    USM_LDC_DATA_WRITE,
    USM_LDC_BUFFER_WRITE,
    
    USM_DISPLAY_TOGGLE_PICTURE,
    USM_DISPLAY_SHOW_PICTURE,
    USM_DISPLAY_SHOW_COLOR,
    
    USM_DISPLAY_SHOWEX_PICTURE,
    USM_DISPLAY_SHOWEX_COLOR,
    
    USM_DISPLAY_SELFCHECK,
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     us_display_register( void );
s32      us_display_id( void );

bx_err_t lcd_open( void );
void lcd_set_area( s16 x1, s16 y1, s16 x2, s16 y2 );
void lcd_show_buffer( u8* buffer,u32 len );
void lcd_show_area(s16 x1,s16 y1,s16 x2,s16 y2,u16 *color);
#ifdef __cplusplus
}
#endif

#endif /* __USER_SERVICE_DISPLAY_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
