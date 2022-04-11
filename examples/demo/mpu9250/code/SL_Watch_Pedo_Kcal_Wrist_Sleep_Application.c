
#include "SL_Watch_Pedo_Kcal_Wrist_Sleep_Algorithm.h"
#include "bx_dbg.h"
#include "stdlib.h"



#if SL_Sensor_Algo_Release_Enable==0x00
#include "usart.h"
extern signed short          SL_DEBUG_DATA[10][128];
extern unsigned char         SL_DEBUG_DATA_LEN;
extern unsigned char         sl_sleep_sys_cnt ;
#endif

#if SL_Sensor_Algo_Release_Enable==0x00
extern signed short          SL_ACCEL_DATA_Buf[3][16];
extern unsigned char         SL_FIFO_ACCEL_PEDO_NUM;
signed short                 hp_buf[16];
#endif


#define SL_SC7A20_SPI_IIC_MODE  1
/***SL_SC7A20_SPI_IIC_MODE==0  :SPI*******/
/***SL_SC7A20_SPI_IIC_MODE==1  :IIC*******/

static signed char sl_init_status=0x00;
/**Please modify the following parameters according to the actual situation**/
signed char SL_SC7A20_PEDO_KCAL_WRIST_SLEEP_INIT(void)
{
	unsigned char  fifo_status       =0;
	unsigned char  sl_person_para[4] ={178,60,26,1};
	unsigned char  Turn_Wrist_Para[2]={1,3};//refer pdf
/*****if use spi mode please config first******/    
#if SL_SC7A20_SPI_IIC_MODE == 0//spi
    sl_init_status=SL_SC7A20_Driver_Init(1,0x04);//iic mode pull up config 
	//init sensor
	sl_init_status=SL_SC7A20_Driver_Init(0,0x04);//spi or iic select
#else//i2c
 	//sl_init_status=SL_SC7A20_Driver_Init(1,0x00);//spi or iic select   
	sl_init_status=SL_SC7A20_Driver_Init(1,0x08);//spi or iic select   ///add by chj 0428
	//0x08-->close sdo pull up
#endif
    /**********sc7a20 fifo test***************/
	//fifo_status=SL_SC7A20_FIFO_TEST();
	
    /**********set pedo sensitivity***********/
    SL_PEDO_TH_SET(26,10,0,40);//36 12 0 20 for motor
	/*which axis used to pedo depend on algo**/
	SL_PEDO_SET_AXIS(3);
    /**********set int para*******************/
    SL_PEDO_INT_SET(3,2,1);//0 or 1 sleep is different
	/**********set motion para****************/
	SL_Pedo_Person_Inf_Init(&sl_person_para[0]);//personal para init
    /**********set turn wrist para************/
    SL_Turn_Wrist_Init(&Turn_Wrist_Para[0]);
    /**********set sleep sensitivity**********/
    SL_Sleep_Para(120,10,1);
	
	return sl_init_status;
}

static unsigned int   SL_STEP                  = 0;
static unsigned int   SL_STEP_TEMP             = 0;
static unsigned char  SL_STEP_MOTION           = 0;
static unsigned int	  SL_DISTANCE              = 0;
static unsigned int	  SL_KCAL                  = 0;    
static unsigned char  SL_CADENCE_STEP          = 0;//step per minutes
static unsigned short SL_CADENCE_AMP           = 0;//Equal scale scaling 
static unsigned char  SL_CADENCE_DEGREE        = 0;//degree
static signed char    SL_WRIST                 = 0;

static unsigned char  SL_SLEEP_ACTIVE          = 0;
static unsigned char  SL_SLEEP_STATUS          = 0;
static unsigned char  SL_SLEEP_ADOM            = 0;
static unsigned char  SL_SLEEP_CNT             = 0;


static unsigned char  SL_INT_TIME_CNT          = 0;
#define SL_INT_TIME_TH   12  //per lsb is 0.5s
extern unsigned char sl_sleep_sys_hour;
unsigned char SL_MCU_SLEEP_ALGO_FUNCTION(void);

static unsigned int  no_move_count =0;
signed short		  SC7A20_XYZ_Buf[3][16];
char hand_easy_button_occur =0;
short AccelTrend = 0;
short x_v,y_v, z_v =0,z_v_old=0;
char hand_camera_button_occur =0;
#define CAMERA_THRESHOLD 170
static int steps_pre =0;
unsigned int SL_GET_NO_MOVE_COUNT(void)
{
	return no_move_count;
}

char hand_on_occur_get(void)
{
	return hand_easy_button_occur;
}
void hand_on_occur_clear(void)
{
	 hand_easy_button_occur =0;
}

void SL_CHECK_REG(void)
	{
	
	unsigned char val_20,val_23,val_24;
		//bmi160_read(0,0x20,&val_20,1);
		//bmi160_read(0,0x23,&val_23,1);
		//bmi160_read(0,0x24,&val_24,1);
		SL_SC7A20_I2c_Spi_Read(0,0x20,1,&val_20);
		SL_SC7A20_I2c_Spi_Read(0,0x23,1,&val_23);
		SL_SC7A20_I2c_Spi_Read(0,0x24,1,&val_24);
		
		bx_logln(" reg =%x,%x,%x\n",val_20,val_23,val_24 );

		if(val_20 != 0x47 || val_23 != 0x98 ||( val_24 != 0x40 && val_24 != 0x42 ) )
			{
			SL_SC7A20_PEDO_KCAL_WRIST_SLEEP_INIT();
			//pedo_reset_step_count_tmp(); //// need fix
			}
	
	}


//extern bool disp_on_from_raise_hand(void);
//extern	bool display_is_on(void);

uint8_t hand_easy_button_recognition(short x,short y,short z)
{
	static uint8_t axis_status=0;//0:nvertical 1:vertical
   	static unsigned int vertical_time_cnt=0,nvertical_time_cnt=0;
   	uint8_t press = 0;//0:void, others:occur

	

	//if( 1 != motionx_get_handon_set())
	//{
	//	return 0;
	//}

//	if(disp_on_from_raise_hand()==true && display_is_on())
//	{
//					if(z<0|| y < -240 || y > 50  || x< -161 ||x > 161  )
//					{
//						//set_hand_off_event();
//						return 2;
//					}
//	}
//	else
//	{
		if((y> -200 && y<=0)  && (x >= -112 && x <= 112) && z >0 )
		{
			vertical_time_cnt++;
			nvertical_time_cnt=0;
		}
		else
		{
			
			vertical_time_cnt=0;
			if(z<0|| y < -240 || y > 50  || x< -161 ||x > 161  )
			{
				nvertical_time_cnt++;
			}
			else
			{
				nvertical_time_cnt=0;
			}
		}
//	}

	if (vertical_time_cnt >= 5)
		{
			if (0 == axis_status)
			{
				axis_status = 1;
				press = 1;
			}
		}
		else if (nvertical_time_cnt >= 4)
		{
			axis_status = 0;
		}
		else
		{
			//do nothing
		}

		
		//NRF_LOG_DEBUG(" vertical=%d,nvertical=%d ,press=%d,axis_status=%d\n",vertical_time_cnt,nvertical_time_cnt ,press,axis_status);

	
	return press;

}

unsigned int  SL_SC7A20_PEDO_KCAL_WRIST_SLEEP_ALGO(void)
{
#if SL_Sensor_Algo_Release_Enable==0x00
	unsigned char         sl_i;
#endif
	signed short          SC7A20_XYZ_Buf[3][16];
	unsigned char         SC7A20_FIFO_NUM;
	unsigned char         SC7A20_INT_STATUS;
	
	int x_count=0,y_count=0,z_count=0,trendmax=0,len =10;
	 int steps=0;
	 
	if(sl_init_status!=SL_SC7A20_CHIP_ID_VALUE)	return 0;//initial fail

    /*******read int status******/
	SC7A20_INT_STATUS=SL_INT_STATUS_READ();
	if((SC7A20_INT_STATUS==1)||(SL_STEP_TEMP!= SL_STEP))
	{
		SL_INT_TIME_CNT =0;
		SL_STEP_TEMP    =SL_STEP;
	}
	else
	{
		if(SL_INT_TIME_CNT<200)
		{
			SL_INT_TIME_CNT++;
		}
	}
	//LOG_RAWC(" SL_INT_TIME_CNT=%d\n",SL_INT_TIME_CNT );
	if(SL_INT_TIME_CNT<SL_INT_TIME_TH)//5s
	{
	    /*******get sc7a20 FIFO data******/
		SC7A20_FIFO_NUM= SL_SC7A20_Read_FIFO();	
        /*******get pedo value************/
	    SL_STEP= SL_Watch_Pedo_Kcal_Algo();

		//LOG_RAWC("SL_STEP =%d\n",SL_STEP);

		SC7A20_FIFO_NUM=SL_SC7A20_GET_FIFO_Buf(&SC7A20_XYZ_Buf[0][0],&SC7A20_XYZ_Buf[1][0],&SC7A20_XYZ_Buf[2][0]);
		for(int i=0;i<SC7A20_FIFO_NUM;i++)
			{
				SC7A20_XYZ_Buf[0][i] = (SC7A20_XYZ_Buf[0][i] >> 5);
				SC7A20_XYZ_Buf[1][i] = (SC7A20_XYZ_Buf[1][i] >> 5);
				SC7A20_XYZ_Buf[2][i] = (SC7A20_XYZ_Buf[2][i] >> 5);
		
				/// need fix
				if(hand_easy_button_occur == 0)
					hand_easy_button_occur = hand_easy_button_recognition(SC7A20_XYZ_Buf[0][i],SC7A20_XYZ_Buf[1][i],SC7A20_XYZ_Buf[2][i]);
				 
			}
		
			
			steps = SL_STEP - steps_pre;
			steps_pre = SL_STEP;
		
			//LOG_RAWC("x =%d,y=%d,z=%d,steps=%d\n",SC7A20_XYZ_Buf[0][0] ,SC7A20_XYZ_Buf[1][0] ,SC7A20_XYZ_Buf[2][0],steps );
			
		
			if(SC7A20_FIFO_NUM==0 || SC7A20_FIFO_NUM >16)
			{
				
				//NRF_LOG_DEBUG(" x =%d,y=%d ,z=%d,steps=%d\n",SC7A20_XYZ_Buf[0][0] ,SC7A20_XYZ_Buf[1][0] ,SC7A20_XYZ_Buf[2][0],steps );
				return steps;
			}
		
		
			
			if(SC7A20_FIFO_NUM<10 )
				len=SC7A20_FIFO_NUM;
			
				 for(int  i=0;i< len;i++)
				  {
					  x_count+=SC7A20_XYZ_Buf[0][i];
					  y_count+=SC7A20_XYZ_Buf[1][i];
					 z_count+=SC7A20_XYZ_Buf[2][i];
				 }
				 x_v = x_count/len;y_v = y_count/len;z_v = z_count/len;
		
				 for(int  i=0;i< len;i++)
				 {
						if(abs(SC7A20_XYZ_Buf[0][i] - x_v)>trendmax)
							trendmax=abs(SC7A20_XYZ_Buf[0][i] - x_v);
		
						if(abs(SC7A20_XYZ_Buf[1][i] - y_v)>trendmax)
							trendmax=abs(SC7A20_XYZ_Buf[1][i] - y_v);
		
						if(abs(SC7A20_XYZ_Buf[2][i] - z_v)>trendmax)
							trendmax=abs(SC7A20_XYZ_Buf[2][i] - z_v);
				 }
				 AccelTrend = trendmax;
		
				 if(AccelTrend < 25)
					no_move_count++;
				 else if(AccelTrend > 30)
					no_move_count=0;
				 
				 if(AccelTrend>CAMERA_THRESHOLD)
					hand_camera_button_occur=1;

#if 0


	    /*********get sleep active degree value*********/
		SL_SLEEP_ACTIVE=SL_Sleep_Active_Degree(0);
		
	    /*******get accel orginal data and length*******/
	    SC7A20_FIFO_NUM=SL_SC7A20_GET_FIFO_Buf(&SC7A20_XYZ_Buf[0][0],&SC7A20_XYZ_Buf[1][0],&SC7A20_XYZ_Buf[2][0]);
    
		/* SL_Pedo_GetMotion_Status */
		SL_STEP_MOTION       = SL_Pedo_GetMotion_Status();
		/* SL_Pedo_Step_Get_Distance */
		SL_DISTANCE          = SL_Pedo_Step_Get_Distance();
		/* SL_Pedo_Step_Get_KCal */
		SL_KCAL              = SL_Pedo_Step_Get_KCal();
		/*****average step per minutes****/    
		SL_CADENCE_STEP      = SL_Pedo_Step_Get_Step_Per_Min();
		/*****average amp per step****/    
		SL_CADENCE_AMP       = SL_Pedo_Step_Get_Avg_Amp();
		/*****motion degree****/    
		SL_CADENCE_DEGREE    = SL_Pedo_Step_Get_Motion_Degree();
    
//	    if(SL_STEP>200)
//	    {
	        /**reset pedo value**/
//	        SL_Pedo_Kcal_ResetStepCount();
//	    }
    
	    /*******get wrist value******/
	    SL_WRIST= SL_Watch_Wrist_Algo();

#endif
    
	}
	else
	{
	    //sc7a20 's data for heart rate algo
		//SC7A20_FIFO_NUM= SL_SC7A20_Read_FIFO();	
	    //SC7A20_FIFO_NUM= SL_SC7A20_GET_FIFO_Buf(&SC7A20_XYZ_Buf[0][0],&SC7A20_XYZ_Buf[1][0],&SC7A20_XYZ_Buf[2][0]);	
		SL_Turn_Wrist_Reset();
		SC7A20_FIFO_NUM=0;
	}


#if 0

	/*******get sleep status value******/
	SL_SLEEP_CNT++;
#if SL_Sensor_Algo_Release_Enable==0x00
	if(SL_SLEEP_CNT>39)//1min
#else
	if(SL_SLEEP_CNT>119)//1min	
#endif
	{
#if SL_Sensor_Algo_Release_Enable==0
		sl_sleep_sys_cnt++;
		if(sl_sleep_sys_cnt>59)//min
		{
			sl_sleep_sys_cnt=0;
			sl_sleep_sys_hour++;//hour
			if(sl_sleep_sys_hour==24)
				sl_sleep_sys_hour=0;
		}
#endif
		SL_SLEEP_CNT=0;
		SL_MCU_SLEEP_ALGO_FUNCTION();
	}

#if SL_Sensor_Algo_Release_Enable==0x00
	SL_DEBUG_DATA_LEN=SC7A20_FIFO_NUM;
	for(sl_i=0;sl_i<SL_DEBUG_DATA_LEN;sl_i++)
	{       
		SL_DEBUG_DATA[0][sl_i]=SC7A20_XYZ_Buf[0][sl_i];
		SL_DEBUG_DATA[1][sl_i]=SC7A20_XYZ_Buf[1][sl_i];
		SL_DEBUG_DATA[2][sl_i]=SC7A20_XYZ_Buf[2][sl_i];
		SL_DEBUG_DATA[3][sl_i]=SL_STEP;
		SL_DEBUG_DATA[4][sl_i]=SL_WRIST;
//        SL_DEBUG_DATA[4][sl_i]=SL_CLOCK_STATUS;
		SL_DEBUG_DATA[5][sl_i]=SL_SLEEP_STATUS;
//        SL_DEBUG_DATA[5][sl_i]=SL_SWAY_STATUS; 
		SL_DEBUG_DATA[6][sl_i]=SL_STEP_MOTION;  
//		SL_DEBUG_DATA[7][sl_i]=SL_DISTANCE;
		SL_DEBUG_DATA[7][sl_i]=hp_buf[sl_i];
		SL_DEBUG_DATA[8][sl_i]=SL_KCAL;
		SL_DEBUG_DATA[9][sl_i]=SL_CADENCE_STEP;
//        SL_DEBUG_DATA[8][sl_i]=SL_CADENCE_AMP;
//        SL_DEBUG_DATA[9][sl_i]=SL_CADENCE_DEGREE;	
	}
#endif
#endif
   return steps;

   // return SL_STEP;
}

#if SL_Sensor_Algo_Release_Enable==0x00
unsigned short sl_sleep_counter=0;
#endif
#define SL_SLEEP_DEEP_TH   6
#define SL_SLEEP_LIGHT_TH  3
/***Call this function regularly for 1 minute***/
#if 0

unsigned char SL_MCU_SLEEP_ALGO_FUNCTION(void)
{

	/*******get sleep status value******/
	SL_SLEEP_STATUS= SL_Sleep_GetStatus(sl_sleep_sys_hour);
	SL_SLEEP_ACTIVE= SL_Sleep_Get_Active_Degree();
	SL_SLEEP_ADOM  = SL_Adom_GetStatus();
	
#if SL_Sensor_Algo_Release_Enable==0x00
	sl_sleep_counter++;
	USART_printf( USART1, "step=%d! sys_time=%d!\r\n",SL_STEP,sl_sleep_sys_hour);
	USART_printf( USART1, "T=%d,sleep_status:%d,sleep_adom:%d!\r\n",sl_sleep_counter,SL_SLEEP_STATUS,SL_SLEEP_ADOM);
	USART_printf( USART1, "SL_SLEEP_ACTIVE:%d!\r\n",SL_SLEEP_ACTIVE);
#endif
	
	if(SL_SLEEP_STATUS<SL_SLEEP_LIGHT_TH)
	{
		return 0;//0 1 2 3
	}
	else if(SL_SLEEP_STATUS<SL_SLEEP_DEEP_TH)
	{
		return 1;//4 5 6
	}
	else
	{
		return 2;//7
	}
}
#endif
