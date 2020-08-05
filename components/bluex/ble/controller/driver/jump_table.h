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
#ifndef __JUMP_TABLE_H__
#define __JUMP_TABLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
enum JUMP_TABLE_INDEX
{
	APP_INTERFACE = 0,
	PLATFORM_RESET,
	NVDS_INIT,
	NVDS_GET,
	NVDS_DEL,
	NVDS_PUT,
	PRF_INIT,
	PRF_CLEANUP,
	PRF_CREATE,
	PRF_ADD_PROFILE,
	PRF_GET_ID_FROM_TASK,
	PRF_GET_TASK_FROM_ID,
	ECC_GENERATE_KEY256,
	ECC_GEN_NEW_SECRET_KEY,
	ECC_GEN_NEW_PUBLIC_KEY,
	RWIP_WAKEUP,
	RWIP_WAKEUP_END,
	RWIP_PREVENT_SLEEP_SET,
	RWIP_PREVENT_SLEEP_CLEAR,
	RWIP_RESET,
	RWIP_RF,
	RWIP_PRIORITY,
	RWIP_COEX_CFG,
	LLD_SLEEP_INIT,
	RWIP_ASSERT_DBG,
	HBEACON,
	DUMMY0,
	DUMMY1,
	DUMMY2,
	JUMP_TABLE_SIZE
};

/* exported variables --------------------------------------------------------*/
extern void *const jump_table[];

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __JUMP_TABLE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
