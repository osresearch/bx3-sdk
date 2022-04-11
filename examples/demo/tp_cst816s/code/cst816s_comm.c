#include <cst816s_comm.h>
#include <bxd_iic.h>
#include <bxd_gpio.h>
#include <bx_pm.h>
#include <plf.h>
#include <bx_dbg.h>
#include <compiler_flag.h>


#define ADRESS_WRITE    0X2a
#define ADRESS_READ     0X2b

#define ADRESS_UPWRITE 0Xd4
#define ADRESS_UPREAD 0Xd5

#define CHIP_ADDRESS    (0x2a)//
#define CHIP_UPD_ADDARESS   (0xD4)

extern unsigned char hynitron_cst816s_update[];

void cst816s_reset( void )
{
    bx_pm_lock( BX_PM_GPIO );
    bxd_gpio_open( BX_GPIOA );
    bxd_gpio_set_mode( BX_GPIOA, 7, BX_GPIO_MODE_OUTPUT );
    bxd_gpio_write( BX_GPIOA, 7, 0 );
    BX_DELAY_US( 10000 );
    bxd_gpio_write( BX_GPIOA, 7, 1 );
    BX_DELAY_US( 10000 );

}

void iic_init( void )
{
    bx_pm_lock( BX_PM_IIC );
    bxd_iic_open( BX_IIC1 );
    bxd_iic_set_scl( BX_IIC1, 3 );
    bxd_iic_set_sda( BX_IIC1, 5 );
    bxd_iic_set_speed( BX_IIC1, BX_IIC_SPEED_STANDARD );
    bxd_iic_set_addr_bit( BX_IIC1, BX_IIC_ADDR_BIT_7B );
    bxd_iic_set_mode( BX_IIC1, BX_IIC_MODE_MASTER );
}

void cst816s_init( void )
{
    //TP RST PIN INIT
#if(TP_RST_PIN != 0xFF)
    bx_pm_lock( BX_PM_GPIO );
    bxd_gpio_open( BX_GPIOA );
    bxd_gpio_set_mode( BX_GPIOA, 7, BX_GPIO_MODE_OUTPUT );
    bxd_gpio_set_pull( BX_GPIOA, 7, BX_GPIO_PULLUP );
    bxd_gpio_write( BX_GPIOA, 7, 0 );
    BX_DELAY_US( 40 );
    bxd_gpio_write( BX_GPIOA, 7, 1 );
#endif
}

int cst816s_enter_bootmode( void )
{
    char retryCnt = 10;
    int ret = -1;

    iic_init();
   
    cst816s_reset();

    uint16_t reg_addr1, reg_addr2;
    reg_addr1 = 0xA001;
    reg_addr2 = 0xA003;
    bx_logln( "cst816s_enter_bootmode" );
    while( retryCnt-- ) {
        uint8_t cmd[3];

#ifdef __CST_716__
        cmd[0] = 0xAA;
#else
        cmd[0] = 0xAB;
#endif
      BX_DELAY_US(5000);
        bx_logln("1");
        if( bxd_iic_write_16( BX_IIC1, CHIP_UPD_ADDARESS, reg_addr1, cmd, 1 ) ) {
            continue;
            bx_logln("123");
        }
        bx_logln("2");
        BX_DELAY_US( 2000 );

        if( bxd_iic_read_16( BX_IIC1, CHIP_UPD_ADDARESS, reg_addr2, cmd, 1 ) == 0 ) {
            BX_DELAY_US( 2000 );
            bx_logln( "cmd=%x\r\n", cmd[0] );
            if( cmd[0] != 0x55 ) {
                BX_DELAY_US( 2000 );
                continue;
            } else {
                ret = 0;
                break;
            }
        }
          bx_logln("3");
    }

    if( ret == 0 ) {
        bx_logln( "\r\n++++++++++enter bootmode Success!!!!\r\n" );
    } else {
        bx_logln( "\r\n----------enter bootmode Failed!!!!\r\n" );
    }

    bx_logln("4");
    return ret;



}

static void cst816s_exit_bootmode( void )
{
    uint8_t cmd[3];
    uint16_t reg_addr1 = 0xA003;
    //iic0.param.mem_addr_bit_num = IIC_16BIT_MEMORY_ADDRESS;
    // exit program mode
    cmd[0] = 0x00;
    //hctp_write_bytes(0xA003,cmd,1,REG_LEN_2B);
//  bx_iic_write(&iic0.inst,&cmd[0], 1, CHIP_UPD_ADDARESS, reg_addr1, 10 );
    bxd_iic_write_16( BX_IIC1, CHIP_UPD_ADDARESS, reg_addr1, &cmd[0], 1 );

    BX_DELAY_US( 100000 );

    bx_logln( "********** TP Exit Bootmode\r\n" );

    cst816s_reset();
    BX_DELAY_US( 10000 ); //delay 10ms

//  cst816s_set_memaddrlen(IIC_8BIT_MEMORY_ADDRESS);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
#define PER_LEN 512
#define FLASH_UPDATE_ADDRESS    0x40000//暂时使用此地址。
typedef struct _tagTPUPDHeader {
    uint16_t address;
    uint16_t length;
    uint16_t chksum;
} TP_UPD_HEADER;

static uint32_t cst816s_read_checksum( void )
{
    union {
        uint32_t sum;
        uint8_t buf[4];
    } checksum;
    char cmd[3];
//  char readback[4] = {0};
    uint16_t reg_addr1, reg_addr2;


    //if (cst816s_enter_bootmode() == -1){
    //  return 0xFFFF;
    //}

    reg_addr1 = 0xA003;
    reg_addr2 = 0xA008;

    cmd[0] = 0;
    //iic0.param.mem_addr_bit_num = IIC_16BIT_MEMORY_ADDRESS;

//  if( bx_iic_write(&iic0.inst,(uint8_t *)(&cmd[0]), 1, CHIP_UPD_ADDARESS, reg_addr1, 10 ) )
    if( bxd_iic_write_16( BX_IIC1, CHIP_UPD_ADDARESS, reg_addr1, ( uint8_t * )( &cmd[0] ), 1 ) ) {
        //iic0.param.mem_addr_bit_num = IIC_8BIT_MEMORY_ADDRESS;

        bx_logln( "---------- read chip checksum fail\r\n" );
        return 0xFFFF;
    }
    BX_DELAY_US( 500000 );

    checksum.sum = 0;
//  if( bx_iic_read( &iic0.inst, &checksum.buf[0], 2, CHIP_UPD_ADDARESS, reg_addr2, 10))
    if( bxd_iic_read_16( BX_IIC1, CHIP_UPD_ADDARESS, reg_addr2, &checksum.buf[0], 2 ) ) {
        //iic0.param.mem_addr_bit_num = IIC_8BIT_MEMORY_ADDRESS;
        bx_logln( "---------- read chip checksum fail\r\n" )  ;
        return 0xFFFF;
    }

    bx_logln( "++++++++++chip chksum = %04X\r\n", checksum.sum );
    return checksum.sum;

}

static int cst816s_update_handle( uint16_t startAddr, uint16_t len )
{
    uint16_t sum_len;
    uint8_t cmd[10];
    uint8_t appbin[PER_LEN];
    uint8_t * p_data;
    uint8_t index = 0;
    int i;
    int ret = -1;

    //if (cst816s_enter_bootmode() == -1){
    // return ret;
    //}
//    wdt_ext_feed();



    //iic0.param.mem_addr_bit_num = IIC_16BIT_MEMORY_ADDRESS;

    p_data = &hynitron_cst816s_update[0];


    sum_len = 0;
    do {
        if ( sum_len >= len ) {
            ret = 0;
            break;
        }

        //spiflash_read_buffer(appbin, FLASH_UPDATE_ADDRESS+index*PER_LEN+6, PER_LEN );
        for( int i = 0; i < PER_LEN; i++ ) {
            //appbin[i] = hynitron_cst816s_update[index*PER_LEN+6 +i];
            appbin[i] = p_data[index * PER_LEN + 6 + i];
        }

        cmd[0] = startAddr & 0xFF;
        cmd[1] = startAddr >> 8;
//        bx_iic_write(&iic0.inst,&cmd[0], 2, CHIP_UPD_ADDARESS, 0xA014, 50 );
        bxd_iic_write_16( BX_IIC1, CHIP_UPD_ADDARESS, 0xA014, &cmd[0], 2 );
        BX_DELAY_US( 5000 );

#if 1
        for( i = 0; i < 4; i++ ) {
//              bx_iic_write(&iic0.inst,&appbin[128*i], PER_LEN/4, CHIP_UPD_ADDARESS, 0xA018+128*i, 50 );
            bxd_iic_write_16( BX_IIC1, CHIP_UPD_ADDARESS, 0xA018 + 128 * i, &appbin[128 * i], PER_LEN / 4 );
            //BX_DELAY_US(10000);
        }

#else
        bx_iic_write( &iic0.inst, &appbin[0], PER_LEN, CHIP_UPD_ADDARESS, 0xA018, 300 );
        BX_DELAY_US( 1000 );
#endif


        cmd[0] = 0xEE;
//        bx_iic_write(&iic0.inst,&cmd[0], 1, CHIP_UPD_ADDARESS, 0xA004, 50 );
        bxd_iic_write_16( BX_IIC1, CHIP_UPD_ADDARESS, 0xA004, &cmd[0], 1 );
        BX_DELAY_US( 150000 );


        int timeout = 50;
        for( i = 0; i < timeout; i++ ) {
//              wdt_feed();
//
//              wdt_ext_feed();
            BX_DELAY_US( 50000 );
//              if( bx_iic_read( &iic0.inst, &cmd[0], 1, CHIP_UPD_ADDARESS, 0xA005, 50)==0)
            if( bxd_iic_read_16( BX_IIC1, CHIP_UPD_ADDARESS, 0xA005, &cmd[0], 1 ) == 0 ) {
                if( cmd[0] == 0x55 ) {
                    break;
                }
            }
        }
//          wdt_ext_feed();

        if( i >= timeout ) {
            break;
        }

        startAddr += PER_LEN;
        sum_len += PER_LEN;
        index++;

        bx_logln( "*** Tp Upd %%%d...\r\n", sum_len * 100 / len );
    } while( len );


    if( ret == 0 ) {
        bx_logln( "++++++++++ TP Update Succeed!\r\n" );
    } else {
        bx_logln( "---------- TP Update Failed\r\n" );
    }
    //cst816s_exit_bootmode();

    return ret;

}

uint16_t   cst816_sum = 0;
//extern const flash_img_by_struct htximginfo[];

int cst816s_update( void )
{
    uint8_t appbin[8];
    TP_UPD_HEADER * ptuh = ( TP_UPD_HEADER * )appbin;
    int ret = -1;

    //spiflash_read_buffer(appbin, FLASH_UPDATE_ADDRESS, sizeof(appbin) );


    for( int i = 0; i < 8; i++ ) {
        appbin[i] = hynitron_cst816s_update[i];
    }

//  wdt_feed();
    if( cst816s_enter_bootmode() == 0 ) {

        cst816_sum =  cst816s_read_checksum();
        if( cst816_sum != ptuh->chksum ) {

            cst816s_update_handle( ptuh->address, ptuh->length );

            BX_DELAY_US( 10000 );
            cst816_sum =  cst816s_read_checksum();
        }

        //  cst816_sum =  cst816s_read_checksum();

        if( cst816_sum == ptuh->chksum ) {
            bx_logln( "*** TP chksum OK! Update Success! ***" );
            ret = 0;
        } else {
            bx_logln( "*** TP chksum err! Update Fail! ***" );
        }
    }
    BX_DELAY_US( 10000 );


    cst816s_exit_bootmode();

    return ret;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

//--------------获取坐标函数----------------//
#define REG_XPOS_H		0x03
int cst816s_get_xypos(short *x, short *y)
{
	uint8_t xypos[4]={0};
	
	//iic_busy_flag = true;
	//app_iic_read(&iic0.inst, xypos, 4, CHIP_ADDRESS, REG_XPOS_H, iic_transfer_cb, NULL );
	//iic_wait_done();
//	bx_iic_read(&iic0.inst, xypos, 4, CHIP_ADDRESS, REG_XPOS_H, 10 );
  bxd_iic_read(BX_IIC1,CHIP_ADDRESS,REG_XPOS_H,xypos,4);
  

	*x = ((short)xypos[1] | ((short)(xypos[0]&0x0F)<<8)) & 0x7FFF;
	*y = ((short)xypos[3] | ((short)(xypos[2]&0x0F)<<8)) & 0x7FFF;
//  *x = ((short)xypos[1] | ((short)xypos[0]<<8)) & 0x7FFF;
//	*y = ((short)xypos[3] | ((short)xypos[2]<<8)) & 0x7FFF;

 	 bx_logln("cst816s_get_xypos (x = %d, y=%d) state=0x%x\r\n", *x, *y, (xypos[0]&0xF0) );

	 return( xypos[0]&0xf0 );	 
}
uint8_t tpchipid=0;
void cst816s_readid(void)
{

	//while(1)
	{
	//i2c_read(&i2c_dev_tp, REG_CHIP_ID, &chipid, 1);

	//LOG_RAW("cst816s init, chipid = %x\r\n", chipid);

	//chipid= 0x00;
//	app_iic_read(&iic0.inst, &chipid, 1, CHIP_ADDRESS, REG_CHIP_ID, iic_transfer_cb, NULL );
	
//	bx_iic_read(&iic0.inst,  &tpchipid, 1, CHIP_ADDRESS, REG_CHIP_ID, 40 );
    bxd_iic_read(BX_IIC1,CHIP_ADDRESS,REG_CHIP_ID,&tpchipid,1);
    bx_logln("iic_read_finish\r\n");
	
	if( tpchipid != 0x00)
	{
		bx_logln("tp_init ok, tpchipid=%x\r\n", tpchipid);
	}
	else
		bx_logln("tp init fail\r\n");

	}
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t cst816s_guesture_id(void)
{
	uint8_t guestureid = 0;
	//iic_busy_flag = true;
	//app_iic_read(&iic0.inst, &guestureid, 1, CHIP_ADDRESS, REG_GESTUREID, iic_transfer_cb, NULL );
	//iic_wait_done();
	bxd_iic_read(BX_IIC1, CHIP_ADDRESS, REG_GESTUREID, &guestureid, 1 );
//	bx_logln("cst816s_guesture_id = %x, rtc.second=%d\r\n", guestureid, rtc_get_time()->second );
	return guestureid;
}
