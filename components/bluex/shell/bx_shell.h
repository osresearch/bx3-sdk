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
#ifndef __BLUEX_SHELL_API_H__
#define __BLUEX_SHELL_API_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config --------------------------------------------------------------------*/
#include "bx_sdk3_config.h"


/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "nr_micro_shell.h"

#if (BX_UART_SHELL_ENABLE > 0 )

/* exported types ------------------------------------------------------------*/
typedef void ( * func_f )( void );
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/
#define SHELL_TEST_ENABLE               1
/* exported macros -----------------------------------------------------------*/

#define bxsh_log(fmt,args...)            printf(fmt,##args)
#define bxsh_logln(fmt,args...)          printf(fmt"\r\n",##args)

/* exported functions --------------------------------------------------------*/

void bxsh_init( void );

bool bxsh_add_cmd( char * cmd, void ( *fp )( char argc, char * argv ), char * description );

void bxsh_run( void );

void bxsh_option_unsupport( char * cmd );

void bxsh_arg_err( char * cmd );

#else
#define bxsh_log( fmt, args... )                        ( ( void ) 0U )
#define bxsh_logln( fmt, args... )                      ( ( void ) 0U )
        
#define bxsh_init()                                     ( ( void ) 0U )
#define bxsh_add_cmd( cmd, fp, description )            ( ( void ) 0U )
#define bxsh_run()                                      ( ( void ) 0U )
#define bxsh_option_unsupport( cmd )                    ( ( void ) 0U )
#define bxsh_arg_err( cmd )                             ( ( void ) 0U )
    
#endif /* BX_UART_SHELL_ENABLE > 0 */

#ifdef __cplusplus
}
#endif

#endif /* __SHELL_API_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

