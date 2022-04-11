#ifndef __BXE_MATRIX_KEYBOARD_WAKEUP_H__
#define __BXE_MATRIX_KEYBOARD_WAKEUP_H__

#ifdef __cplusplus
extern "C" {
#endif
    
#include "bx_type_def.h"


typedef enum
{
    USER_BUTTON_0 = 0,
    USER_BUTTON_1,
    USER_BUTTON_2,
    USER_BUTTON_3,
    USER_BUTTON_4,
    USER_BUTTON_5,
    USER_BUTTON_6,
    USER_BUTTON_7,
    USER_BUTTON_8,
    USER_BUTTON_9,
    USER_BUTTON_10,
    USER_BUTTON_11,
    USER_BUTTON_MAX
} user_button_t;

struct key_tag{
    u32 id;
    u8 pressed_logic_level;
    u8 click_cnt;
    u8 trigger_mode;
    u8 trigger_sta;
	bool logic_level;
    u32 pre_press_timestamp;
    u32 pre_release_timestamp;
    u32 now_press_timestamp;
    u32 now_release_timestamp;
    u32 max_multiple_clicks_interval;
	u8 key_sta;
};


enum trigger_mode{
    TIRGGER_MODE_NONE,
    TRIGGER_FALLING_MODE,
    TRIGGER_RISING_MODE
    
};

enum trigger_sta{
    TRIGGER_STA_NONE,
    TRIGGER_STA_RISING,
    TRIGGER_STA_FALLING
};

enum key_sta{
    KEY_STA_NONE,
    KEY_STA_PRESS_DOWN,
    KEY_STA_PRESS_CLICK,
    KEY_STA_PRESS_DOUBLE_CLICK,
    KEY_STA_PRESS_REPEAT_CLICK    
};



extern struct key_tag us_key[USER_BUTTON_MAX];

void key_init(void);
void key_scan_process(void *data);
void key_scan_stop_process(void *data);

#ifdef __cplusplus
}
#endif

#endif /* __BXE_MATRIX_KEYBOARD_WAKEUP_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
