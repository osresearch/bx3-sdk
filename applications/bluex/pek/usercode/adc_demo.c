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

/* includes ------------------------------------------------------------------*/

#include "apollo_00_reg.h"
#include "adc_demo.h"
#include "bx_shell.h"
#include "bx_adc.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/


/* private variables ---------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_user_delay( uint32_t val )
{
    for( uint32_t i = 0; i < val; i++ )
        for( uint32_t j = 0; j < 3000; j++ );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bool char_to_u32( char * str, uint32_t * value )
{
    char ch[1];
    if( sscanf( str, "%*[0]%*[x|X]%8X%1s", value, ch ) == 1 ) {
    } else if( sscanf( str, "%10u%1s", value, ch ) == 1 ) {
    } else {
        bxsh_logln( "param err" );
        return false;
    }
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    : 注意不做越界处理
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bool string_to_hex_buff( char * str, uint8_t * buff, uint32_t * buff_len )
{
    if( str[0] != '0' || str[1] != 'x' ) {
        bxsh_logln( "not begin with \"0x\"" );
        return false;
    }
    uint32_t len = strlen( str );
    if( len % 2 != 0 || len / 2 > *buff_len ) {
        bxsh_logln( "data len err" );
        return false;
    }
    for( uint32_t i = 0; i < len / 2 - 1; i++ ) {
        uint32_t value;
        if( sscanf( &str[2 + i * 2], "%2X", &value ) != 1 ) {
            str[2 + i * 2 + 2] = '\0';
            bxsh_logln( "data format err:%s", &str[2 + i * 2] );
            return false;
        }
        *buff = value;
        buff++;
    }
    *buff_len = len / 2 - 1;
    return true;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_spim_cmd_handler( char argc, char * argv )
{
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: help [options]" );
            bxsh_logln( "options:" );
            bxsh_logln( "\t init \t: adc init" );
            bxsh_logln( "\t -ra + channel \t: get channel adv value " );
            bxsh_logln( "\t -rv + channel \t: get channel volt value " );
            bxsh_logln( "\t -rv + channel \t: get battery volt value " );
        } else if ( !strcmp( "init", &argv[argv[1]] ) ) {
            bx_adc_init();
            bxsh_logln( "init done" );
        } else if ( !strcmp( "-ra", &argv[argv[1]] ) ) {
            
        } else if ( !strcmp( "-rv", &argv[argv[1]] ) ) {

        } else if ( !strcmp( "-rb", &argv[argv[1]] ) ) {

        } else {
            bxsh_option_unsupport( &argv[argv[0]] );
        }
    } else {
        bxsh_arg_err( &argv[argv[0]] );
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
void spim_add_shell_cmd( void )
{
    bxsh_add_cmd( "spim", prv_spim_cmd_handler, "spim test" );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/

/*============================ interrupt function ============================*/


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void spim_rx_full_isr( void )
{
    uint32_t count = BX_READ_REG( BX_SPIM->RXFL );
    //printf("%u\n",count);
    //过滤在发送时接收到的数据
    while( spim_tx_len > 0 && BX_READ_REG( BX_SPIM->RXFL ) > 0 ) {
        BX_READ_REG( BX_SPIM->DATA );
        spim_tx_len--;
        spim_rx_len_all++;
    }

    while( spim_rx_len > 0 && BX_READ_REG( BX_SPIM->RXFL ) > 0 ) {
        *spim_rx_buff = BX_READ_REG( BX_SPIM->DATA );
        spim_rx_len--;
        spim_rx_len_all++;
    }
    //多余的数据
    while( BX_READ_REG( BX_SPIM->RXFL ) > 0 ) {
        BX_READ_REG( BX_SPIM->DATA );
        spim_rx_len_all++;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void SPIM0_IRQHandler( void )
{
    uint32_t irq_stat = BX_SPIM->IS;
    if( irq_stat & SPIM_IS_RFF ) {
        spim_rx_full_isr();
    }
    //BX_READ_REG(BX_SPIM->EOI);
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
