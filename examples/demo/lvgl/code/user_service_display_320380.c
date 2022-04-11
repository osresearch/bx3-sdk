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

#include "bx_kernel.h"
#include "user_service_display.h"
#include "bx_spi_type_def.h"
#include "flash_wrapper.h"
#include "bx_dbg.h"
#include "plf.h"
#include "bxd_gpio.h"
#include "app_qspi_wrapper.h"
#include "arch_init.h"

/* private define ------------------------------------------------------------*/
#define LCD_CS_PIN                  2
#define FLASH_CS_PIN                4
#define LCD_RST_PIN                 7
#define LCD_LEDK_PIN                20

#define LCD_WIDE                    360
#define LCD_HIGH                    360

#define FILE_ID              3000000       
/* private typedef -----------------------------------------------------------*/
struct us_display_service {
    s32 id;
    u32 open_count;
    u8 * pic_buff;
    u32 pic_buff_max_len;

    s16 start_x;
    s16 start_y;

    s16 size_w;
    s16 size_h;
    
    u8  light_percent;
    u8  light_percent_bk;
};

struct lcd_cmd {
    u16 delay_ms;
    u8 addr;
    u32 len;
    u8 para[32];
};

struct lcd_cmd lcd_cmd_hub[] = {
    { 0, 0xFE, 0, {0} },
    { 0, 0xEF, 0, {0} },
    { 0, 0x80, 1, {0x11} },
    { 0, 0x81, 1, {0x70} },
    { 0, 0x82, 1, {0x09} },
    { 0, 0x83, 1, {0x03} },
    { 0, 0x84, 1, {0x22} },


    { 0, 0x89, 1, {0x18} },
    { 0, 0x8A, 1, {0x40} },
    { 0, 0x8B, 1, {0x0A} },



    { 0, 0x3A, 1, {0x05} },
    { 0, 0x36, 1, {0x40} },
    { 0, 0xEC, 1, {0x07} },

    { 0, 0x74, 6, {0x01, 0x80, 0, 0, 0, 0} },

    { 0, 0x98, 1, {0x3E} },
    { 0, 0x99, 1, {0x3E} },


    { 0, 0xA1, 2, {0x01, 0x04} },
    { 0, 0xA2, 2, {0x01, 0x04} },


    { 0, 0xCB, 1, {0x02} },
    { 0, 0xAC, 1, {0x44} },

    { 0, 0x7C, 2, {0xB6, 0x25} },
    { 0, 0xF6, 1, {0x80} },
    { 0, 0xB5, 2, {0x09, 0x09} },
    { 0, 0xEB, 2, {0x01, 0x7B} },
    { 0, 0x60, 4, {0x58, 0x09, 0x5b, 0x56} },
    { 0, 0x63, 4, {0x5B, 0x05, 0x5b, 0x56} },

    { 0, 0x64, 6, {0x38, 0x0f, 0X73, 0x17, 0x5b, 0x56} },
    { 0, 0x66, 6, {0x38, 0x0f, 0X73, 0x17, 0x5b, 0x56} },
    { 0, 0x65, 6, {0x38, 0x0b, 0X73, 0x13, 0x5b, 0x56} },
    { 0, 0x6E, 32, {0x00, 0x00, 0X00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0D, 0x0F, 0x09, 0x0B, 0x07, 0x00, 0x00, 0X00, 0x00, 0x00, 0X00, 0x08, 0x14, 0x12, 0x10, 0x0E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
    { 0, 0x6C, 7, {0xCC, 0x0C, 0XCC, 0x84, 0xCC, 0x04, 0x50} },
    { 0, 0x7D, 1, {0x72} },
    { 0, 0x70, 10, {0x02, 0x03, 0X09, 0x04, 0x0C, 0x06, 0x09, 0x05, 0x0C, 0x06} },
    { 0, 0x90, 4, {0x06, 0x06, 0x05, 0x06} },
    { 0, 0x93, 3, {0x45, 0xFF, 0x00} },
    { 0, 0xC3, 5, {0x40, 0xC4, 0x60, 0xC9, 0x3d} },
    { 0, 0xF0, 6, {0x47, 0x07, 0X08, 0x02, 0x00, 0x27} },
    { 0, 0xF2, 6, {0x47, 0x08, 0X07, 0x02, 0x00, 0x27} },
    { 0, 0xF1, 6, {0x41, 0xaA, 0x5a, 0x28, 0x2C, 0xef} },
    { 0, 0xF3, 6, {0x41, 0x9A, 0x5a, 0x28, 0x2C, 0xef} },
    { 0, 0xF9, 1, {0x30} },
    { 0, 0xBE, 1, {0x11} },
    { 0, 0xFB, 2, {0x00, 0x00} },
    { 0, 0xAA, 2, {0xb0, 0x00} },
    { 0, 0x11, 0, {0} },
    { 0, 0x2A, 4, {0, 0, ( 319 >> 8 ), ( 319 & 0xFF )} },
    { 0, 0x2B, 4, {0, 0, ( 379 >> 8 ), ( 379 & 0xFF )} },
    { 0, 0x29, 0, {0} },

//    { 0, 0x2c, 0, {0} },
//    { 0, 0x2c, 0, {0} },
//    { 120, 0, 0, {0} },
};


struct lcd_cmd lcd_cmd_hub2[] = {
    { 0, 0xC0, 2, {0x5a,0x5a} },
    { 0, 0xC1, 2, {0x5a,0x5A} },
    { 0, 0xBA, 1, {0x81} },
};
/* private variables ---------------------------------------------------------*/
static struct us_display_service display_svc = {0};
/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
#define GET_DISPLAY_SERVICE_BY_ID( p_svc, svc_id )                          \
do{                                                                         \
    if( ( svc_id ) == display_svc.id ) {                                    \
        p_svc = &display_svc;                                               \
    } else {                                                                \
        return BX_ERR_NOTSUP;                                               \
    }                                                                       \
}while(0)


#define bx_delay_ms(a)                                                      \
do{                                                                         \
    uint32_t n = a;                                                         \
    while( n > 0 ){                                                         \
        --n;                                                                \
        BX_DELAY_US( 1000 );                                                \
    }                                                                       \
} while( 0 )

#define lcd_io_init()                                                       \
do{                                                                         \
    bxd_gpio_set_mode( BX_GPIOA, LCD_RST_PIN, BX_GPIO_MODE_OUTPUT );     \
    bxd_gpio_set_mode( BX_GPIOA, LCD_CS_PIN, BX_GPIO_MODE_OUTPUT );      \
    bxd_gpio_set_mode( BX_GPIOA, FLASH_CS_PIN, BX_GPIO_MODE_OUTPUT );    \
    bxd_gpio_set_mode( BX_GPIOA, LCD_LEDK_PIN, BX_GPIO_MODE_OUTPUT );    \
    bxd_gpio_write(BX_GPIOA,LCD_LEDK_PIN,0);                             \
}while(0)

#define lcd_reset()                                                         \
do{                                                                         \
    bxd_gpio_write(BX_GPIOA,LCD_RST_PIN,1);                              \
    bx_delay_ms(50);                                                        \
    bxd_gpio_write(BX_GPIOA,LCD_RST_PIN,0);                              \
    bx_delay_ms(200);                                                        \
    bxd_gpio_write(BX_GPIOA,LCD_RST_PIN,1);                              \
    bx_delay_ms(50);                                                        \
}while(0)

#define qspi_use_to_lcd()                                                   \
do{                                                                         \
    cache_disable();    \
    bxd_gpio_set_mode( BX_GPIOA, FLASH_CS_PIN, BX_GPIO_MODE_OUTPUT );    \
    bxd_gpio_write(BX_GPIOA,FLASH_CS_PIN,1);                             \
    bxd_gpio_write(BX_GPIOA,LCD_CS_PIN,0);                               \
}while(0)

#define qspi_use_to_flash()                                                 \
do{                                                                         \
    bxd_gpio_set_mode( BX_GPIOA, FLASH_CS_PIN, BX_GPIO_MODE_INPUT );     \
    bxd_gpio_write(BX_GPIOA,LCD_CS_PIN,1);                               \
    cache_enable(); \
}while(0)
/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void lcd_send_cmd( u8 cmd )
{
    u8 data[4] = {0};
    data[0] = 0x02;
    data[1] = 0x00;
    data[2] = cmd;
    data[3] = 0x00;
    bxd_gpio_write(BX_GPIOA,LCD_CS_PIN,0);
    BX_DELAY_US(1);
    app_qspi_std_write_wrapper( data, 4 );
    bxd_gpio_write(BX_GPIOA,LCD_CS_PIN,1);
    BX_DELAY_US(1);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void lcd_cmd_write_ex( u8 cmd ,u8 * param, u32 len )
{
    if( cmd == 0 ) {
        return;
    }
    
    u8 data[64] = {0};
    data[0] = 0x02;
    data[1] = 0x00;
    data[2] = cmd;
    data[3] = 0x00;
    memcpy( &data[4], param, len );
    bxd_gpio_write(BX_GPIOA,LCD_CS_PIN,0);
    BX_DELAY_US(1);
    app_qspi_std_write_wrapper( data, 4 + len );
    bxd_gpio_write(BX_GPIOA,LCD_CS_PIN,1);
    BX_DELAY_US(1);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t lcd_open( void )
{
    bx_logln("dspl_drv_open");
    bxd_gpio_open(BX_GPIOA);
    lcd_io_init();
    lcd_reset();
    qspi_use_to_lcd();
    for( u32 i = 0 ; i < sizeof( lcd_cmd_hub ) / sizeof( lcd_cmd_hub[0] ); i++ ) {
        struct lcd_cmd * cmd = &lcd_cmd_hub[i];
        if( cmd->delay_ms > 0 ) {
            bx_delay_ms( cmd->delay_ms );
        }
        lcd_cmd_write_ex(cmd->addr,cmd->para,cmd->len);
        BX_DELAY_US(20);
    }
    qspi_use_to_flash();
    bx_logln("dspl_drv_open OK");
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void lcd_pixel_4wire_write_start( void )
{
    u8 data[4] = {0};
    data[0] = 0x32;
    data[1] = 0x00;
    data[2] = 0x2c;
    data[3] = 0x00;
    app_qspi_std_write_wrapper( data, 4 );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void lcd_pixel_4wire_write_continue( void )
{
    u8 data[4] = {0};
    data[0] = 0x32;
    data[1] = 0x00;
    data[2] = 0x3c;
    data[3] = 0x00;
    app_qspi_std_write_wrapper( data, 4 );
}

void lcd_show_area(s16 x1,s16 y1,s16 x2,s16 y2,u16 *color)
{
    MARK();
    lcd_set_area(x1,x2,y1,y2);
    u32 len = (x2 - x1 + 1)*(y2-y1+1)*2;
    MARK();
    lcd_show_buffer((u8*)color,len);
    MARK();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t dspl_show_color_ex(struct us_display_service * p_svc, u32 color )
{    
    uint16_t rgb = (color&0xFF00)>>8;
    rgb |= (color&0xFF) << 8;
    
    for( u32  j = 0; j < p_svc->pic_buff_max_len; j += 2 ) {
        uint16_t * p = (uint16_t *)&(p_svc->pic_buff[j]);
        * p = rgb;
    }
    
    //lcd_show_area(0,0,159,9,(u16 *)p_svc->pic_buff);
    
    qspi_use_to_lcd();
    lcd_pixel_4wire_write_start();
    u32 count = LCD_HIGH * LCD_WIDE / (p_svc->pic_buff_max_len / 2 );
    for( u32 i = 0; i < count; i++ ) {
        app_qspi_4wire_write_wrapper( p_svc->pic_buff, p_svc->pic_buff_max_len );
    }
    qspi_use_to_flash();

    return BX_OK;
}

///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static bx_err_t dspl_show_color_ex(struct us_display_service * p_svc, u32 color )
//{    
////    uint16_t rgb = (color&0xFF00)>>8;
////    rgb |= (color&0xFF) << 8;
//    uint32_t * p = (uint32_t *)(p_svc->pic_buff);
//    for( u32  j = 0; j < p_svc->pic_buff_max_len/4; j ++ ) {
//        * p = color;
//        p++;
//    }
//    //qspi_use_to_lcd();
//    //lcd_pixel_4wire_write_start();
//    u32 count = LCD_HIGH * LCD_WIDE / (p_svc->pic_buff_max_len / 2 );
//    for( u32 i = 0; i < count; i++ ) {
//        qspi_use_to_flash();
//        BX_DELAY_US(1000);
//        qspi_use_to_lcd();
//        if( i==0  )
//            app_qspi_4wire_write_ex_wrapper( 0x12,0x2c00,p_svc->pic_buff, p_svc->pic_buff_max_len );
//        else
//            app_qspi_4wire_write_ex_wrapper( 0x12,0x3c00,p_svc->pic_buff, p_svc->pic_buff_max_len );
//    }
//    qspi_use_to_flash();
//    return BX_OK;
//}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static void lcd_set_windows( s16 x, s16 y, s16 w, s16 h )
//{
//    u16 start_x = x;
//    u16 start_y = y;
//    u16 end_x = start_x + w - 1;
//    u16 end_y = start_y + h - 1;
//    
//    u8 data[5] = {0};
//    u8 len = 0;
//    data[len++] = start_x >> 8;
//    data[len++] = start_x;
//    data[len++] = end_x >> 8;
//    data[len++] = end_x;
//    lcd_cmd_write_ex(0x2A,data,len);
//    len = 0;
//    data[len++] = start_y >> 8;
//    data[len++] = start_y;
//    data[len++] = end_y >> 8;
//    data[len++] = end_y;
//    lcd_cmd_write_ex(0x2B,data,len);

//    lcd_send_cmd(0x2C);
//}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void lcd_set_area( s16 x1, s16 x2, s16 y1, s16 y2 )
{
//    struct lcd_cmd cmd_hub[2]={
//        { 0, 0x2A, 4, {( x1 >> 8 ), ( x1 & 0xFF ), ( x2 >> 8 ), ( x2 & 0xFF )} },
//        { 0, 0x2B, 4, {( y1 >> 8 ), ( y1 & 0xFF ), ( y2 >> 8 ), ( y2 & 0xFF )} },
//    };
//    qspi_use_to_lcd();
//    for( u32 i = 0 ; i < sizeof( cmd_hub ) / sizeof( cmd_hub[0] ); i++ ) {
//        struct lcd_cmd * cmd = &cmd_hub[i];
//        if( cmd->delay_ms > 0 ) {
//            bx_delay_ms( cmd->delay_ms );
//        }
//        lcd_cmd_write_ex(cmd->addr,cmd->para,cmd->len);
//        BX_DELAY_US(20);
//    }
//    qspi_use_to_flash();
    
    qspi_use_to_lcd();
    u8 data[5] = {0};
    u8 len = 0;
    data[len++] = x1 >> 8;
    data[len++] = x1 & 0xFF; 
    data[len++] = x2 >> 8;
    data[len++] = x2 & 0xFF;
    lcd_cmd_write_ex(0x2A,data,len);
    len = 0;
    data[len++] = y1 >> 8;
    data[len++] = y1 & 0xFF;
    data[len++] = y2 >> 8;
    data[len++] = y2 & 0xFF;
    lcd_cmd_write_ex(0x2B,data,len);
    qspi_use_to_flash();
}

void lcd_show_buffer( u8* buffer,u32 len )
{
    qspi_use_to_lcd();
    lcd_pixel_4wire_write_start();
    MARK();
    app_qspi_4wire_write_wrapper( buffer, len );
    MARK();
    qspi_use_to_flash();
    MARK();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t dspl_show_pic_ex(struct us_display_service * p_svc, u32 addr_base )
{    
//    lcd_set_windows(0,0,LCD_WIDE,LCD_HIGH);
    u32 addr = addr_base;
    u32 count = LCD_HIGH * LCD_WIDE / (p_svc->pic_buff_max_len / 2 );
    for( u32 i = 0; i < count; i++ ) {
        qspi_use_to_flash();
        flash_multi_read( addr, p_svc->pic_buff_max_len, p_svc->pic_buff);
        qspi_use_to_lcd();
        if( i==0  )
            lcd_pixel_4wire_write_start();
        else
            lcd_pixel_4wire_write_continue();
        app_qspi_4wire_write_wrapper( p_svc->pic_buff, p_svc->pic_buff_max_len );
        
//        if( i==0  )
//            app_qspi_4wire_write_ex_wrapper( 0x12,0x2c00,p_svc->pic_buff, p_svc->pic_buff_max_len );
//        else
//            app_qspi_4wire_write_ex_wrapper( 0x12,0x3c00,p_svc->pic_buff, p_svc->pic_buff_max_len );
//        
        addr += p_svc->pic_buff_max_len;
    }
    qspi_use_to_flash();
    bx_logln("lcd_show_pic_ex done:%08X,%08X",addr_base,addr);
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t display_msg_handle( s32 svc_id, u32 msg, u32 param0, u32 param1 )
{
    struct us_display_service * p_svc;
    GET_DISPLAY_SERVICE_BY_ID( p_svc, svc_id );

    switch( msg ) {
        case BXM_OPEN: {
            return lcd_open();
        }

        case BXM_CLOSE: {
            break;
        }
        
        case USM_DISPLAY_TOGGLE_PICTURE:{
            bx_logln("USM_DISPLAY_TOGGLE_PICTURE done");
            break;
        }
        
        case USM_DISPLAY_SHOW_PICTURE: {
            bx_logln("USM_DISPLAY_SHOW_PICTURE");
            break;
        }

        case USM_DISPLAY_SHOW_COLOR:{
            bx_logln("USM_DISPLAY_SHOW_COLOR done");
            break;
        }
        
        case USM_DISPLAY_SHOWEX_PICTURE: {
            bx_logln("USM_DISPLAY_SHOWEX_PICTURE");
            dspl_show_pic_ex(p_svc,param0);
            break;
        }

        case USM_DISPLAY_SHOWEX_COLOR:{
            dspl_show_color_ex(p_svc,param0);
            bx_logln("USM_DISPLAY_SHOWEX_COLOR done");
            break;
        }

        default:
            return BX_ERR_NOTSUP;
    }

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t display_property_set( s32 svc_id, u32 property, u32 param0, u32 param1 )
{
    struct us_display_service * p_svc;
    GET_DISPLAY_SERVICE_BY_ID( p_svc, svc_id );

    switch( property ) {
        case USP_PIC_SIZE:
            p_svc->size_w = param0;
            p_svc->size_h = param1;
            break;

        case USP_PIC_START_PONIT :
            p_svc->start_x = param0;
            p_svc->start_y = param1;
            break;

        case USP_PIC_BUFF :
            p_svc->pic_buff = ( u8 * )param0;
            p_svc->pic_buff_max_len = param1;
            break;

        default:
            return BX_ERR_NOTSUP;
    }

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t display_property_get( s32 svc_id, u32 property, u32 param0, u32 param1 )
{
//    struct us_display_service * p_svc;
//    GET_DISPLAY_SERVICE_BY_ID( p_svc, svc_id );

    switch( property ) {
        default:
            return BX_ERR_NOTSUP;
    }
}


/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool us_display_register( void )
{
    struct bx_service svc;
    svc.name = "display service";
    svc.msg_handle_func = display_msg_handle;
    svc.prop_get_func = display_property_get;
    svc.prop_set_func = display_property_set;
    display_svc.id = bx_register( &svc );
    if( display_svc.id == -1 ) {
        return false;
    }
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 us_display_id( void )
{
    return display_svc.id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



