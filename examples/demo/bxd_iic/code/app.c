/**
  ******************************************************************************
  * @file   :   main.c
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
#include "app.h"
#include "bx_pm.h"
#include "bxd_iic.h"
#include "lis3dsh_iic.h"
#include "plf.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


uint8_t iic_data[3] = {0x77, 0x02, 0x04};
uint8_t iic_readbuf[3] = {0};
uint8_t lis3_data[2] = {0x8f, 0x00};





/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    bx_pm_lock( BX_PM_IIC );//��IICʱ��Դ
    bxd_iic_open( BX_IIC0 ); //ѡ��IIC���ͣ�IICO��IIC1��
    bxd_iic_set_scl( BX_IIC0, 2 ); //����P02Ϊʱ����
    bxd_iic_set_sda( BX_IIC0, 3 ); //����P03Ϊ������
    bxd_iic_set_addr_bit( BX_IIC0, BX_IIC_ADDR_BIT_7B ); //ѡ��7λ��ַѰַģʽ
    bxd_iic_set_speed( BX_IIC0, BX_IIC_SPEED_STANDARD ); //ѡ���׼�������
    bxd_iic_set_mode( BX_IIC0, BX_IIC_MODE_MASTER ); //ѡ��IIC����ģʽ


    //����ʹ��lis3dsh������ٶ�ģ������ʾ����
    iic_read_lis3dsh( 0x0f, iic_readbuf, 3 );//��ȡWHO_AM_I��ֵ
    if( iic_readbuf[0] == UC_WHO_AM_I_DEFAULT_VALUE ) {
        bx_logln( "device ID=%02x\r\n", iic_readbuf[0] );
        iic_write_lis3dsh( ADD_REG_CTRL_4, iic_data, 3 );//��ӻ��Ĵ���д����
        iic_read_lis3dsh( ADD_REG_CTRL_4, iic_readbuf, 3 );//�ӼĴ���������
        if( iic_readbuf[0] == 0x77 ) {
            bx_logln( "read and write success\r\n" );//ȷ�϶�д�ɹ�
            bx_dwork( read_lis3dsh, NULL, 1000, BX_FOREVER );//IIC��ȡ���ٶ�����

        }

    } else {
        bx_logln( "device get failed\r\n" );
    }

}

void read_lis3dsh( void * arg )
{
    iic_read_lis3dsh( 0x28, iic_readbuf, 1 );
    bx_logln( "XL=%d", iic_readbuf[0] );
    iic_read_lis3dsh( 0x29, iic_readbuf, 1 );
    bx_logln( " XH=%d\r\n", iic_readbuf[0] );
    iic_read_lis3dsh( 0x2a, iic_readbuf, 1 );
    bx_logln( "YL=%d", iic_readbuf[0] );
    iic_read_lis3dsh( 0x2b, iic_readbuf, 1 );
    bx_logln( " YH=%d\r\n", iic_readbuf[0] );
    iic_read_lis3dsh( 0x2c, iic_readbuf, 1 );
    bx_logln( "ZL=%d", iic_readbuf[0] );
    iic_read_lis3dsh( 0x2d, iic_readbuf, 1 );
    bx_logln( " ZH=%d\r\n", iic_readbuf[0] );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



