
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
#define __RAM_CODE__

/* includes ------------------------------------------------------------------*/
#include "bx_dbg.h"

#if ( BX_ENABLE_LOG > 0 )

#include "SEGGER_RTT.h"
#include <stdarg.h>
#include "apollo_00_ble_reg.h"
#include "apollo_00_reg.h"
#include "bx_sys_config.h"
#include "arch_init.h"
/* private define ------------------------------------------------------------*/
#define MAX_TAG_LENGTH  30
/* private typedef -----------------------------------------------------------*/
struct {
    uint32_t msp;
    uint32_t psp;
    uint32_t lr;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
} hardfault_env;

enum {
    R0_INSTACK,
    R1_INSTACK,
    R2_INSTACK,
    R3_INSTACK,
    R12_INSTACK,
    LR_INSTACK,
    PC_INSTACK,
    xPSR_INSTACK,
};
struct uart_baudrate_cfg {
    u8  num1;
    u8  num0;
    u8  len1;
    u8  len0;
    u32 div;
};
static struct uart_baudrate_cfg bd_cfg_hub[] = {
    {0, 0, 0, 0, 8},   /*250000*/
    {0, 0, 0, 0, 4},   /*500000*/
    {0,  0, 0, 0, 2},  /*1000000*/
    {0,  0, 0, 0, 1},  /*2000000*/

    {2, 12, 2, 1, 768},/*1200*/
    {2, 12, 2, 1, 384},/*2400*/
    {2, 12, 2, 1, 192},/*4800*/
    {2, 12, 2, 1, 96}, /*9600*/
    {2, 12, 2, 1, 64}, /*14400*/
    {2, 12, 2, 1, 48}, /*19200*/
    {2, 12, 2, 1, 24}, /*38400*/
    {2, 12, 2, 1, 16}, /*57600*/
    {2, 12, 2, 1, 12}, /*76800*/
    {2, 12, 2, 1, 8},  /*115200*/
    {2, 12, 2, 1, 4},  /*230400*/
    {1, 29, 4, 7, 1},  /*256000*/
    {2, 12, 2, 1, 2},  /*460800*/
    {12, 2, 1, 2, 1},  /*921600*/

};

enum uart_baudrate {
    BX_UART_BD_250000,
    BX_UART_BD_500000,
    BX_UART_BD_1000000,
    BX_UART_BD_2000000,

    BX_UART_BD_1200,
    BX_UART_BD_2400,
    BX_UART_BD_4800,
    BX_UART_BD_9600,
    BX_UART_BD_14400,
    BX_UART_BD_19200,
    BX_UART_BD_38400,
    BX_UART_BD_57600,
    BX_UART_BD_76800,
    BX_UART_BD_115200,
    BX_UART_BD_230400,
    BX_UART_BD_256000,
    BX_UART_BD_460800,
    BX_UART_BD_921600,
    BX_UART_BD_MAX,
};

static bool uart_init_flag = false;

static const char * level_output_info[] = {
    [LOG_LVL_ASSERT]  = "A/",
    [LOG_LVL_ERROR]   = "E/",
    [LOG_LVL_WARN]    = "W/",
    [LOG_LVL_INFO]    = "I/",
    [LOG_LVL_DEBUG]   = "D/",
    [LOG_LVL_VERBOSE] = "V/",
};

static volatile u32 log_sys_tick = 0;

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void uart_log_init( void )
{
    NVIC_ClearPendingIRQ( UART0_IRQn );

    /* close clock */
    BX_PER->CLKG0 |= PER_CLKG0_32M_CLR_UART0;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_CLR_UART0;

    uint8_t baudrate = BX_UART_BD_115200;
    struct uart_baudrate_cfg * p_cfg = &bd_cfg_hub[baudrate];

    BX_PER->CDP1  = ( ( ( uint32_t )p_cfg->num1 << 24 )     \
                      | ( ( uint32_t )p_cfg->num0 << 16 )  \
                      | ( ( uint32_t )p_cfg->len1 << 8 )   \
                      | ( ( uint32_t )p_cfg->len0 << 0 ) );
    if( baudrate > BX_UART_BD_2000000 ) {
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_DIV_UART0 );
    } else {
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_UART0 );
    }

    /* open clock */
    BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART0;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_UART0;

    BX_SET_BIT( BX_CPU->FIOEN, GPIO_PIN_13 >> 2 );
    BX_SET_BIT( BX_CPU->FIOEN, GPIO_PIN_12 >> 2 );

    /* rx pin n  input config */
    BX_GPIOA->DIR &= ~( GPIO_PIN_13 );
    BX_AWO->GPIOIS |= ( GPIO_PIN_13 );
    BX_AWO->GPIOIE |= ( GPIO_PIN_13 );


    //gpio_mux[12] = funcio 10 , gpio_mux[13]=funcio 11
    BX_MODIFY_REG( BX_CPU->FIOS1, CPU_FIOS1_IO10, CPU_FIO_TYPE_UART0_TX << ( ( 10 - 8 ) * 4 ) );
    BX_MODIFY_REG( BX_CPU->FIOS1, CPU_FIOS1_IO11, CPU_FIO_TYPE_UART0_RX << ( ( 11 - 8 ) * 4 ) );

    BX_MODIFY_REG( BX_UART0->LC, UART_LC_DATA_WIDTH, UART_LC_DATA_WIDTH_T_8B );


    BX_SET_BIT( BX_UART0->LC, UART_LC_STOP_BIT );
    BX_CLR_BIT( BX_UART0->LC, UART_LC_PARITY_EN );

    //UART0->LCR |= UART_PARITY_EVEN;//even
    //UART0->LCR &= ~UART_PARITY_EVEN;//odd

    /* before set divisor must open clk */
    BX_UART0->LC |= 0x80;
    BX_UART0->RTD = ( uint8_t )p_cfg->div;
    BX_UART0->DI = ( uint8_t )( p_cfg->div >> 8 );
    BX_UART0->LC &= ~( ( uint32_t )0x80 );

    BX_UART0->IF |= UART_IF_FIFO_EN;

    uart_init_flag = true;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void uart_log_write( u8 * buff, u32 len )
{
    if( !uart_init_flag ) {
        return;
    }

    while( len ) {
        BX_UART0->RTD = *buff;
        while( BX_READ_BIT( BX_UART0->LS, UART_LS_TX_EMPTY ) == 0 );
        buff++;
        len--;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :cur_len current copied log length, max size is LOG_PRINTF_BUFFER_SIZE
 * @param   :dst destination
 * @param   :src source
 * @retval  :copied length
-----------------------------------------------------------------------------*/
u32 bx_log_strcpy( size_t cur_len, char * dst, const char * src )
{
    const char * src_old = src;

    while ( src != 0 && *src != 0 ) {
        /* make sure destination has enough space */
        if ( cur_len++ < LOG_PRINTF_BUFFER_SIZE ) {
            *dst++ = *src++;
        } else {
            break;
        }
    }
    return src - src_old;
}

#if ( BX_USE_SYS_TICK_FOR_LOG > 0 )
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void SysTick_init( void )
{
    SysTick->LOAD  = ( u32 )( MAIN_CLOCK / 1000  - 1UL );                   /* set reload register */
    NVIC_SetPriority ( SysTick_IRQn, ( 1UL << __NVIC_PRIO_BITS ) - 1UL ); /* set Priority for Systick Interrupt */
    SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                     SysTick_CTRL_TICKINT_Msk   |
                     SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */

    NVIC_ClearPendingIRQ( SysTick_IRQn );
    NVIC_EnableIRQ( SysTick_IRQn );
    __enable_irq();
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void SysTick_Handler( void )
{
    log_sys_tick++;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
char * log_get_time( void )
{
    static char time[16] = { 0 };
    sprintf( time, "%10d ", log_sys_tick );
    return time;
}
#else
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
char * log_get_time( void )
{
    return NULL;
}
#endif
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void log_init( void )
{
#if ( BX_USE_UART_LOG > 0 )
    uart_log_init();
#endif
#if ( BX_USE_SYS_TICK_FOR_LOG > 0 )
    SysTick_init();
#endif

    // u32 unloaded_area_data = unloaded_area->data;
    // SHOW_VAR(unloaded_area_data);
    // for( u32 i = 0; i < 32; i++ ) {
    //     unloaded_area->mark_count--;
    //     u32 index = unloaded_area->mark_count & 0x1F;
    //     LOG_RAW( "mark[%02u]:%10u\r\n", index, unloaded_area->mark[index] );
    // }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void log_output( int8_t level, const char * tag, bool linefeed, const char * format, ... )
{
    u32 log_len = 0;
    u32 tag_len = strlen( tag );
    u32 newline_len = strlen( BX_DATA_NEWLINE_SIGN );
    char tag_sapce[MAX_TAG_LENGTH / 2 + 1] = { 0 };
    char log_buf[LOG_PRINTF_BUFFER_SIZE] = {0};
    va_list ap;
    va_start( ap, format );
    __disable_irq();
    if( linefeed ) {
        log_len += bx_log_strcpy( log_len, log_buf + log_len, log_get_time() );
    }
    if( level <= LOG_LVL_VERBOSE ) {
        log_len += bx_log_strcpy( log_len, log_buf + log_len, level_output_info[level] );
    }
    if ( tag_len > 0 ) {
        log_len += bx_log_strcpy( log_len, log_buf + log_len, tag );
        if ( tag_len <= MAX_TAG_LENGTH / 2 ) {
            memset( tag_sapce, ' ', MAX_TAG_LENGTH / 2 - tag_len );
            log_len += bx_log_strcpy( log_len, log_buf + log_len, tag_sapce );
        }
        log_len += bx_log_strcpy( log_len, log_buf + log_len, " " );
    }

    s32 fmt_result = vsnprintf( log_buf + log_len, LOG_PRINTF_BUFFER_SIZE - log_len, format, ap );
    va_end( ap );

    if ( ( log_len + fmt_result <= LOG_PRINTF_BUFFER_SIZE ) && ( fmt_result > -1 ) ) {
        log_len += fmt_result;
    } else {
        /* using max length */
        log_len = LOG_PRINTF_BUFFER_SIZE;
    }
    if( linefeed ) {
        if ( log_len + newline_len > LOG_PRINTF_BUFFER_SIZE ) {
            /* using max length */
            log_len = LOG_PRINTF_BUFFER_SIZE;
            log_len -= newline_len;
        }
        log_len += bx_log_strcpy( log_len, log_buf + log_len, BX_DATA_NEWLINE_SIGN );
    }
    __enable_irq();

#if ( BX_USE_RTT_LOG > 0 )
    SEGGER_RTT_Write( 0, log_buf, log_len );
#endif

#if ( BX_USE_UART_LOG > 0 )
    uart_log_write( ( u8 * )log_buf, log_len );
#endif
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_assert_failed( char * expr, char * file, int line )
{
    __disable_irq();
    LOG( LOG_LVL_ERROR, "Assertion Failed: file %s, line %d, %s\n", file, line, expr );
    while( 1 );
}
#endif
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :   in bx_dbg_asm.s
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rwip_assert_c( uint32_t lvl, uint32_t param0, uint32_t param1, uint32_t lr )
{
    LOG( lvl, "lvl:%x,lr=0x%08x,param0=0x%x,param1=0x%x\n", lvl, lr, param0, param1 );
    if( lvl == LVL_ERROR ) {
        __disable_irq();
        while( 1 );
    }
}

#if ( BX_ENABLE_LOG > 0 )
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void hardfault_print( void )
{
    uint32_t msp = hardfault_env.msp;
    uint32_t psp = hardfault_env.psp;
    uint32_t lr = hardfault_env.lr;
    uint32_t r4 = hardfault_env.r4;
    uint32_t r5 = hardfault_env.r5;
    uint32_t r6 = hardfault_env.r6;
    uint32_t r7 = hardfault_env.r7;
    LOG( LOG_LVL_ERROR, "!!!!!!!!!!HardFault Handler is triggered!!!!!!!!!!\r\n" );
    LOG( LOG_LVL_ERROR, "Prolog:\r\n" );
    LOG( LOG_LVL_ERROR, "R4   = 0x%08x\r\n", r4 );
    LOG( LOG_LVL_ERROR, "R5   = 0x%08x\r\n", r5 );
    LOG( LOG_LVL_ERROR, "R6   = 0x%08x\r\n", r6 );
    LOG( LOG_LVL_ERROR, "R7   = 0x%08x\r\n", r7 );
    LOG( LOG_LVL_ERROR, "lr   = 0x%08x\r\n", lr );
    LOG( LOG_LVL_ERROR, "msp  = 0x%08x\r\n", msp );
    LOG( LOG_LVL_ERROR, "psp  = 0x%08x\r\n", psp );
    uint32_t * sp = 0;
    if( lr == 0xfffffffd ) {
        sp = ( uint32_t * )psp;
        LOG( LOG_LVL_ERROR, "PSP Stack Info:\r\n" );
    } else {
        sp = ( uint32_t * )msp;
        LOG( LOG_LVL_ERROR, "MSP Stack Info:\r\n" );
    }

    // Try to dump
    LOG( LOG_LVL_ERROR, "R0   = 0x%08x\r\n", sp[R0_INSTACK] );
    LOG( LOG_LVL_ERROR, "R1   = 0x%08x\r\n", sp[R1_INSTACK] );
    LOG( LOG_LVL_ERROR, "R2   = 0x%08x\r\n", sp[R2_INSTACK] );
    LOG( LOG_LVL_ERROR, "R3   = 0x%08x\r\n", sp[R3_INSTACK] );
    LOG( LOG_LVL_ERROR, "R12  = 0x%08x\r\n", sp[R12_INSTACK] );
    LOG( LOG_LVL_ERROR, "LR   = 0x%08x\r\n", sp[LR_INSTACK] );
    LOG( LOG_LVL_ERROR, "PC   = 0x%08x\r\n", sp[PC_INSTACK] );
    LOG( LOG_LVL_ERROR, "xPSR = 0x%08x\r\n", sp[xPSR_INSTACK] );
}
#endif /* ( BX_ENABLE_LOG > 0 ) */
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void HardFault_Handler( void )
{
#if ( BX_ENABLE_LOG > 0 )
    uint32_t canonical_frame_addr = __get_MSP() + 8;
    uint32_t * lr_addr = ( uint32_t * )( canonical_frame_addr - 4 );
    hardfault_env_save( &hardfault_env, canonical_frame_addr, *lr_addr );
    hardfault_print();
#endif
    while( 1 );
}


/*=========================== end of import function =========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

