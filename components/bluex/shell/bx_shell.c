/**
  ******************************************************************************
  * @file   :   .c
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
/* config --------------------------------------------------------------------*/


/* includes ------------------------------------------------------------------*/
#include "bxsh_uart.h"
#include "bx_shell.h"

#if ( BX_UART_SHELL_ENABLE > 0 )

/* private define ------------------------------------------------------------*/
#define S_SHELL_CONFIG_MAX_CMD_COUNT                 20

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static bool is_init = false;

/* private macros ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
static_cmd_st static_cmd[S_SHELL_CONFIG_MAX_CMD_COUNT] = {0};

/* exported function prototypes ----------------------------------------------*/

/*============================= private function =============================*/


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_memory_write( char argc, char * argv )
{
    uint32_t addr = 0;
    uint32_t data = 0;
    char ch[1];
    if ( argc == 2 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_log( "useage: %s + addr + data \r\n", &argv[argv[0]] );
            //bxsh_log( "\t test \t\t: toggle gpio pin 2\r\n" );
        } else {
            bxsh_option_unsupport( &argv[argv[0]] );
        }
    } else if( argc == 3 ) {
        if( sscanf( &argv[argv[1]], "%*[0]%*[x|X]%8X%1s", &addr, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[1]], "%10u%1s", &addr, ch ) == 1 ) {
        } else {
            bxsh_log( "addr err\r\n" );
            return;
        }

        if( sscanf( &argv[argv[2]], "%*[0]%*[x|X]%8X%1s", &data, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[2]], "%10u%1s", &data, ch ) == 1 ) {
        } else {
            bxsh_log( "data err\r\n" );
            return;
        }
        //bxsh_log( "addr:%u\t0x%08X\r\n", addr,addr );
        //bxsh_log( "data:%u\t0x%08X\r\n", data,data );

        *( uint32_t * )addr = data;
        bxsh_log( "write done\r\n" );
    } else {
        bxsh_arg_err( &argv[argv[0]] );
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_memory_read( char argc, char * argv )
{
    uint32_t addr = 0;
    uint32_t data = 0;
    uint32_t len = 0;
    char ch[1];
    if ( argc == 2 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_log( "useage: %s + addr \r\n", &argv[argv[0]] );
            bxsh_log( "useage: %s + addr + len \r\n", &argv[argv[0]] );
            return ;
        }
        if( sscanf( &argv[argv[1]], "%*[0]%*[x|X]%8X%1s", &addr, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[1]], "%10u%1s", &addr, ch ) == 1 ) {
        } else {
            bxsh_log( "addr err\r\n" );
            return;
        }
        //bxsh_log( "addr:%u\t0x%08X\r\n", addr,addr );
        data = *( uint32_t * )addr;
        bxsh_log( "0x%08x value : %uUL\t0x%08x\r\n", addr, data, data );
    } else if ( argc == 3 ) {
        if( sscanf( &argv[argv[1]], "%*[0]%*[x|X]%8X%1s", &addr, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[1]], "%10u%1s", &addr, ch ) == 1 ) {
        } else {
            bxsh_log( "addr err\r\n" );
            return;
        }
        if( sscanf( &argv[argv[2]], "%*[0]%*[x|X]%8X%1s", &len, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[2]], "%10u%1s", &len, ch ) == 1 ) {
        } else {
            bxsh_log( "len err\r\n" );
            return;
        }
        
        for( uint32_t i=0;i<len;i++ ){
            data = *( uint32_t * )addr;
            bxsh_log( "0x%08x value : 0x%08x\r\n", addr, data );
                addr += 4;
        }
    } else {
        bxsh_arg_err( &argv[argv[0]] );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_reset_cmd( char argc, char * argv )
{
    BX_CPU->SRST |= CPU_SRST_CLR_WDT_N;
    BX_CPU->SRST |= CPU_SRST_SET_WDT_N;

    BX_CPU->CLKG1 |= CPU_CLKG1_SET_WDT;
    BX_MODIFY_REG( BX_WDT->CTRL, WDT_CTRL_RST_PULSE_LEN, WDT_CTRL_RST_PULSE_LEN_T_2_PCLK_CYCLES );
    BX_MODIFY_REG( BX_WDT->TR, WDT_TR_PERIOD, 1 );
    BX_WDT->CTRL |= WDT_CTRL_EN;
    
//    BX_AWO->SRST |= AWO_SRST_ALL_CLR;
//    BX_AWO->SRST |= AWO_SRST_ALL_SET;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_list_cmd( char argc, char * argv )
{
    for ( uint32_t i = 0; nr_shell.static_cmd[i].fp != NULL; i++ ) {
        bxsh_logln( "%s\t%s", nr_shell.static_cmd[i].cmd, nr_shell.static_cmd[i].description );
    }
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxsh_init( void )
{
    bxsh_uart_init();
    memset( static_cmd, 0, sizeof( static_cmd ) );
    shell_init();
    bxsh_add_cmd( "mw", prv_memory_write, "memory write" );
    bxsh_add_cmd( "mr", prv_memory_read, "memory read" );
    bxsh_add_cmd( "ls", prv_list_cmd, "show all command" );
    bxsh_add_cmd( "reset", prv_reset_cmd, "reset chip" );
    is_init = true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxsh_open( void )
{
#if ( BX_USE_UART_LOG <= 0 )  //?uart????,????????
    bxsh_uart_init();
#endif
    memset( static_cmd, 0, sizeof( static_cmd ) );
    is_open = true;
    shell_init();
    bxsh_add_cmd( "mw", prv_memory_write, "memory write" );
    bxsh_add_cmd( "mr", prv_memory_read, "memory read" );
    bxsh_add_cmd( "ls", prv_list_cmd, "show all command" );
    bxsh_add_cmd( "reset", prv_reset_cmd, "reset chip" );	//uart shell???4???,???????
    bx_pm_lock( BX_PM_UART );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxsh_close( void )
{
    is_open = false;
    bx_pm_unlock( BX_PM_UART );		//??uart shell
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bxsh_add_cmd( char * cmd, void ( *fp )( char argc, char * argv ), char * description )
{
    static_cmd_st xcmd;
    sprintf( xcmd.cmd, "%s", cmd );
    xcmd.fp = fp;
    xcmd.description = description;

    for ( uint32_t i = 0; static_cmd[i].fp != NULL; i++ ) {
        if ( !strcmp( cmd, static_cmd[i].cmd ) ) {
            bxsh_logln( "cmd \"%s\" had used", cmd );
            return false;
        }
    }

    for ( uint32_t i = 0; i < S_SHELL_CONFIG_MAX_CMD_COUNT ; i++ ) {
        if ( static_cmd[i].fp == NULL  ) {
            static_cmd[i] = xcmd;
            return true;
        }
    }
    bxsh_logln( "not enough space to add cmd : %s", cmd );
    return false;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :   function must in loop
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxsh_run( void )
{
    if( uart_data_ready() ) {
        shell( bxsh_uart_read_byte() );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxsh_option_unsupport( char * cmd )
{
    bxsh_logln( "\"%s\" option unsupported", cmd );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxsh_arg_err( char * cmd )
{
    bxsh_logln( "\"%s\" arg err", cmd );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/** ---------------------------------------------------------------------------
 * @brief   :   uart_redirect
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int fputc( int ch, FILE * f )
{
    if( is_init ) {
        bxsh_uart_send_byte( ch );
    }
    return ch;
}

/** ---------------------------------------------------------------------------
 * @brief   :   uart_redirect
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int fgetc( FILE * f )
{
    int ch;
    if( is_init ) {
        ch = bxsh_uart_read_byte();
    }
    return ch;
}
/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/
/*========================= end of interrupt function ========================*/

#endif /* BX_UART_SHELL_ENABLE > 0 */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
