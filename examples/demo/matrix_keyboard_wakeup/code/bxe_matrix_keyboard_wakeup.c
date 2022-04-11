#include "bxe_matrix_keyboard_wakeup.h"
#include "log.h"
#include "bxd_gpio.h"
#include "bx_kernel.h"
#include "flexible_button.h"
#include "gattc_task.h"
#include "ke_msg.h"
#include "rtc.h"




#if BUTTON_TIME_SCAN_MODE == 1
static flex_button_t user_button[USER_BUTTON_MAX] = {0};
#elif BUTTON_TIME_SCAN_MODE == 0
#define portMAX_32_BIT_NUMBER       (0xffffffff)
struct key_tag us_key[USER_BUTTON_MAX] = {0};
#endif



//u8 key_pin[5] = {15,16,17,22,23};
//u8 key_pin[5] = {17,23,22,15,16};

/*
      P13      P12      P2
P15____|________|________|      S1      S2      S3
       |        |        |
P17____|________|________|      S4      S5      S6
       |        |        |
P22____|________|________|      S7      S8      S9
       |        |        |
P23____|________|________|      S10     S11     S12

*/
u8 column_key_pin[3] = {13, 12, 2};
u8 raw_key_pin[4] = {15, 17, 22, 23};

#if BUTTON_TIME_SCAN_MODE == 0
u8 ext_trigger_mode[5] = {0};
#endif

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

#define ENUM_TO_STR(e) (#e)

static char * us_key_string[] = {
    ENUM_TO_STR( KEY_STA_NONE ),
    ENUM_TO_STR( KEY_STA_PRESS_DOWN ),
    ENUM_TO_STR( KEY_STA_PRESS_CLICK ),
    ENUM_TO_STR( KEY_STA_PRESS_DOUBLE_CLICK ),
    ENUM_TO_STR( KEY_STA_PRESS_REPEAT_CLICK ),
};
#if BUTTON_TIME_SCAN_MODE == 0
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint32_t system_time_ms( void )
{
    u32 time = 0;
    static uint32_t tick_count_last = 0;
    uint32_t tick_count_current = RTC_CURRENTCNT_GET();
    uint32_t tick_temp;
    if( tick_count_current > tick_count_last ) {
        tick_temp = tick_count_current - tick_count_last;
    } else if( tick_count_current < tick_count_last ) {
        tick_temp = ( portMAX_32_BIT_NUMBER - tick_count_last ) + tick_count_current;
    }

    time = tick_temp * 1000 / 32768;

    return time;
}
#endif
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_send_data_notify( u8 * data, u8 length, u16 handle )
{
    struct gattc_send_evt_cmd * notify_cmd = KE_MSG_ALLOC_DYN( GATTC_SEND_EVT_CMD,
            TASK_GATTC, TASK_APP,
            gattc_send_evt_cmd, length );
    CHECK_POINTER( notify_cmd );
    static u16 notify_seq_num = 0;
    notify_cmd->operation = GATTC_NOTIFY;
    notify_cmd->seq_num = notify_seq_num++;
    notify_cmd->length = length;
    notify_cmd->handle = handle;

    memcpy( notify_cmd->value, data, length );

    ke_msg_send( notify_cmd );
    return BX_OK;
}
#if BUTTON_TIME_SCAN_MODE == 1
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint8_t common_btn_read( void * arg )
{

    uint8_t value = 0;

    flex_button_t * btn = ( flex_button_t * )arg;
    u32 colum_size = ARRAY_SIZE( column_key_pin );

    for( u32 i = 0; i < colum_size  ; i++ ) {
        if( i == ( btn->id % colum_size ) ) {
            bxd_gpio_write( BX_GPIOA, column_key_pin[i], 0 );
        } else {
            bxd_gpio_write( BX_GPIOA, column_key_pin[i], 1 );
        }
    }
    u32 port_value = 0;
    bxd_gpio_read( BX_GPIOA, &port_value );
    value = ( ( port_value >> raw_key_pin[btn->id / colum_size] ) & 0x01 );
    return value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void common_btn_evt_cb( void * arg )
{
    flex_button_t * btn = ( flex_button_t * )arg;

    LOG_I( "btn->event = %d,btn->id = %d", btn->event, btn->id );

    u8 notify_buf[2] = {0};
    notify_buf[0] = btn->event;
    notify_buf[1] = btn->id;
    ble_send_data_notify( notify_buf, sizeof( notify_buf ), 30 );

    switch( btn->event ) {
        case FLEX_BTN_PRESS_DOWN:
            break;

        case FLEX_BTN_PRESS_CLICK:
        case FLEX_BTN_PRESS_DOUBLE_CLICK:
        case FLEX_BTN_PRESS_REPEAT_CLICK:
            bx_dwork( key_scan_process, NULL, 50, 1 );
            bx_dwork( key_scan_stop_process, NULL, 51, 1 );
            break;


        case FLEX_BTN_PRESS_SHORT_START:
        case FLEX_BTN_PRESS_LONG_START:
        case FLEX_BTN_PRESS_LONG_HOLD:
            break;

        case FLEX_BTN_PRESS_SHORT_UP:
        case FLEX_BTN_PRESS_LONG_UP:
        case FLEX_BTN_PRESS_LONG_HOLD_UP:
            bx_dwork( key_scan_process, NULL, 50, 1 );
            bx_dwork( key_scan_stop_process, NULL, 51, 1 );
            break;
    }

}

void key_init( void )
{
    bxd_gpio_open( BX_GPIOA );
    for( u8 i = 0; i < sizeof( raw_key_pin ) / sizeof( raw_key_pin[0] ); i++ ) {
        bxd_gpio_set_mode( BX_GPIOA, raw_key_pin[i], BX_GPIO_MODE_INPUT );
        bxd_gpio_set_pull( BX_GPIOA, raw_key_pin[i], BX_GPIO_PULLUP );
        bxd_gpio_set_mode( BX_GPIOA, raw_key_pin[i], BX_GPIO_MODE_EIT_FALLING );
    }

    for( u8 i = 0; i < sizeof( column_key_pin ) / sizeof( column_key_pin[0] ); i++ ) {
        bxd_gpio_set_mode( BX_GPIOA, column_key_pin[i], BX_GPIO_MODE_OUTPUT );
        bxd_gpio_write( BX_GPIOA, column_key_pin[i], 0 );
    }

    for( u8 i = 0; i < USER_BUTTON_MAX; i++ ) {
        user_button[i].id = i;
        user_button[i].usr_button_read = common_btn_read;
        user_button[i].cb = common_btn_evt_cb;
        user_button[i].pressed_logic_level = 0;
        user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT( 1000 / FLEX_BTN_SCAN_FREQ_HZ );
        user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT( 2000 );
        user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT( 4500 );
        flex_button_register( &user_button[i] );
    }
}


void key_scan_process( void * data )
{
    flex_button_scan();
}

void key_scan_stop_process( void * data )
{
    for( u32 i = 0; i < sizeof( column_key_pin ) / sizeof( column_key_pin[0] ); i++ ) {
        bxd_gpio_write( BX_GPIOA, column_key_pin[i], 0 );
    }	
}

#elif BUTTON_TIME_SCAN_MODE == 0
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void key_init( void )
{
    bxd_gpio_open( BX_GPIOA );
    for( u8 i = 0; i < sizeof( raw_key_pin ); i++ ) {
        bxd_gpio_set_mode( BX_GPIOA, raw_key_pin[i], BX_GPIO_MODE_INPUT );
        bxd_gpio_set_pull( BX_GPIOA, raw_key_pin[i], BX_GPIO_PULLUP );
        bxd_gpio_set_mode( BX_GPIOA, raw_key_pin[i], BX_GPIO_MODE_EIT_FALLING );

    }

    for( u8 i = 0; i < 5; i++ ) {
        ext_trigger_mode[i] = TRIGGER_FALLING_MODE;
    }

    for( u8 i = 0; i < sizeof( column_key_pin ); i++ ) {
        bxd_gpio_set_mode( BX_GPIOA, column_key_pin[i], BX_GPIO_MODE_OUTPUT );
        bxd_gpio_write( BX_GPIOA, column_key_pin[i], 0 );
    }

    for( u8 i = 0; i < USER_BUTTON_MAX; i++ ) {
        us_key[i].pressed_logic_level = 0;
        us_key[i].id = i;
        us_key[i].logic_level = 1;
        us_key[i].max_multiple_clicks_interval = 300;
    }

}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void key_state_machine( u32 key_value, u32 key_sta )
{

    u8 notify_buf[2] = {0};
    notify_buf[0] = key_sta;
    notify_buf[1] = key_value;
    ble_send_data_notify( notify_buf, sizeof( notify_buf ), 30 );

    switch( key_sta ) {
        case KEY_STA_NONE: {

        }
        break;

        case KEY_STA_PRESS_DOWN: {
        }
        break;

        case KEY_STA_PRESS_CLICK: {

        }
        break;

        case KEY_STA_PRESS_DOUBLE_CLICK: {

        }
        break;

        case KEY_STA_PRESS_REPEAT_CLICK: {

        }
        break;

        default:
            break;
    }
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int ext_to_pin( u8 ext_state )
{
    u32 pin_value = 0;

    switch( ext_state ) {
        case 0:
            pin_value = 15;
            break;

        case 1:
            pin_value = 16;
            break;

        case 2:
            pin_value = 17;
            break;

        case 3:
            pin_value = 22;
            break;

        case 4:
            pin_value = 23;
            break;

        default:
            break;

    }
    return pin_value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void key_press_process( void * data )
{
    u32 time = 0;

    time = system_time_ms();//unit:ms

    for( u8 i = 0; i < USER_BUTTON_MAX; i++ ) {
        if( us_key[i].now_press_timestamp != us_key[i].pre_press_timestamp ) {
            if( ( us_key[i].now_press_timestamp - us_key[i].release_timestamp  ) > us_key[i].max_multiple_clicks_interval ) {
                us_key[i].click_cnt = 1;

                us_key[i].pre_press_timestamp = us_key[i].now_press_timestamp;
                us_key[i].key_sta = KEY_STA_PRESS_DOWN;
                key_state_machine( i, us_key[i].key_sta );
            } else if( ( us_key[i].now_press_timestamp - us_key[i].release_timestamp > 20 ) && ( ( us_key[i].now_press_timestamp - us_key[i].release_timestamp ) <= us_key[i].max_multiple_clicks_interval ) ) {
                us_key[i].click_cnt++;
                us_key[i].pre_press_timestamp = us_key[i].now_press_timestamp;
            }
        }
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void key_release_process( void * data )
{
    u32 time = 0;

    time = system_time_ms();//unit:ms

    for( u8 i = 0; i < USER_BUTTON_MAX; i++ ) {
        if( us_key[i].click_cnt != 0 ) {
            if( us_key[i].click_cnt > 2 ) {
                us_key[i].key_sta = KEY_STA_PRESS_REPEAT_CLICK;
            } else {
                us_key[i].key_sta = KEY_STA_PRESS_DOWN + us_key[i].click_cnt;
            }
            key_state_machine( i, us_key[i].key_sta );
            us_key[i].click_cnt = 0;

        }
    }
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void get_trigger_timestamp( u8 mode, u8 ext_value )
{
    u32 time = 0;
    u32 pin_num = 0;
    u32 key_value = 0;

    time = system_time_ms();//unit:ms
    pin_num = ext_to_pin( ext_value );


    switch( mode ) {
        case BX_GPIO_MODE_EIT_RISING: {
            for( u8 i = 0; i < sizeof( column_key_pin ); i++ ) {
                bxd_gpio_write( BX_GPIOA, column_key_pin[i], 0 );
            }

            for( u8 i = 0; i < USER_BUTTON_MAX; i++ ) {
                if( us_key[i].logic_level == us_key[i].pressed_logic_level ) {
                    us_key[i].logic_level = 1;

                    us_key[i].release_timestamp = time;

                    bx_dwork_cancel( key_release_process );
                    bx_dwork( key_release_process, NULL, 200, 1 );

                    break;
                }
            }
        }
        break;

        case BX_GPIO_MODE_EIT_FALLING: {
            for( u8 i = 0; i < sizeof( raw_key_pin ); i++ ) {

                if( raw_key_pin[i] == pin_num ) {
                    for( u8 j = 0; j < sizeof( column_key_pin ); j++ ) {
                        for( u8 m = 0; m < sizeof( column_key_pin ); m++ ) {
                            if( m == j ) {
                                bxd_gpio_write( BX_GPIOA, column_key_pin[m], 0 );
                            } else {
                                bxd_gpio_write( BX_GPIOA, column_key_pin[m], 1 );
                            }
                        }
                        u32 pin_value = 0;
                        bxd_gpio_read( BX_GPIOA, &pin_value );
                        if( ( ( pin_value >> raw_key_pin[i] ) & 0x01 ) == us_key[i].pressed_logic_level ) {
                            key_value = i * sizeof( column_key_pin ) + j;
                            us_key[key_value].logic_level = us_key[i].pressed_logic_level;
                            break;
                        }
                    }
                    break;
                }
            }

            for( u8 i = 0; i < USER_BUTTON_MAX; i++ ) {
                if( us_key[i].logic_level == us_key[i].pressed_logic_level ) {

                    us_key[i].now_press_timestamp = time;
                    bx_dwork_cancel( key_release_process );
                    bx_dwork( key_press_process, NULL, 10, 1 );

                    break;
                }
            }

        }
        break;

        default:
            break;
    }
}
#endif
