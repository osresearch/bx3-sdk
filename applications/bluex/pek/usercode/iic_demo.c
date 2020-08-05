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
#include "iic_demo.h"
#include "bx_shell.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct iic_speed_onfig {
    uint32_t lcnt;    // low level count
    uint32_t hcnt;    // high level count
    uint32_t rx_hold; // rx hold
    uint32_t tx_hold; // tx hold
};

/// IIC clock speed selection.
enum speed_mode {
    /// SCL clock is 100kHz
    IIC_STANDARD_MODE   = 1,
    /// SCL clock is 400kHz
    IIC_FAST_MODE       = 2,
    /// SCL clock is 1000kHz.                                                           <p>
    /// High speed has a master code before main data send                              <p>
    /// IC_HS_MADDR regisitor can change the master code , but cannot be removed .
    IIC_HIGH_SPEED_MODE = 3,

    IIC_MODE_MAX,
};

/* private variables ---------------------------------------------------------*/
static struct iic_speed_onfig iic_speed_ary[IIC_MODE_MAX] = {
    {0,   0,   0, 0 }, //speed mode is 1-3,array[0] is no use.
    {160, 145, 3, 10}, // STANDARD_100K_32M
    {40,  30,  3, 6 }, // FAST_400K_32M
    {16,  8,   3, 3 }, // HIGH_1M_32M
};

/*============================= private function =============================*/

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
    uint32_t dev_addr;
    uint32_t mem_addr;

    do {
        if( !char_to_u32( &argv[argv[2]], &dev_addr ) ) {
            break;
        }
        if( !char_to_u32( &argv[argv[3]], &mem_addr ) ) {
            break;
        }
        uint8_t data = iic_read_byte( dev_addr, mem_addr );
        bxsh_logln( "%02X %02X : %02X", dev_addr, mem_addr, data );
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
static void write_byte_test( char argc, char * argv )
{
    //bxsh_logln( "write_byte_test start" );
    uint32_t dev_addr;
    uint32_t mem_addr;
    uint32_t data;
    do {
        if( !char_to_u32( &argv[argv[2]], &dev_addr ) ) {
            break;
        }
        if( !char_to_u32( &argv[argv[3]], &mem_addr ) ) {
            break;
        }
        if( !char_to_u32( &argv[argv[4]], &data ) ) {
            break;
        }
        iic_write_byte( dev_addr, mem_addr, data );
        bxsh_logln( "write done" );
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
    //bxsh_logln( "read_buff_test start" );
    uint32_t dev_addr;
    uint32_t mem_addr;
    uint32_t len;
    uint8_t data[32] = {0};
    do {
        if( !char_to_u32( &argv[argv[2]], &dev_addr ) ) {
            break;
        }
        if( !char_to_u32( &argv[argv[3]], &mem_addr ) ) {
            break;
        }
        if( !char_to_u32( &argv[argv[4]], &len ) ) {
            break;
        }
        if( len > 32 ) {
            break;
        }
        iic_read_buff( dev_addr, mem_addr, data, len );

        bxsh_log( "rd data %u\t:", len );
        for( uint32_t i = 0; i < len; i++ ) {
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
static void write_buff_test( char argc, char * argv )
{
    //bxsh_logln( "write_buff_test start" );
    uint32_t dev_addr;
    uint32_t mem_addr;
    uint8_t data[32];
    uint32_t len = 32;
    do {
        if( !char_to_u32( &argv[argv[2]], &dev_addr ) ) {
            break;
        }
        if( !char_to_u32( &argv[argv[3]], &mem_addr ) ) {
            break;
        }
        if( !string_to_hex_buff( &argv[argv[4]], data, &len ) ) {
            break;
        }
        bxsh_log( "wr data %u\t:", len );
        for( uint32_t i = 0; i < len; i++ ) {
            bxsh_log( "%02x ", data[i] );
        }
        bxsh_logln( "" );
        iic_write_buff( dev_addr, mem_addr, data, len );
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
static void prv_iic_cmd_handler( char argc, char * argv )
{
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: help [options]" );
            bxsh_logln( "options:" );
            bxsh_logln( "\t init \t: iic init" );
            bxsh_logln( "\t -r + dev_addr + mem_addr \t: read 1 byte " );
            bxsh_logln( "\t -w + dev_addr + mem_addr + data\t: write 1 byte " );
            bxsh_logln( "\t -rb + dev_addr + mem_addr + len\t: read buff " );
            bxsh_logln( "\t -wb + dev_addr + mem_addr + hex_data\t: write buff " );
        } else if ( !strcmp( "init", &argv[argv[1]] ) ) {
            iic_init();
            bxsh_logln( "init done" );
        } else if ( !strcmp( "-r", &argv[argv[1]] ) ) {
            read_byte_test( argc, argv );
        } else if ( !strcmp( "-w", &argv[argv[1]] ) ) {
            write_byte_test( argc, argv );
        } else if ( !strcmp( "-rb", &argv[argv[1]] ) ) {
            read_buff_test( argc, argv );
        } else if ( !strcmp( "-wb", &argv[argv[1]] ) ) {
            write_buff_test( argc, argv );
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
void iic_add_shell_cmd( void )
{
    bxsh_add_cmd( "iic", prv_iic_cmd_handler, "iic test" );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void iic_init( void )
{
    //选择时钟源 set clock src
    BX_MODIFY_REG( BX_PER->CS, PER_CS_IIC0, PER_CS_TYPE_16M_IIC0 );
    //打开时钟 set clock gate
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_IIC0 );
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_IIC0 );

    //复位
    BX_SET_BIT( BX_PER->SRST, PER_SRST_CLR_IIC0 );
    BX_SET_BIT( BX_PER->SRST, PER_SRST_SET_IIC0 );
    //先关闭 IIC
    BX_CLR_BIT( BX_IIC0->EN, IIC_EN_ENABLE );
    //设置分频参数
    //BX_MODIFY_REG(BX_PER->CDP0, PER_CDP0_IIC0 ,0 << PER_CDP0_IIC0_POS );

    BX_PER->CLKG1 |= PER_CLKG1_CLR_GPIO;
    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;

    //设为输入
    BX_AWO->GPIOIS |= ( GPIO_PIN_2 | GPIO_PIN_3 );
    BX_AWO->GPIOIE |= ( GPIO_PIN_2 | GPIO_PIN_3 );
    //上拉
    BX_AWO->GPIOPS |= ( GPIO_PIN_2 | GPIO_PIN_3 );
    BX_AWO->GPIOPE |= ( GPIO_PIN_2 | GPIO_PIN_3 );

    //配置引脚
    BX_SET_BIT( BX_CPU->FIOEN, GPIO_PIN_2 >> 2 );
    BX_SET_BIT( BX_CPU->FIOEN, GPIO_PIN_3 >> 2 );

    //设置对应功能
    // CPU_FIOS0_IO00 => GPIO_PIN_2
    // CPU_FIOS0_IO01 => GPIO_PIN_3
    BX_MODIFY_REG( BX_CPU->FIOS0, CPU_FIOS0_IO00, CPU_FIO_TYPE_IIC0_SDA << ( 0 * 4 ) );
    BX_MODIFY_REG( BX_CPU->FIOS0, CPU_FIOS0_IO01, CPU_FIO_TYPE_IIC0_SCL << ( 1 * 4 ) );

    //设置速度 set speed mode
#define IIC_SPEED_MODE  IIC_STANDARD_MODE

    BX_FIELD_WR( BX_IIC0->CR, IIC_CR_SPEED, IIC_SPEED_MODE );
    BX_FIELD_WR( BX_IIC0->SSSH, IIC_SSSH, iic_speed_ary[IIC_SPEED_MODE].hcnt );
    BX_FIELD_WR( BX_IIC0->SSSL, IIC_SSSL, iic_speed_ary[IIC_SPEED_MODE].lcnt );
    BX_FIELD_WR( BX_IIC0->SDAHT, IIC_SDAHT_RX_HOLD, iic_speed_ary[IIC_SPEED_MODE].rx_hold );
    BX_FIELD_WR( BX_IIC0->SDAHT, IIC_SDAHT_TX_HOLD, iic_speed_ary[IIC_SPEED_MODE].tx_hold );

    //0 -> 7bit 1->10bit
    BX_CLR_BIT( BX_IIC0->CR, IIC_CR_10BITADDR_MASTER );

    //工作模式 master ,默认slave
    BX_SET_BIT( BX_IIC0->CR, IIC_CR_MASTER_MODE );
    BX_SET_BIT( BX_IIC0->CR, IIC_CR_SLAVE_DISABLE );

    BX_FIELD_WR( BX_IIC0->TFTL, IIC_TFTL_TX_TL, 1 );

    //*(uint32_t *)(0x20145000)=0x0163;

    BX_SET_BIT( BX_IIC0->EN, IIC_EN_ENABLE );

    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_IIC0 );
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_IIC0 );
    BX_CLR_BIT( BX_IIC0->EN, IIC_EN_ENABLE );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//cmd 0->write
//cmd 1->read
void app_iic_set_data_cmd_pack( uint8_t restart, uint8_t stop, uint8_t cmd, uint8_t dat )
{
    BX_IIC0->DC = ( ( ( uint32_t )restart << 10 ) | ( ( uint32_t )stop << 9 ) | ( ( uint32_t )cmd << 8 ) | ( ( uint32_t )dat << 0 ) );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t iic_read_byte( uint8_t device_address, uint8_t mem_address )
{
    uint8_t ret = 0xDD;
    BX_CLR_BIT( BX_IIC0->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IIC0->TA, IIC_TA_TAR, device_address >> 1 );
    BX_SET_BIT( BX_IIC0->EN, IIC_EN_ENABLE );

    //while( BX_READ_BIT() );
    //0 0 0 0F
    app_iic_set_data_cmd_pack( 0, 0, 0, mem_address );
    //restart will send a byte of data
    app_iic_set_data_cmd_pack( 1, 1, 1, 0 );
    while( BX_READ_BIT ( BX_IIC0->STA, IIC_STA_RFNE ) == 0 );
    //while( BX_FIELD_RD ( BX_IIC0->RFTL,IIC_RFTL_RX_TL ) > 0 )
    while( BX_READ_BIT ( BX_IIC0->STA, IIC_STA_RFNE ) ) {
        ret = BX_FIELD_RD( BX_IIC0->DC, IIC_DC_DAT );
    }
    return ret;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void iic_write_byte( uint8_t device_address, uint8_t mem_address, uint8_t byte )
{
    BX_CLR_BIT( BX_IIC0->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IIC0->TA, IIC_TA_TAR, device_address >> 1 );
    BX_SET_BIT( BX_IIC0->EN, IIC_EN_ENABLE );

    //while( BX_READ_BIT() );
    //0 0 0 0F
    app_iic_set_data_cmd_pack( 1, 0, 0, mem_address );
    //restart will send a byte of data
    app_iic_set_data_cmd_pack( 0, 1, 0, byte );
    while( BX_READ_BIT ( BX_IIC0->STA, IIC_STA_TFE ) == 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :   return read length
-----------------------------------------------------------------------------*/
void iic_read_buff( uint8_t device_address, uint8_t mem_address, uint8_t * data, uint32_t read_len )
{
    BX_CLR_BIT( BX_IIC0->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IIC0->TA, IIC_TA_TAR, device_address >> 1 );
    BX_SET_BIT( BX_IIC0->EN, IIC_EN_ENABLE );

    uint8_t restart = 1;
    uint8_t stop = 0;
    //restart will send a byte of data
    do {
        if( read_len == 1 ) {
            stop = 1;
        }
        app_iic_set_data_cmd_pack( 0, 0, 0, mem_address++ );
        app_iic_set_data_cmd_pack( restart, stop, 1, 0 );
        restart = 0;
        while( BX_READ_BIT ( BX_IIC0->STA, IIC_STA_RFNE ) == 0 );
        *data = BX_FIELD_RD( BX_IIC0->DC, IIC_DC_DAT );
        data++;
        read_len--;
    } while( read_len > 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void iic_write_buff( uint8_t device_address, uint8_t mem_address, uint8_t * data, uint32_t buff_len )
{
    BX_CLR_BIT( BX_IIC0->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IIC0->TA, IIC_TA_TAR, device_address >> 1 );
    BX_SET_BIT( BX_IIC0->EN, IIC_EN_ENABLE );

    uint8_t stop = 0;
    //restart will send a byte of data
    do {
        if( buff_len == 1 ) {
            stop = 1;
        }
        app_iic_set_data_cmd_pack( 1, 0, 0, mem_address++ );
        app_iic_set_data_cmd_pack( 0, stop, 0, *data );
        while( BX_READ_BIT ( BX_IIC0->STA, IIC_STA_TFE ) == 0 );
        data++;
        buff_len--;
    } while( buff_len > 0 );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
