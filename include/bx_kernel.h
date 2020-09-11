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
#ifndef __BX_KERNEL_H__
#define __BX_KERNEL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config --------------------------------------------------------------------*/
#include "bx_kernel_config.h"

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* config --------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef bx_err_t( *msg_handle_f )( s32 svc, u32 msg, u32 param0, u32 param1 );
typedef bx_err_t( *prop_handle_f )( s32 svc, u32 prop, u32 param0, u32 param1 );

struct bx_service {
    prop_handle_f   prop_set_func;
    prop_handle_f   prop_get_func;
    msg_handle_f    msg_handle_func;
    char      *     name;
};

enum bx_msg_kernel {
    BXM_KERNEL_ASET = BXM_FIRST_USER_MSG,
    BXM_KERNEL_AGET,
};

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void bx_kernel_init( void );
void bx_kernel_schedule( void );
s32  bx_register( struct bx_service * p_svc );

bx_err_t bx_call( s32 svc, u32 msg, u32 param0, u32 param1 );
bx_err_t bx_post( s32 svc, u32 msg, u32 param0, u32 param1 );
bx_err_t bx_defer( s32 svc, u32 msg, u32 param0, u32 param1, u32 time );
bx_err_t bx_repeat( s32 svc, u32 msg, u32 param0, u32 param1, u32 period );
bx_err_t bx_repeatn( s32 svc, u32 msg, u32 param0, u32 param1, u32 period, s32 num );
bx_err_t bx_cancel( s32 svc, u32 msg );

bx_err_t bx_subscibe( s32 svc, u32 msg, u32 param0, u32 param1 );
bx_err_t bx_subscibeex( s32 src, s32 dst, u32 msg );
bx_err_t bx_public( s32 svc, u32 msg, u32 param0, u32 param1 );
void     bx_err( s32 svc, u32 msg, u32 param0, u32 param1, bx_err_t err );

bx_err_t bx_set( s32 svc, u32 prop, u32 param0, u32 param1 );
bx_err_t bx_get( s32 svc, u32 prop, u8 * buff, u32 len );

u32                 bx_get_service_count( void );
struct bx_service * bx_get_service( s32 id );
s32                 bx_msg_source( void );

bool                bx_ke_busy(void);
#ifdef __cplusplus
}
#endif

#endif /* __BX_KERNEL_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
