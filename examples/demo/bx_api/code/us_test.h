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
#ifndef __USER_SERVICE_TEST_H__
#define __USER_SERVICE_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
struct test_property_type {
    u16 wide;
    u16 high;
    char  name[16];
};

enum user_property_test {
    USP_TEST_FIRST = BXP_FIRST_USER_PROP,
    
    USP_TEST_MY_PROPERTY,
    
    USP_TEST_WIDE,
    USP_TEST_HIGH,
    USP_TEST_NAME,
};

enum user_msg_test {
    USM_TEST_FIRST = BXM_FIRST_USER_MSG,
    
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     us_test_register( void );
s32      us_test_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __USER_SERVICE_TEST_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
