#ifndef __CST816S_COMM_H_
#define __CST816S_COMM_H_

#include <stdint.h>
#include <stdbool.h>


#define REG_GESTUREID	0x01
#define REG_FINGERNUM	0x02
#define REG_XPOS_H		0x03
#define REG_XPOS_L		0x04
#define REG_YPOS_H		0x05
#define REG_YPOS_L		0x06

#define REG_BPC0_H		0xB0
#define REG_BPC0_L		0xB1
#define REG_BPC1_H		0xB2
#define REG_BPC1_L		0xB3

#define REG_CHIP_ID		0xA7
#define REG_PROJ_ID		0xA8
#define REG_FW_VERSION	0xA9

#define REG_MOTION_MNASK	0xEC
#define REG_IRQPLUS_WIDTH	0xED
#define REG_NORSCAN_PER		0xEE
#define REG_MOTION_SL_ANGLE	0xEF

#define REG_LP_SCANRAW_1H	0xF0
#define REG_LP_SCANRAW_1L	0xF1
#define REG_LP_SCANRAW_2H	0xF2
#define REG_LP_SCANRAW_2L	0xF3
#define REG_LP_AUTO_WAKETIME 0xF4
#define REG_LP_SCAN_TH		0xF5
#define REG_LP_SCAN_WIN		0xF6
#define REG_LP_SCAN_FREQ	0xF7
#define REG_LP_SCAN_IDAC	0xF8

#define REG_AUTOSLEEP_TIME	0xF9
#define REG_IRQ_CTL			0xFA
#define REG_AUTORESET		0xFB

#define REG_LONGPRESS_TIME	0xFC
#define REG_IOCTL			0xFD
#define REG_DIS_AUTOSLEEP	0xFE



#define GUESTURE_ID_NONE		0x00 	//：无手势
#define GUESTURE_ID_SWIPE_UP	0x01	//：上滑
#define GUESTURE_ID_SWIPE_DOWN	0x02	//：下滑
#define GUESTURE_ID_SWIPE_LEFT	0x03	//：左滑
#define GUESTURE_ID_SWIPE_RIGHT	0x04	//：右滑
#define GUESTURE_ID_CLICK		0x05	//：单击
#define GUESTURE_ID_DBLCLICK	0x0B	//：双击
#define GUESTURE_ID_LONG_PRESS	0x0C	//：长按

#define TP_NO_TOUCH		0x40	//没有触摸
#define TP_FIRST_TOUCH	0x00	//首次触摸
#define TP_HAVE_FINGER	0x80	//有触摸

int cst816s_enter_bootmode(void) ;
void cst816s_reset(void);
void iic_init(void);
void iic_cst816s(void);
int cst816s_update( void );
int cst816s_get_xypos(short *x, short *y);
void cst816s_readid(void);
uint8_t cst816s_guesture_id(void);
void cst816s_init( void );

#endif
