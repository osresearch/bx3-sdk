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
#include "spim_demo.h"
#include "bx_shell.h"
/* private define ------------------------------------------------------------*/

#define BX_SPIM_CS          GPIO_PIN_3
#define BX_SPIM_CLK         GPIO_PIN_4
#define BX_SPIM_MISO        GPIO_PIN_5
#define BX_SPIM_MOSI        GPIO_PIN_6

#define BX_SPIM             BX_SPIM0

/* private typedef -----------------------------------------------------------*/

static __IO uint8_t spim_tx_len = 0;
static __IO uint8_t spim_rx_len = 0;
static __IO uint8_t spim_rx_len_all = 0;
//static uint8_t * spim_tx_buff = NULL;
static uint8_t * spim_rx_buff = NULL;

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
static void prv_spim_init( void )
{
    //选择时钟源 set clock src

    //打开时钟 set clock gate
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_SPIM0 );
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_SPIM0 );

    //复位
    BX_SET_BIT( BX_PER->SRST, PER_SRST_CLR_SPIM0 );
    BX_SET_BIT( BX_PER->SRST, PER_SRST_SET_SPIM0 );

    //先关闭
    BX_CLR_BIT( BX_SPIM->SSIE, SPIM_SSIE_BIT );

    //设置分频参数 16M/160 = 100KHz
    BX_MODIFY_REG( BX_SPIM->BRS, SPIM_BRS_CD, ( uint32_t ) 160 );//Baud Rate Select

    //引脚配置
    BX_SET_BIT( BX_CPU->PSEN, CPU_PSEN_SPIM0 );

    BX_AWO->GPIOIS |= ( GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 );
    BX_AWO->GPIOIE |= ( GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 );
    //上拉
    BX_AWO->GPIOPS |= ( GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_5 );
    BX_AWO->GPIOPE |= ( GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_5 );

    //寄存器
    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_DFS32, SPIM_CTRL_DFS32_T_8_BITS );  //set Data Frame Size  mode
    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_SCPH, SPIM_CTRL_SCPH_T_MIDDLE ); //set Serial Clock Phase
    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_SCPOL, SPIM_CTRL_SCPOL_T_LOW ); //set Serial Clock Polarity
    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_FF, SPIM_CTRL_FF_T_MOTOROLA_SPI );

    //选择 0x01->cs0 0x02->cs1
    BX_MODIFY_REG( BX_SPIM->SE, SPIM_SE_VAL, 1 );
    BX_SET_BIT( BX_SPIM->SSIE, SPIM_SSIE_BIT );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_spim_transmit( uint8_t * data, uint32_t len )
{

#define SPIM_TXFIFO_LEN 16

    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_TM, SPIM_CTRL_TM_T_TXRX );

    uint32_t tx_len;
    while( 1 ) {
        tx_len = len > SPIM_TXFIFO_LEN ? SPIM_TXFIFO_LEN : len;
        for( uint32_t i = 0; i < len; i++ ) {
            BX_SPIM->DATA = *data;
            data++;
        }
        //确保Fifo不拥堵
        while( BX_READ_REG( BX_SPIM->TXFL ) != 0 );

        len -= tx_len;
        if( len == 0 ) {
            break;
        }
    }
}


///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static void prv_spim_transmit_recieve( uint8_t * tx_data, uint32_t tx_len, uint8_t * rx_data, uint32_t rx_len )
//{
//    if( tx_data == NULL || rx_data == NULL ) {
//        return ;
//    }
//
////    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
////    BX_GPIOA->DIR |= GPIO_PIN_2;
//
//#define SPIM_TX_FIFO_MAX_LEN 16
//#define SPIM_RX_FIFO_MAX_LEN 16

//    NVIC_ClearPendingIRQ( SPIM0_IRQn );  //clear  interrupt

//    uint32_t remain = BX_READ_REG( BX_SPIM->RXFL );
////    bxsh_logln("remain1:%u",remain);
//    //清空原有的干扰数据
//    while( remain>0 ) {
//        remain--;
//        BX_READ_REG( BX_SPIM->DATA );
//    }
//    remain = BX_READ_REG( BX_SPIM->RXFL );
////    bxsh_logln("remain2:%u",remain);
//
//    spim_rx_len_all = 0;
//    spim_tx_len = tx_len;
//    spim_rx_len = rx_len;
//    spim_rx_buff = rx_data;

//    BX_MODIFY_REG( BX_SPIS->CTRL, SPIS_CTRL_TM, ( uint32_t ) SPIS_CTRL_TM_T_TXRX );

//    //设置接收满阈值为1
//    BX_MODIFY_REG ( BX_SPIM->RXFTL, SPIM_RXFTL_VAL, 16 );

//    //清空中断
//    BX_READ_REG( BX_SPIM->EOI );

//    //屏蔽所有中断
//    BX_SET_REG( BX_SPIM->IM, 0 );
//    //打开接收满中断
//    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_RFF );

//    //即每接收一个，产生一次中断
//    NVIC_EnableIRQ( SPIM0_IRQn );
//
////    BX_GPIOA->OD ^= GPIO_PIN_2;
//    uint32_t len = 0;
//    while( 1 ) {
//        len = tx_len > SPIM_TX_FIFO_MAX_LEN ? SPIM_TX_FIFO_MAX_LEN : tx_len;
//        for( uint32_t i = 0; i < len; i++ ) {
//            BX_SPIM->DATA = *tx_data;
//            tx_data++;
//        }
//        while( BX_READ_REG( BX_SPIM->TXFL ) != 0 );
//        tx_len -= len;
//        if( tx_len == 0 ) {
//            break;
//        }
//    }

//    //用于产生波形,在中断中接收
//    while( 1 ) {
//        len = rx_len > SPIM_RX_FIFO_MAX_LEN ? SPIM_RX_FIFO_MAX_LEN : rx_len;
//        for( uint32_t i = 0; i < len; i++ ) {
//            BX_SPIM->DATA = 0xAA;
//        }
//        while( BX_READ_REG( BX_SPIM->TXFL ) != 0 );
//        rx_len -= len;
//        if( rx_len == 0 ) {
//            break;
//        }
//    }
////    while( BX_READ_BIT(BX_SPIM->STA,SPIM_STA_BUSY)>0 );
////    BX_GPIOA->OD ^= GPIO_PIN_2;
//    prv_user_delay(2000);
//    //BX_READ_REG( BX_SPIM->RXFL );
//    bxsh_logln("spim_rx_len_all:%u",spim_rx_len_all);
//    //while( spim_rx_len > 0 );
//}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_spim_transmit_recieve( uint8_t * tx_data, uint32_t tx_len, uint8_t * rx_data, uint32_t rx_len )
{
    if( tx_data == NULL || rx_data == NULL ) {
        return ;
    }

    uint32_t rx_data_len_in_tx = tx_len;
    uint32_t rx_data_len_in_rx = 0;

#define SPIM_TX_FIFO_MAX_LEN 16
#define SPIM_RX_FIFO_MAX_LEN 16

    uint32_t remain = BX_READ_REG( BX_SPIM->RXFL );
    while( remain > 0 ) {
        remain--;
        BX_READ_REG( BX_SPIM->DATA );
    }
    remain = BX_READ_REG( BX_SPIM->RXFL );

    BX_MODIFY_REG( BX_SPIS->CTRL, SPIS_CTRL_TM, ( uint32_t ) SPIS_CTRL_TM_T_TXRX );

    uint32_t len = 0;
    while( 1 ) {
        len = tx_len > SPIM_TX_FIFO_MAX_LEN ? SPIM_TX_FIFO_MAX_LEN : tx_len;
        for( uint32_t i = 0; i < len; i++ ) {
            BX_SPIM->DATA = *tx_data;
            tx_data++;
        }
        while( BX_READ_REG( BX_SPIM->TXFL ) != 0 );
        tx_len -= len;
        if( tx_len == 0 ) {
            break;
        }
    }

    while( 1 ) {
        len = rx_len > SPIM_RX_FIFO_MAX_LEN ? SPIM_RX_FIFO_MAX_LEN : rx_len;
        for( uint32_t i = 0; i < len; i++ ) {
            BX_SPIM->DATA = 0xAA;
        }
        while( BX_READ_REG( BX_SPIM->TXFL ) != 0 );
        //while( BX_READ_REG( BX_SPIM->RXFL ) <= len + rx_data_len_in_tx );
        while( BX_READ_REG( BX_SPIM->RXFL ) == 0 );
        while( BX_READ_REG( BX_SPIM->RXFL ) > 0 ) {
            rx_data_len_in_rx++;
            if( rx_data_len_in_tx > 0 ) {
                BX_READ_REG( BX_SPIM->DATA );
                rx_data_len_in_tx--;
            } else {
                *rx_data = BX_READ_REG( BX_SPIM->DATA );
                rx_data++;
            }
        }
        rx_len -= len;
        if( rx_len == 0 ) {
            break;
        }
    }

    //bxsh_logln( "spim_rx_len_all:%u", rx_data_len_in_rx );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_spim_receive( uint8_t * data, uint32_t rx_len )
{
    //清空当前存在的数据
    while( BX_READ_REG( BX_SPIM->RXFL ) > 0 ) {
        BX_READ_REG( BX_SPIM->DATA );
    }
    
    while( 1 ) {
        uint32_t len = rx_len > SPIM_RX_FIFO_MAX_LEN ? SPIM_RX_FIFO_MAX_LEN : rx_len;
        for( uint32_t i = 0; i < len; i++ ) {
            BX_SPIM->DATA = 0xAA;
        }
        while( BX_READ_REG( BX_SPIM->TXFL ) != 0 );
        while( BX_READ_REG( BX_SPIM->RXFL ) == 0 );
        while( BX_READ_REG( BX_SPIM->RXFL ) > 0 ) {
            *data = BX_READ_REG( BX_SPIM->DATA );
            data++;
        }
        rx_len -= len;
        if( rx_len == 0 ) {
            break;
        }
    }
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
static void read_byte_test( char argc, char * argv )
{
    //bxsh_logln( "read_byte_test start" );
    uint8_t data;
    prv_spim_receive( &data, 1 );
    bxsh_logln( "rx : %02X %u", data, data );

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void write_byte_test( char argc, char * argv )
{
    //bxsh_logln( "write_byte_test start" );
    uint32_t value;
    uint8_t data;
    do {
        if( !char_to_u32( &argv[argv[2]], &value ) ) {
            break;
        }
        data = value;
        bxsh_logln( "write : %02x", data );
        prv_spim_transmit( &data, 1 );
        return;
    } while( 0 );
    bxsh_arg_err( &argv[argv[0]] );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void read_buff_test( char argc, char * argv )
{
    uint32_t len;
    uint8_t data[32] = {0};
    do {
        if( !char_to_u32( &argv[argv[2]], &len ) ) {
            break;
        }
        if( len > 32 ) {
            break;
        }
        prv_spim_receive( data, len );

        bxsh_log( "rd data %u\t:", len );
        for( uint32_t i = 0; i < len; i++ ) {
            if( i % 16 == 0 ) {
                bxsh_logln( "" );
            }
            bxsh_log( "%02x ", data[i] );
        }
        bxsh_logln( "" );
        return;
    } while( 0 );
    bxsh_arg_err( &argv[argv[0]] );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void write_read_test( char argc, char * argv )
{
    //bxsh_logln( "write_buff_test start" );
    uint8_t tx_data[128];
    uint32_t tx_len = 32;
    uint8_t rx_data[128];
    uint32_t rx_len = 0;
    do {
        if( !string_to_hex_buff( &argv[argv[2]], tx_data, &tx_len ) ) {
            break;
        }
        if( !char_to_u32( &argv[argv[3]], &rx_len ) ) {
            break;
        }
        bxsh_log( "wr data %u: ", tx_len );
        for( uint32_t i = 0; i < tx_len; i++ ) {
            bxsh_log( "%02x ", tx_data[i] );
        }
        bxsh_logln( "" );
        prv_spim_transmit_recieve( tx_data, tx_len, rx_data, rx_len );
        bxsh_logln( "write buff done" );

        bxsh_log( "rx data %u: ", rx_len );
        for( uint32_t i = 0; i < rx_len; i++ ) {
            bxsh_log( "%02x ", rx_data[i] );
        }
        bxsh_logln( "" );
        return;
    } while( 0 );
    bxsh_arg_err( &argv[argv[0]] );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void write_buff_test( char argc, char * argv )
{
    uint8_t data[32];
    uint32_t len = 32;
    do {
        if( !string_to_hex_buff( &argv[argv[2]], data, &len ) ) {
            break;
        }
        bxsh_log( "wr data %u\t:", len );
        for( uint32_t i = 0; i < len; i++ ) {
            bxsh_log( "%02x ", data[i] );
        }
        bxsh_logln( "" );
        prv_spim_transmit( data, len );
        bxsh_logln( "write buff done" );
        return;
    } while( 0 );
    bxsh_arg_err( &argv[argv[0]] );
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
            bxsh_logln( "\t init \t: spim init" );
            bxsh_logln( "\t -r + addr \t: read 1 byte " );
            bxsh_logln( "\t -w + addr + data\t: write 1 byte " );
            bxsh_logln( "\t -rb + len\t: read buff " );
            bxsh_logln( "\t -wb + hex_data\t: write buff " );
            bxsh_logln( "\t -wr + write_data + read_len\t: write read test" );
        } else if ( !strcmp( "init", &argv[argv[1]] ) ) {
            prv_spim_init();
            bxsh_logln( "init done" );
        } else if ( !strcmp( "-r", &argv[argv[1]] ) ) {
            read_byte_test( argc, argv );
        } else if ( !strcmp( "-w", &argv[argv[1]] ) ) {
            write_byte_test( argc, argv );
        } else if ( !strcmp( "-rb", &argv[argv[1]] ) ) {
            read_buff_test( argc, argv );
        } else if ( !strcmp( "-wb", &argv[argv[1]] ) ) {
            write_buff_test( argc, argv );
        } else if ( !strcmp( "-wr", &argv[argv[1]] ) ) {
            write_read_test( argc, argv );
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
