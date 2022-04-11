# 将SDK3.3中修复的bug合并到SDK3.2中

## 1、替换文件

替换SDK3\components\bluex\ble路径下的controller和dbg文件

## 2、更改驱动文件

### 2.1、bx_drv_uart.c

#### 修改前：

```c
static struct uart_baudrate_cfg bd_cfg_hub[] = {
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

    {0, 0, 0, 0, 8},   /*250000*/
    {1, 29, 4, 7, 1},  /*256000*/
    {2, 12, 2, 1, 2},  /*460800*/
    {0, 0, 0, 0, 4},   /*500000*/
    {12, 2, 1, 2, 1},  /*921600*/
    {0,  0, 0, 0, 2},  /*1000000*/
    {0,  0, 0, 0, 1},  /*2000000*/
};
```

```c
bx_err_t bx_drv_uart_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {

	 	NVIC_ClearPendingIRQ( UART0_IRQn );
        BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART0;
        BX_PER->SRST |= PER_SRST_SET_UART0;
        BX_PER->SRST |= PER_SRST_CLR_UART0;
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_DIV_UART0 );
    } else if( BX_UARTx == BX_UART1 ) {
		NVIC_ClearPendingIRQ( UART1_IRQn );
        BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART1;
        BX_PER->SRST |= PER_SRST_SET_UART1;
        BX_PER->SRST |= PER_SRST_CLR_UART1;
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART1, PER_CS_TYPE_16M_DIV_UART1 );
    } else {
        return BX_ERR_INVAL;
    }
    
    BX_UARTx->IF |= UART_IF_FIFO_EN;

    return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        BX_PER->CLKG0 |= PER_CLKG0_32M_CLR_UART0;
        BX_PER->CLKG0 |= PER_CLKG0_PLL_CLR_UART0;
        
    } else if( BX_UARTx == BX_UART1 ) {
        BX_PER->CLKG0 |= PER_CLKG0_32M_CLR_UART1;
        BX_PER->CLKG0 |= PER_CLKG0_PLL_CLR_UART1;
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_write( void * hdl, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    while( len ){
        BX_UARTx->RTD = *buff;
        while( BX_READ_BIT( BX_UARTx->LS, UART_LS_TX_EMPTY ) == 0 );
        buff++;
        len--;
    }
	bx_public(bxs_uart1_id(),BXM_DATA_TX_END,0,0);
    return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_intr_enable( void * hdl )
{
	CHECK_HANDLE( hdl );
	reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    BX_UARTx->DI = ( ( ( uint32_t )0/*ptime*/ << 7 ) \
                       | ( ( uint32_t )0/*edssi, 0: Modem_Status_Interrupt_Disabled, 1: Modem_Status_Interrupt_Enabled*/ << 3 ) \
                       | ( ( uint32_t )1/*elsi, 0: Receiver_Line_Status_Interrupt_Disabled, 1: Receiver_Line_Status_Interrupt_Enabled*/ << 2 ) \
                       | ( ( uint32_t )0/*etbei, 0: Transmit_Holding_Register_Empty_Interrupt_Disabled, 1: Transmit_Holding_Register_Empty_Interrupt_Enabled*/ << 1 ) \
                       | ( ( uint32_t )0/*erbfi, 0: Received_Data_Available_Interrupt_Disabled, 1: Received_Data_Available_Interrupt_Enabled*/ << 0 ) );

    BX_UARTx->IF = ( ( ( uint32_t )0/*rcvr, 0: RCVR_Trigger_One_Character, 1: RCVR_Trigger_FIFO_One_Quarter_Full, 2: RCVR_Trigger_FIFO_Half_Full, 3: RCVR_Trigger_FIFO_Two_Less_Than_Full*/ << 6 ) \
                       | ( ( uint32_t )0/*tet, 0: TX_Empty_Trigger_FIFO_Empty, 1: TX_Empty_Trigger_Two_Characters_In_FIFO, 2: TX_Empty_Trigger_One_Quarter_Full, 3: Tx_Empty_Trigger_Half_Full*/ << 4 ) \
                       | ( ( uint32_t )0/*dmam*/ << 3 ) \
                       | ( ( uint32_t )0/*xfifor*/ << 2 ) \
                       | ( ( uint32_t )0/*rfifor*/ << 1 ) \
                       | ( ( uint32_t )1/*fifoe, 0: FIFO_Disabled, 1: FIFO_Enabled*/ << 0 ) );
	if(BX_UARTx == BX_UART0){
		NVIC_EnableIRQ( UART0_IRQn );
	} else if(BX_UARTx == BX_UART1){
		NVIC_EnableIRQ( UART1_IRQn );
	}else{
		return BX_ERR_INVAL;
	}

	return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_intr_read_start( void * hdl)
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    bx_drv_uart_intr_enable(BX_UARTx);
	BX_SET_BIT(BX_UARTx->DI,UART_DI_IE_RDA_AND_IDLE);

    return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_set_speed( void * hdl, u8 baudrate )
{
    CHECK_HANDLE( hdl );
    CHECK_BAUDRATE( baudrate );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    struct uart_baudrate_cfg * p_cfg = &bd_cfg_hub[baudrate];
    if( BX_UARTx == BX_UART0 ) {
        BX_PER->CDP1  = ( ( ( uint32_t )p_cfg->num1 << 24 )     \
                           | ( ( uint32_t )p_cfg->num0 << 16 )  \
                           | ( ( uint32_t )p_cfg->len1 << 8 )   \
                           | ( ( uint32_t )p_cfg->len0 << 0 ) );
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_DIV_UART0 );            
    } else if( BX_UARTx == BX_UART1 ) {
        BX_PER->CDP2  = ( ( ( uint32_t )p_cfg->num1 << 24 )     \
                           | ( ( uint32_t )p_cfg->num0 << 16 )  \
                           | ( ( uint32_t )p_cfg->len1 << 8 )   \
                           | ( ( uint32_t )p_cfg->len0 << 0 ) );
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART1, PER_CS_TYPE_16M_DIV_UART1 );
    } else {
        return BX_ERR_INVAL;
    }
    BX_UARTx->LC |= 0x80;
    BX_UARTx->RTD = ( uint8_t )p_cfg->div;
    BX_UARTx->DI = ( uint8_t )( p_cfg->div >> 8 );
    BX_UARTx->LC &= ~( ( uint32_t )0x80 );
    return BX_OK;
}
```





#### 修改后：

```c
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
```

```c
bx_err_t bx_drv_uart_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {

	 	NVIC_ClearPendingIRQ( UART0_IRQn );
        BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART0;
        BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_UART0;
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_DIV_UART0 );
    } else if( BX_UARTx == BX_UART1 ) {
		NVIC_ClearPendingIRQ( UART1_IRQn );
        BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART1;
        BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_UART1;
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART1, PER_CS_TYPE_16M_DIV_UART1 );
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        BX_PER->CLKG0 &= ~PER_CLKG0_32M_SET_UART0;
        BX_PER->CLKG0 &= ~PER_CLKG0_PLL_SET_UART0;
        BX_PER->CLKG0 |= PER_CLKG0_32M_CLR_UART0;
        BX_PER->CLKG0 |= PER_CLKG0_PLL_CLR_UART0;
        
    } else if( BX_UARTx == BX_UART1 ) {
        BX_PER->CLKG0 &= ~PER_CLKG0_32M_SET_UART1;
        BX_PER->CLKG0 &= ~PER_CLKG0_PLL_SET_UART1;
        BX_PER->CLKG0 |= PER_CLKG0_32M_CLR_UART1;
        BX_PER->CLKG0 |= PER_CLKG0_PLL_CLR_UART1;
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_write( void * hdl, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    while( len ){
        BX_UARTx->RTD = *buff;
        while( BX_READ_BIT( BX_UARTx->LS, UART_LS_TX_EMPTY ) == 0 );
        buff++;
        len--;
    }
    //以下为修改部分

    return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_intr_enable( void * hdl )
{
	CHECK_HANDLE( hdl );
	reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        NVIC_EnableIRQ( UART0_IRQn );
    } else if( BX_UARTx == BX_UART1 ) {
        NVIC_EnableIRQ( UART1_IRQn );
    } else {
        return BX_ERR_INVAL;
    }

	return BX_OK;
}
```

```c
bx_err_t bx_drv_uart_intr_read_start( void * hdl)
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    BX_UARTx->DI = 0;

    if( BX_UARTx == BX_UART0 ) {
        NVIC_DisableIRQ( UART0_IRQn );
    } else if( BX_UARTx == BX_UART1 ) {
        NVIC_DisableIRQ( UART1_IRQn );
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
```

新增以下代码

```c
bx_err_t bx_drv_uart_intr_read_stop( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    BX_UARTx->DI = 0;
    BX_CLR_BIT( BX_UARTx->IF, UART_IF_FIFO_EN );


    return BX_OK;
}
```

```
bx_err_t bx_drv_uart_set_speed( void * hdl, u8 baudrate )
{
    CHECK_HANDLE( hdl );
    CHECK_BAUDRATE( baudrate );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    struct uart_baudrate_cfg * p_cfg = &bd_cfg_hub[baudrate];
    if( BX_UARTx == BX_UART0 ) {
        BX_PER->CDP1  = ( ( ( uint32_t )p_cfg->num1 << 24 )     \
                          | ( ( uint32_t )p_cfg->num0 << 16 )  \
                          | ( ( uint32_t )p_cfg->len1 << 8 )   \
                          | ( ( uint32_t )p_cfg->len0 << 0 ) );
        if( baudrate > BX_UART_BD_2000000 ) {
            BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_DIV_UART0 );
        } else {
            BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_UART0 );
        }
    } else if( BX_UARTx == BX_UART1 ) {
        BX_PER->CDP2  = ( ( ( uint32_t )p_cfg->num1 << 24 )     \
                          | ( ( uint32_t )p_cfg->num0 << 16 )  \
                          | ( ( uint32_t )p_cfg->len1 << 8 )   \
                          | ( ( uint32_t )p_cfg->len0 << 0 ) );
        if( baudrate > BX_UART_BD_2000000 ) {
            BX_MODIFY_REG( BX_PER->CS, PER_CS_UART1, PER_CS_TYPE_16M_DIV_UART1 );
        } else {
            BX_MODIFY_REG( BX_PER->CS, PER_CS_UART1, PER_CS_TYPE_16M_UART1 );
        }
    } else {
        return BX_ERR_INVAL;
    }
    BX_UARTx->LC |= 0x80;
    BX_UARTx->RTD = ( uint8_t )p_cfg->div;
    BX_UARTx->DI = ( uint8_t )( p_cfg->div >> 8 );
    BX_UARTx->LC &= ~( ( uint32_t )0x80 );
    return BX_OK;
}
```

### 2.2、bx_drv_tim.c

#### 修改前：

#### 修改后：

增加代码：

```c
#include "bx_drv_tim.h"
//以下为新增代码
static timer_intr_cb timer_intr_cb_0 = NULL;
static timer_intr_cb timer_intr_cb_1 = NULL;
```

增加代码：

```c
bx_err_t bx_drv_timer_set_intr_callback( void * hdl, timer_intr_cb cb )
{
    CHECK_HANDLE( hdl );
	if(hdl == BX_TIM0)
	{
		timer_intr_cb_0 =  cb;
	}
	else if(hdl == BX_TIM1)
	{
		timer_intr_cb_1 =  cb;
	}
	else
	{
		return BX_ERR_INVAL;
	}
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void TIMER_IRQHandler( void )
{
    uint32_t timer_isr_status0, timer_isr_status1;
    timer_isr_status0 = BX_TIM0->IS & 0x01;
    timer_isr_status1 = BX_TIM1->IS & 0x01;
    if( timer_isr_status0 ) {
        BX_READ_REG( BX_TIM0->EOI );
		timer_intr_cb_0();
    }
    if( timer_isr_status1 ) {
        BX_READ_REG( BX_TIM1->EOI );
		timer_intr_cb_1();
    }
}
```



### 2.3、bx_drv_spim.c

#### 修改前：

```c
bx_err_t bx_drv_spim_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_spim_t * BX_SPIMx = ( reg_spim_t * )hdl;

    if( BX_SPIMx == BX_SPIM0 ) {
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_SPIM0 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_SPIM0 );
    } else if ( BX_SPIMx == BX_SPIM1 ) {
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_SPIM1 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_SPIM1 );
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
```

```c
bx_err_t bx_drv_spim_set_data_bit( void * hdl, u8 data_bit )
{
    CHECK_HANDLE( hdl );
    CHECK_DATA_BIT( data_bit );

    reg_spim_t * BX_SPIMx = ( reg_spim_t * )hdl;

    BX_MODIFY_REG( BX_SPIMx->CTRL, SPIM_CTRL_DFS32, data_bit );

    return BX_OK;
}
```



#### 修改后：

```c
bx_err_t bx_drv_spim_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_spim_t * BX_SPIMx = ( reg_spim_t * )hdl;

    if( BX_SPIMx == BX_SPIM0 ) {
        BX_CLR_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_SPIM0 );
        BX_CLR_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_SPIM0 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_SPIM0 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_SPIM0 );
    } else if ( BX_SPIMx == BX_SPIM1 ) {
        BX_CLR_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_SPIM1 );
        BX_CLR_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_SPIM1 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_SPIM1 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_SPIM1 );
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
```

```c
bx_err_t bx_drv_spim_set_data_bit( void * hdl, u8 data_bit )
{
    CHECK_HANDLE( hdl );
    CHECK_DATA_BIT( data_bit );

    reg_spim_t * BX_SPIMx = ( reg_spim_t * )hdl;

    u32 val = ( u32 )( data_bit + 3 )<<SPIM_CTRL_DFS32_POS;
 
    BX_MODIFY_REG( BX_SPIMx->CTRL, SPIM_CTRL_DFS32, val );

    return BX_OK;
}
```



### 2.4、bx_drv_pwm.c

#### 修改前:

```c
/* private variables ---------------------------------------------------------*/
static struct bx_pwm_drv pwm_drv[5] = { 0 };
```

```c
bx_err_t bx_drv_pwm_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;

    /* close clock gate */
    if( BX_PWMx == BX_PWM0 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM0;
    } else if ( BX_PWMx == BX_PWM1 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM1;
    } else if ( BX_PWMx == BX_PWM2 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM2;
    } else if ( BX_PWMx == BX_PWM3 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM3;
    } else if ( BX_PWMx == BX_PWM4 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM4;
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
```

```c
bx_err_t bx_drv_pwm_start( void * hdl, u32 freq, u8 duty )
{
    CHECK_HANDLE( hdl );
    CHECK_FREQUENCY( freq );
    CHECK_DUTY( duty );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;


    uint32_t high_time;
    uint32_t low_time;
	u32 pin_mask ;
	
    if( duty == 0 ) {
		for(u8 i = 0; i < 5; i++)
		{
			if(pwm_drv[i].handle == BX_PWMx)
			{
			    BX_PWMx->EN = 0;
			    bx_drv_iomux_set_pin_type(pwm_drv[i].pin_num,BX_PIN_TYPE_GENERAL_IO);
				
			    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
				pin_mask =  0x01UL << pwm_drv[i].pin_num;
				BX_GPIOA->DIR |= ( pin_mask );
				BX_GPIOA->OD &= ~( 0x01UL << pwm_drv[i].pin_num );
				break;
			}
		}
    } else if( duty == 100 ) {
    	for(u8 i = 0; i < 5; i++)
		{
			if(pwm_drv[i].handle == BX_PWMx)
			{
			    BX_PWMx->EN = 0;
			    bx_drv_iomux_set_pin_type(pwm_drv[i].pin_num,BX_PIN_TYPE_GENERAL_IO);
				
			    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
				pin_mask =  0x01UL << pwm_drv[i].pin_num;
				BX_GPIOA->DIR |= ( pin_mask );
				BX_GPIOA->OD |= ( 0x01UL << pwm_drv[i].pin_num );
				break;
			}
		}
    } else {
        high_time = ( ( 160000 ) * duty ) / ( freq );
        low_time  = ( ( 160000 ) * ( 100 - duty ) ) / ( freq );

    	for(u8 i = 0; i < 5; i++)
		{
			if(pwm_drv[i].handle == BX_PWMx)
			{
				u32 value = pwm_drv[i].pin_type - BX_PIN_TYPE_UART0_TX;
			    u8 af_enable = pwm_drv[i].pin_num - 2 + FUNC_IO_EN00;
			    bx_drv_iomux_af_enable( af_enable );

			    u32 addr = 0x20132030 + ( pwm_drv[i].pin_num / 8 ) * 4;

			    *( u32 * ) addr |= value << ( ( ( pwm_drv[i].pin_num - 2 ) % 8 ) * 4 );
				break;
			}
		}
		
		BX_PWMx->EN = 0;
		BX_PWMx->PS = ( ( uint32_t )high_time << 16 ) | low_time;
		BX_PWMx->EN = 1;

    }

    return BX_OK;
}
```



#### 修改后：

新增代码：

```c
#define PWM_MAX_FREQUENCY_HZ                    16000000

/* private define ------------------------------------------------------------*/
#define CHECK_DIV(hdl)                                   \
do{                                                         \
    if( (hdl) < 2 ){                                \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)
```

```c
/* private variables ---------------------------------------------------------*/
static struct bx_pwm_drv pwm_drv[5] = { 0 };
static u8 pwm_div = 0;
```

新增代码

```c
bx_err_t bx_drv_pwm_set_clock_div( u8 div )
{
	/* div minimum value is 2 */
	CHECK_DIV(div);
	/* PWM tick clock = 32MHz/div */
    BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM_DIV;
    BX_PER->CDP0 = ( uint32_t )(div - 1) << PER_CDP0_PWM_POS;
    BX_PER->CLKG1 |= PER_CLKG1_SET_PWM_DIV;
	pwm_div = div;
    return BX_OK;
}
```

```c
bx_err_t bx_drv_pwm_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;

    /* close clock gate */
    if( BX_PWMx == BX_PWM0 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM0;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM0;
    } else if ( BX_PWMx == BX_PWM1 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM1;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM1;
    } else if ( BX_PWMx == BX_PWM2 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM2;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM2;
    } else if ( BX_PWMx == BX_PWM3 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM3;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM3;
    } else if ( BX_PWMx == BX_PWM4 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM4;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM4;
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
```

```c
bx_err_t bx_drv_pwm_start( void * hdl, u32 freq, u8 duty )
{
    CHECK_HANDLE( hdl );
    CHECK_FREQUENCY( freq );
    CHECK_DUTY( duty );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;


    uint32_t high_time;
    uint32_t low_time;
	u32 pin_mask ;
    static bool is_set_funcio = false;
    if( duty == 0 ) {
		for(u8 i = 0; i < 5; i++)
		{
			if(pwm_drv[i].handle == BX_PWMx)
			{
			    BX_PWMx->EN = 0;
			    bx_drv_iomux_set_pin_type(pwm_drv[i].pin_num,BX_PIN_TYPE_GENERAL_IO);
				
			    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
				pin_mask =  0x01UL << pwm_drv[i].pin_num;
				BX_GPIOA->DIR |= ( pin_mask );
				BX_GPIOA->OD &= ~( 0x01UL << pwm_drv[i].pin_num );
				break;
			}
		}
        is_set_funcio = true;
    } else if( duty == 100 ) {
    	for(u8 i = 0; i < 5; i++)
		{
			if(pwm_drv[i].handle == BX_PWMx)
			{
			    BX_PWMx->EN = 0;
			    bx_drv_iomux_set_pin_type(pwm_drv[i].pin_num,BX_PIN_TYPE_GENERAL_IO);
				
			    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
				pin_mask =  0x01UL << pwm_drv[i].pin_num;
				BX_GPIOA->DIR |= ( pin_mask );
				BX_GPIOA->OD |= ( 0x01UL << pwm_drv[i].pin_num );
				break;
			}
		}
        is_set_funcio = true;
    } else {
		high_time = ( ( 320000 / ( pwm_div) ) * duty ) / ( freq );
        low_time  = ( ( 320000 / ( pwm_div) ) * ( 100 - duty ) ) / ( freq );
        if( high_time > 0xFFFF || low_time > 0xFFFF ) {
            return BX_ERR_INVAL;
        }
        for( u8 i = 0; i < 5 && is_set_funcio ; i++ ) {
            if( pwm_drv[i].handle == BX_PWMx ) {
                bx_drv_iomux_set_pin_type( pwm_drv[i].pin_num,pwm_drv[i].pin_type);
                break;
            }
        }

        BX_PWMx->EN = 0;
        BX_PWMx->PS = ( ( uint32_t )high_time << 16 ) | low_time;
        BX_PWMx->EN = 1;
        is_set_funcio = false;
    }

    return BX_OK;
}
```



### 2.5、bx_drv_io_mux.c

#### 修改前：

```c
bx_err_t set_func_io_pin( u8 pin_num, u8 pin_type )
{
    if( pin_num > 23 || pin_num < 2 ) {
        return BX_ERR_INVAL;
    }

    u32 value = pin_type - BX_PIN_TYPE_UART0_TX;
    u8 af_enable = pin_num - 2 + FUNC_IO_EN00;
    bx_drv_iomux_af_enable( af_enable );

    u32 addr = 0x20132030 + ( pin_num / 8 ) * 4;

    *( u32 * ) addr |= value << ( ( ( pin_num - 2 ) % 8 ) * 4 );

    return BX_OK;
}
```



#### 修改后：

```c
bx_err_t set_func_io_pin( u8 pin_num, u8 pin_type )
{
    if( pin_num > 23 || pin_num < 2 ) {
        return BX_ERR_INVAL;
    }

    u32 value = pin_type - BX_PIN_TYPE_UART0_TX;
    u8 af_enable = pin_num - 2 + FUNC_IO_EN00;
    bx_drv_iomux_af_enable( af_enable );

    u32 addr = 0x20132030 + ( ( pin_num - 2 ) / 8 ) * 4;
    u32 addr_value = *( u32 * ) addr;
    addr_value &= ~( 0xF << ( ( ( pin_num - 2 ) % 8 ) * 4 ) );
    addr_value |= value << ( ( ( pin_num - 2 ) % 8 ) * 4 );

    *( u32 * ) addr = addr_value;
    return BX_OK;
}
```



### 2.6、bx_drv_iic.c

#### 修改前：

```

```

#### 修改后：

添加头文件

```c
#include "plf.h"
```

添加代码

```c
bx_err_t bx_drv_iic_read_ex( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len, s32 timeout_ms )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TA, IIC_TA_TAR, addr >> 1 );
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    uint8_t restart = 1;
    uint8_t stop = 0;
    //restart will send a byte of data
    do {
        if( len == 1 ) {
            stop = 1;
        }
        app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg++ );
        app_iic_set_data_cmd_pack( hdl, restart, stop, 1, 0 );
        restart = 0;

        while( ( BX_READ_BIT ( BX_IICx->STA, IIC_STA_RFNE ) == 0 ) && ( timeout_ms -- > 0 ) ) {
            BX_DELAY_US( 1000 );
        }
        if( timeout_ms <= 0 ) {
            return BX_ERR_TIMEOUT;
        }
        *buff = BX_FIELD_RD( BX_IICx->DC, IIC_DC_DAT );
        buff++;
        len--;
    } while( len > 0 );

    return BX_OK;
}
```

添加代码：

```c
bx_err_t bx_drv_iic_write_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TA, IIC_TA_TAR, addr >> 1 );
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    uint8_t stop = 0;
    //restart will send a byte of data
    app_iic_set_data_cmd_pack( hdl, 1, 0, 0, reg >> 8 );
    app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg & 0xFF );
    do {
        if( len == 1 ) {
            stop = 1;
        }

        app_iic_set_data_cmd_pack( hdl, 0, stop, 0, *buff );
        while( BX_READ_BIT ( BX_IICx->STA, IIC_STA_TFE ) == 0 );
        buff++;
        len--;
    } while( len > 0 );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_iic_read_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TA, IIC_TA_TAR, addr >> 1 );
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    uint8_t restart = 1;
    uint8_t stop = 0;
    //restart will send a byte of data
    app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg >> 8 );
    app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg & 0xFF );
    do {
        if( len == 1 ) {
            stop = 1;
        }

        app_iic_set_data_cmd_pack( hdl, restart, stop, 1, 0 );
        restart = 0;
        while( BX_READ_BIT ( BX_IICx->STA, IIC_STA_RFNE ) == 0 );
        *buff = BX_FIELD_RD( BX_IICx->DC, IIC_DC_DAT );
        buff++;
        len--;
    } while( len > 0 );

    return BX_OK;
}
```



### 2.7、bx_drv_gpio.c

#### 修改前：

```c
bx_err_t bx_drv_gpio_open( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;

    return BX_OK;
}
```

```c
bx_err_t bx_drv_gpio_close( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_PER->CLKG1 |= PER_CLKG1_CLR_GPIO;

    return BX_OK;
}
```

```c
static bx_err_t gpio_set_it_mode( void * hdl, u8 pin_num, u8 mode )
{
    u32 pin_mask =  0x01UL << pin_num;
    if( pin_num >= 2 ) {
        BX_AWO-> GPIOIE |= ( pin_mask );
        BX_AWO-> GPIOIS |= ( pin_mask );
    }
    switch( mode ) {
        case BX_GPIO_MODE_IT_LOW:
            BX_GPIOA->IT &= ~( pin_mask );
            BX_GPIOA->IP &= ~( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_HIGH:
            BX_GPIOA->IT &= ~( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_RISING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_FALLING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP &= ~( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_RISING_FALLING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE |= ( pin_mask );
            break;

        default:
            return BX_ERR_INVAL;
    }
    BX_GPIOA->IE |= pin_mask;
    BX_GPIOA->IM &= ~( pin_mask );

    NVIC_ClearPendingIRQ( GPIO_IRQn );
    NVIC_EnableIRQ( GPIO_IRQn );
    return BX_OK;
}
```

```c
static bx_err_t gpio_set_eit_mode( void * hdl, u8 pin_num, u8 mode )
{
    u8 index = ext_int_idx_get( pin_num );
    if( index == 0xFF ) {
        return BX_ERR_PERM;
    }

    u32 trigger_mode = 0;

    switch( mode ) {
        case BX_GPIO_MODE_EIT_LOW:
            trigger_mode = 0;
            break;

        case BX_GPIO_MODE_EIT_HIGH:
            trigger_mode = 1;
            break;

        case BX_GPIO_MODE_EIT_RISING:
            trigger_mode = 2;
            break;

        case BX_GPIO_MODE_EIT_FALLING:
            trigger_mode = 3;
            break;

        case BX_GPIO_MODE_EIT_RISING_FALLING:
            return BX_ERR_NOTSUP;

        default:
            return BX_ERR_INVAL;
    }

    u32 pin_mask =  0x01UL << pin_num;

    BX_AWO-> GPIOIE |= ( pin_mask );
    BX_AWO-> GPIOIS |= ( pin_mask );

    //清中断
    BX_AWO->EICLR |= ( 0x01UL << index );
    //先失能
    BX_AWO->EICFG &= ~( 0x01UL << index );
    //作为外部中断源
    BX_AWO->EICFG |= ( 0x01UL << ( index + 20 ) );
    //设置触发模式
    BX_AWO->EICFG |= trigger_mode << ( 8 + index * 2 );
    //使能外部中断
    BX_AWO->EICFG |= ( 0x01UL << index );

    NVIC_ClearPendingIRQ( EXT_INTR_IRQn );
    NVIC_EnableIRQ( EXT_INTR_IRQn );

    return BX_OK;
}
```

```c
bx_err_t bx_drv_gpio_set_mode( void * hdl, u8 pin_num, u8 mode )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    CHECK_MODE( mode );

    u32 pin_mask =  0x01UL << pin_num;
    switch( mode ) {
        case BX_GPIO_MODE_INPUT:
            BX_GPIOA->DIR &= ~( pin_mask );
            BX_AWO->GPIOIS |= ( pin_mask );
            BX_AWO->GPIOIE |= ( pin_mask );
            break;

        case BX_GPIO_MODE_OUTPUT:
            BX_GPIOA->DIR |= ( pin_mask );
            break;

        case BX_GPIO_MODE_IT_LOW:
        case BX_GPIO_MODE_IT_HIGH:
        case BX_GPIO_MODE_IT_RISING:
        case BX_GPIO_MODE_IT_FALLING:
        case BX_GPIO_MODE_IT_RISING_FALLING:
            return gpio_set_it_mode( hdl, pin_num, mode );


        case BX_GPIO_MODE_EIT_LOW:
        case BX_GPIO_MODE_EIT_HIGH:
        case BX_GPIO_MODE_EIT_RISING:
        case BX_GPIO_MODE_EIT_FALLING:
        case BX_GPIO_MODE_EIT_RISING_FALLING:
            return gpio_set_eit_mode( hdl, pin_num, mode );

        default:
            return BX_ERR_INVAL;
    };
    return BX_OK;
}
```



#### 修改后：

添加头文件

```c
#include "io_ctrl.h"
#include "sysctrl.h"
#include "bx_pcb_config.h"
#include "bx_dbg.h"
```

添加代码：

```c
/* private variables ---------------------------------------------------------*/
static u8 pin_intr_mode[32] = { 0 };
static gpio_intr_cb interrupt_callback = NULL;
```

```c
bx_err_t bx_drv_gpio_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    static bool is_open = false;
    if( ! is_open ) {
        BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
        io_init();
        is_open = true;
    }
    return BX_OK;
}
```

```c
bx_err_t bx_drv_gpio_close( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_PER->CLKG1 &= ~PER_CLKG1_SET_GPIO;
    BX_PER->CLKG1 |= PER_CLKG1_CLR_GPIO;

    return BX_OK;
}
```

```c
static bx_err_t gpio_set_it_mode( void * hdl, u8 pin_num, u8 mode )
{
    u32 pin_mask =  0x01UL << pin_num;
    if( pin_num >= 2 ) {
        BX_AWO-> GPIOIE |= ( pin_mask );
        BX_AWO-> GPIOIS |= ( pin_mask );
    }
    switch( mode ) {
        case BX_GPIO_MODE_IT_LOW:
            BX_GPIOA->IT &= ~( pin_mask );
            BX_GPIOA->IP &= ~( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_HIGH:
            BX_GPIOA->IT &= ~( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_RISING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_FALLING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP &= ~( pin_mask );
            BX_GPIOA->IBE &= ~( pin_mask );
            break;

        case BX_GPIO_MODE_IT_RISING_FALLING:
            BX_GPIOA->IT |= ( pin_mask );
            BX_GPIOA->IP |= ( pin_mask );
            BX_GPIOA->IBE |= ( pin_mask );
            break;

        case BX_GPIO_MODE_NO_IT:
            break;

        default:
            return BX_ERR_INVAL;
    }

    if ( mode == BX_GPIO_MODE_NO_IT ) {
        BX_GPIOA->IE &= ~( pin_mask );
        BX_GPIOA->IM |= pin_mask;
    } else {
        BX_GPIOA->IE |= pin_mask;
        BX_GPIOA->IM &= ~( pin_mask );
    }

    pin_intr_mode[pin_num] = mode;

    return BX_OK;
}
```

添加代码：

```c
bx_err_t bx_drv_gpio_clr_intr( void * hdl )
{
    CHECK_HANDLE( hdl );

    BX_GPIOA->EOI = 0xFFFFFFFF;
    BX_AWO->EICLR = 0x3F;

    NVIC_ClearPendingIRQ( GPIO_IRQn );
    NVIC_ClearPendingIRQ( EXT_INTR_IRQn );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_enable_intr( void * hdl )
{
    CHECK_HANDLE( hdl );

    NVIC_EnableIRQ( GPIO_IRQn );
    NVIC_EnableIRQ( EXT_INTR_IRQn );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_disable_intr( void * hdl )
{
    CHECK_HANDLE( hdl );

    NVIC_DisableIRQ( GPIO_IRQn );
    NVIC_DisableIRQ( EXT_INTR_IRQn );

    return BX_OK;
}
```

```c
static bx_err_t gpio_set_eit_mode( void * hdl, u8 pin_num, u8 mode )
{
    u8 index = ext_int_idx_get( pin_num );
    if( index == 0xFF ) {
        return BX_ERR_PERM;
    }

    u32 trigger_mode = 0;

    sysctrl_io_config_mask( 1 << pin_num, EXTERNAL_INTR_IO );

    switch( mode ) {
        case BX_GPIO_MODE_EIT_LOW:
            trigger_mode = 0;
            break;

        case BX_GPIO_MODE_EIT_HIGH:
            trigger_mode = 1;
            break;

        case BX_GPIO_MODE_EIT_RISING:
            trigger_mode = 2;
            break;

        case BX_GPIO_MODE_EIT_FALLING:
            trigger_mode = 3;
            break;

        case BX_GPIO_MODE_EIT_RISING_FALLING:
            return BX_ERR_NOTSUP;

        case BX_GPIO_MODE_NO_EIT:
            break;

        default:
            return BX_ERR_INVAL;
    }
    if( mode == BX_GPIO_MODE_NO_EIT ) {
        BX_AWO->EICFG &= ~( 0x01UL << index );
        BX_AWO->EICFG &= ~( 0x01UL << ( index + 20 ) );
    } else {
        u32 pin_mask =  0x01UL << pin_num;

    BX_AWO-> GPIOIE |= ( pin_mask );
    BX_AWO-> GPIOIS |= ( pin_mask );

        //中断失能
        BX_AWO->EICFG &= ~( 0x01UL << index );
        //中断源选择
        BX_AWO->EICFG |= ( 0x01UL << ( index + 20 ) );
        //设置中断触发模式
        //注意 &= ~ 的操作实际上是设置触发模式为高电平触发，若引脚此时刚好为高，会触发一次中断
        //    BX_AWO->EICFG &= ~( 0x3 << ( 8 + index * 2 ) );
        //    BX_AWO->EICFG |= trigger_mode << ( 8 + index * 2 );
        //此设置方式则不会存在上面的风险
        u32 value = BX_AWO->EICFG;
        value &= ~( 0x3 << ( 8 + index * 2 ) );
        value |= trigger_mode << ( 8 + index * 2 );
        BX_AWO->EICFG = value;

        //清空因设置中断触发模式导致的可能的中断
        BX_AWO->EICLR |= ( 0x01UL << index );
        //中断使能
        BX_AWO->EICFG |= ( 0x01UL << index );
    }

    pin_intr_mode[pin_num] = mode;

    return BX_OK;
}
```

新增代码

```c
bx_err_t bx_drv_gpio_disable_ext_intr( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );

    u8 index = ext_int_idx_get( pin_num );
    if( index == 0xFF ) {
        return BX_ERR_PERM;
    }
    BX_AWO->EICFG &= ~( 0x01UL << index );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_gpio_enable_ext_intr( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );

    u8 index = ext_int_idx_get( pin_num );
    if( index == 0xFF ) {
        return BX_ERR_PERM;
    }
    BX_AWO->EICLR |= ( 0x01UL << index );
    BX_AWO->EICFG |= ( 0x01UL << index );

    return BX_OK;
}
```

```c
bx_err_t bx_drv_gpio_set_mode( void * hdl, u8 pin_num, u8 mode )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    CHECK_MODE( mode );

    u32 pin_mask =  0x01UL << pin_num;
    switch( mode ) {
        case BX_GPIO_MODE_INPUT:
            BX_GPIOA->DIR &= ~( pin_mask );
            BX_AWO->GPIOIS |= ( pin_mask );
            BX_AWO->GPIOIE |= ( pin_mask );
            break;

        case BX_GPIO_MODE_OUTPUT:
            BX_GPIOA->DIR |= ( pin_mask );
            break;
        
        case BX_GPIO_MODE_NO_IT:
        case BX_GPIO_MODE_IT_LOW:
        case BX_GPIO_MODE_IT_HIGH:
        case BX_GPIO_MODE_IT_RISING:
        case BX_GPIO_MODE_IT_FALLING:
        case BX_GPIO_MODE_IT_RISING_FALLING:
            return gpio_set_it_mode( hdl, pin_num, mode );

        case BX_GPIO_MODE_NO_EIT:
        case BX_GPIO_MODE_EIT_LOW:
        case BX_GPIO_MODE_EIT_HIGH:
        case BX_GPIO_MODE_EIT_RISING:
        case BX_GPIO_MODE_EIT_FALLING:
        case BX_GPIO_MODE_EIT_RISING_FALLING:
            return gpio_set_eit_mode( hdl, pin_num, mode );

        default:
            return BX_ERR_INVAL;
    };
    return BX_OK;
}
```

新增代码：

```c
bx_err_t bx_drv_gpio_set_intr_callback( void * hdl, gpio_intr_cb cb )
{
    CHECK_HANDLE( hdl );

    interrupt_callback =  cb;

    return BX_OK;
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
u32 ext_int_stat_2_pin_state( u32 ext_int_stat )
{
    u32 ret = 0;
    u32 temp = 0;
    for( u32 i = 0; i < 5; i++ ) {
        if( ext_int_stat & ( 0x01 << i ) ) {
            switch( i ) {
                case 0:
                    temp = 0x01 << 15;
                    break;

                case 1:
                    temp = 0x01 << 16;
                    break;

                case 2:
                    temp = 0x01 << 17;
                    break;

                case 3:
                    temp = 0x01 << 22;
                    break;

                case 4:
                    temp = 0x01 << 23;
                    break;

                default:
                    break;
            }
        }
        ret |= temp;
    }
    return ret;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u8 get_reason( u8 pin_num )
{
    switch( pin_intr_mode[pin_num] ) {
        case BX_GPIO_MODE_IT_LOW:
        case BX_GPIO_MODE_EIT_LOW:
            return BX_GPIO_INTR_LOW;

        case BX_GPIO_MODE_IT_HIGH:
        case BX_GPIO_MODE_EIT_HIGH:
            return BX_GPIO_INTR_HIGH;

        case BX_GPIO_MODE_IT_RISING:
        case BX_GPIO_MODE_EIT_RISING:
            return BX_GPIO_INTR_RISING;

        case BX_GPIO_MODE_IT_FALLING:
        case BX_GPIO_MODE_EIT_FALLING:
            return BX_GPIO_INTR_FALLING;

        case BX_GPIO_MODE_IT_RISING_FALLING:
        case BX_GPIO_MODE_EIT_RISING_FALLING:
            return BX_GPIO_INTR_RISING_FALLING;

        default :
            return BX_GPIO_INTR_NONE;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void GPIO_IRQHandler( void )
{
    uint32_t int_stat = BX_GPIOA->IS;
    BX_GPIOA->EOI |= int_stat;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void EXT_INTR_IRQHandler( void )
{
    uint32_t ext_int_stat = BX_FIELD_RD( BX_AWO->EIVAL, AWO_EIVAL_VAL ) ;
    BX_AWO->EICLR |= ext_int_stat;
    u32 pin_state = ext_int_stat_2_pin_state( ext_int_stat );
    if( interrupt_callback != NULL ) {
        for( u8 i = 0; i < 32; i++ ) {
            if( pin_state & ( 0x1 << i ) ) {
                u8 reason = get_reason( i );
                if( reason != BX_GPIO_INTR_NONE ) {
                    interrupt_callback( BX_GPIOA, i, reason );
                } else {
                    //something error
                }
            }
        }
    }
}
```



### 2.8、bx_drv_adc.c

#### 修改前：

```c
static uint32_t adc_val_to_volt( int32_t adc_val )
{
    uint32_t temp, quotient, reminder;
    uint32_t adc_value_volt = 0;

    adc_val = ( adc_val  > 0 ? ( uint32_t )adc_val : 0 );

    if( adc_val <= 0 ) {
        adc_val = 0;
    }
    if( adc_val > SG_END_VAL_HIGH ) {
        adc_value_volt = SG_END_LOW;
    } else if( adc_val <= SG_END_SUBSTRATOR ) { // not SG_END_VAL_LOW
        adc_value_volt =  SG_END_HIGH;
    } else {

        temp = ( adc_val - SG_END_SUBSTRATOR ) / SG_END_VAL_STEP;
        quotient = temp / 1000;
        reminder = temp % 1000;

        if( reminder > 400 ) { // round up and round down
            quotient++;
        }

        adc_value_volt =  ( SG_END_INDEX_HIGH - 1 - quotient ) * SG_END_VOLT_STEP;
    }
    return adc_value_volt;
}
```

```c
bx_err_t bx_drv_adc_get_value( void * hdl, u8 channel, int32_t * value )
{
    CHECK_HANDLE( hdl );
    CHECK_CHANNEL( channel );
    CHECK_POINTER( value );

    uint16_t adc_val[4];
    uint16_t cal_param = 0;

    int32_t adc_val_sum = 0;

    cal_param = g_beta_offset_904[adc_cp_RO] + GPADC_BASE_VAL;

    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.
    config_init();

    for( uint8_t i = 0; i < 4; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t ) ( channel << ADC_SSM_CH_NUM_POS ) );
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START );

        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS );

        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS );
        adc_val_sum += cal_param * adc_val[i] + 766000 - cal_param * 766;
    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off

    * value = ( ( adc_val_sum - 255000 * 4 ) ) / 2; // adc/2 = adc*2/4;

    return BX_OK;
}
```

```c
bx_err_t bx_drv_adc_get_battery( void * hdl, u32 * bat_value )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( bat_value );

    uint16_t adc_val[BAT_SAMPLE_NUM];
    uint16_t adc_val_16;
    uint32_t adc_battery_value = 0;


    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.

    rf_setting_battery_init();

    for( uint8_t i = 0; i < BAT_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t )( 3 << ADC_SSM_CH_NUM_POS ) ); //set battery channel
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START ); //start adc
        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS ); //wait for adc done
        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS ); //read adc data

    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off
    qsort( adc_val, BAT_SAMPLE_NUM, sizeof( adc_val[0] ), adc_comparator );

    adc_val_16 = AvgArray( adc_val );

    adc_battery_value = app_adc_2_battery_volt( adc_val_16 );

    *bat_value = adc_battery_value;

    return BX_OK;
}
```



#### 修改后：

添加的头文件

```c
#include "bx_config.h"
#include "rf_power_set.h"
#include "app_adc_utils.h"
```

需要删掉的代码

```c
#define SG_END_VAL_HIGH                                 1023000
#define SG_END_VAL_LOW                                  0
#define SG_END_HIGH                                     2850
#define SG_END_LOW                                      0
#define SG_END_VOLT_STEP                                25
#define SG_END_INDEX_HIGH                               ( ( SG_END_HIGH - SG_END_LOW ) / SG_END_VOLT_STEP )
#define SG_END_SUBSTRATOR                               6000
#define SG_END_VAL_STEP                                 9

#define ADC_CAL_NUM                                     64

#define GPADC_BASE_VAL                                  904
#define ADC_SAMPLE_NUM                                  4
#define ADC_DEL_NUM                                     1
#define BAT_SAMPLE_NUM                                  ADC_SAMPLE_NUM
#define TMP_SAMPLE_NUM                                  ADC_SAMPLE_NUM

#define M_BAT_BASE                                      940
```

需要删掉的代码

```c
static uint8_t g_beta_offset_904[64] = {
    187,
    187,
    181,
    174,
    174,
    168,
    168,
    161,
    155,
    155,
    149,
    149,
    149,
    143,
    137,
    137,
    131,
    131,
    131,
    119,
    119,
    113,
    113,
    113,
    102,
    102,
    102,
    96,
    96,
    96,
    85,
    85,
    85,
    80,
    80,
    74,
    69,
    69,
    64,
    64,
    58,
    53,
    53,
    53,
    48,
    48,
    43,
    38,
    38,
    38,
    33,
    28,
    23,
    23,
    23,
    19,
    14,
    14,
    9,
    9,
    9,
    5,
    0,
    0
};


static uint16_t m_adc_2_bat_k[ADC_CAL_NUM] = {
    12886 - 10667,
    12837 - 10667,
    12802 - 10667,
    12752 - 10667,
    12713 - 10667,
    12679 - 10667,
    12651 - 10667,
    12557 - 10667,
    12500 - 10667,
    12500 - 10667,
    12500 - 10667,
    12500 - 10667,
    12392 - 10667,
    12336 - 10667,
    12312 - 10667,
    12299 - 10667,
    12240 - 10667,
    12192 - 10667,
    12164 - 10667,
    12120 - 10667,
    12086 - 10667,
    12049 - 10667,
    12019 - 10667,
    11972 - 10667,
    11935 - 10667,
    11903 - 10667,
    11866 - 10667,
    11823 - 10667,
    11800 - 10667,
    11760 - 10667,
    11716 - 10667,
    11688 - 10667,
    11656 - 10667,
    11626 - 10667,
    11584 - 10667,
    11553 - 10667,
    11517 - 10667,
    11486 - 10667,
    11445 - 10667,
    11418 - 10667,
    11375 - 10667,
    11345 - 10667,
    11319 - 10667,
    11280 - 10667,
    11250 - 10667,
    11221 - 10667,
    11187 - 10667,
    11149 - 10667,
    11121 - 10667,
    11089 - 10667,
    11056 - 10667,
    11028 - 10667,
    10997 - 10667,
    10969 - 10667,
    10947 - 10667,
    10908 - 10667,
    10870 - 10667,
    10843 - 10667,
    10812 - 10667,
    10780 - 10667,
    10753 - 10667,
    10713 - 10667,
    10699 - 10667,
    10667 - 10667,
};

static uint32_t m_adc_2_bat_base[ADC_CAL_NUM] = {
    6658000,
    6635500,
    6613600,
    6591400,
    6570600,
    6551300,
    6530700,
    6499900,
    6475000,
    6462500,
    6450000,
    6437500,
    6404700,
    6381100,
    6363700,
    6348700,
    6324300,
    6302600,
    6284700,
    6263800,
    6244000,
    6227800,
    6209200,
    6187300,
    6167400,
    6151600,
    6132300,
    6111400,
    6097100,
    6076700,
    6055700,
    6040700,
    6022000,
    6006700,
    5985700,
    5970400,
    5951000,
    5935000,
    5914700,
    5900100,
    5879300,
    5863800,
    5849400,
    5829400,
    5813800,
    5798700,
    5779400,
    5762900,
    5747800,
    5732400,
    5713200,
    5698300,
    5682600,
    5667800,
    5653300,
    5637300,
    5617000,
    5602300,
    5587000,
    5571400,
    5556600,
    5539100,
    5536900,
    5511100,
};

static uint8_t m_bat[ADC_CAL_NUM] = {
    0,
    2,
    4,
    6,
    8,
    10,
    12,
    14,
    16,
    18,
    20,
    22,
    25,
    27,
    29,
    31,
    33,
    35,
    38,
    40,
    42,
    44,
    46,
    49,
    51,
    53,
    55,
    58,
    60,
    62,
    65,
    67,
    69,
    72,
    74,
    76,
    79,
    81,
    83,
    86,
    88,
    91,
    93,
    96,
    98,
    101,
    103,
    106,
    108,
    111,
    113,
    116,
    118,
    121,
    123,
    126,
    129,
    131,
    134,
    137,
    139,
    142,
    145,
    147
};
static void config_init( void )
{
    //init adc reg_rg
    BX_ADC_CFG->ADC_COMP_Current = 0;//ADC Comparator Current Option,000: 1uA  ; 001: 1.3uA  ; 010: 1.3uA ;  011: 1.6uA; 100: 1.3uA  ; 101: 1.6uA  ; 110:1.6uA ;  111:1.9uA
    BX_ADC_CFG->ADC_CLK_DIV = 0;//00 :  DIV1               01 :  DIV2            10 :  DIV4              11 :  DIV8
    BX_ADC_CFG->ADC_REFP = 0 ; //ADC REFN Voltage Option, 00 : 2.8V               01 :2.6V             10 : 2.4V             11 :2.2V
    BX_ADC_CFG->ADC_REF_BUF_Current = 3 ; //ADC Buffer Current Option, 00 : 0.5uA               01 : 1.5uA             10 : 3.5uA             11 : 7.5uA
    BX_ADC_CFG->Reserved0 = 0 ;
    BX_ADC_CFG->LV_VCM = 0 ; //ADC VREF Low Voltage Mode , 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Force_ADC_CH_VDD_to_INT = 1; //Force VDD_3V of ADC Channel Tie to VDD_3V_INT, 0 : Tie to VDD_3V_ADC  ;  1 : Tie to VDD_3V_INT
    BX_ADC_CFG->ADC_SINGLE_DR = 1 ; //Bypass Internal ADC Reference Buffer, 0 : 9.6b  ;  1 : 9b
    BX_ADC_CFG->Sinlge_ended_Mode = 1 ; //ADC Input Single-ended Mode, 0 : Differential Mode  ;  1 : Single-ended Mode
    BX_ADC_CFG->External_Input_Buffer = 0;//Double VCM Buffer Current Bias, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Temperature_Sensor_Type = 0;//Differential Types of Temperature Sensor Option, 0 : NTAT   ;  1 : Channel 3 Input Buffer Enable
    BX_ADC_CFG->Temperature_Sensor = 0;//Temperature Sensor Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Battery_Monitor = 0;//VBAT Voltage Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Reserved2 = 0;
}
```

```c
static uint32_t adc_val_to_volt( int32_t adc_val )
{
    uint32_t temp;
    uint32_t adc_value_volt = 0;

    adc_val = ( adc_val  > 0 ? ( uint32_t )adc_val : 0 );

    if( adc_val <= 0 ) {
        adc_val = 0;
    }

    if( adc_val > SG_END_VAL_HIGH << 1 ) {
        adc_value_volt = SG_END_LOW;
    } else if( adc_val <= SG_END_SUBSTRATOR << 1 ) { // not SG_END_VAL_LOW
        adc_value_volt =  SG_END_HIGH;
    } else {

        temp = ( SG_END_VAL_STEP * 2 * 1000 ) * ( SG_END_INDEX_HIGH - 1 ) - adc_val + 12000;
        adc_value_volt = temp / ( ( SG_END_VAL_STEP * 2 * 1000 ) / SG_END_VOLT_STEP );	
    }
    return adc_value_volt;
}
```

需要删掉的代码

```c
static void rf_setting_battery_init( void )
{
    //init adc reg_rg
    BX_ADC_CFG->ADC_COMP_Current = 0;//ADC Comparator Current Option,000: 1uA  ; 001: 1.3uA  ; 010: 1.3uA ;  011: 1.6uA; 100: 1.3uA  ; 101: 1.6uA  ; 110:1.6uA ;  111:1.9uA
    BX_ADC_CFG->ADC_CLK_DIV = 0;//00 :  DIV1               01 :  DIV2            10 :  DIV4              11 :  DIV8
    BX_ADC_CFG->ADC_REFP = 0 ; //ADC REFN Voltage Option, 00 : 2.8V               01 :2.6V             10 : 2.4V             11 :2.2V
    BX_ADC_CFG->ADC_REF_BUF_Current = 3 ; //ADC Buffer Current Option, 00 : 0.5uA               01 : 1.5uA             10 : 3.5uA             11 : 7.5uA
    BX_ADC_CFG->Reserved0 = 0 ;
    BX_ADC_CFG->LV_VCM = 1 ; //ADC VREF Low Voltage Mode , 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Force_ADC_CH_VDD_to_INT = 1; //Force VDD_3V of ADC Channel Tie to VDD_3V_INT, 0 : Tie to VDD_3V_ADC  ;  1 : Tie to VDD_3V_INT
    BX_ADC_CFG->Sinlge_ended_Mode = 1 ; //ADC Input Single-ended Mode, 0 : Differential Mode  ;  1 : Single-ended Mode
    BX_ADC_CFG->External_Input_Buffer = 0;//Double VCM Buffer Current Bias, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Temperature_Sensor_Type = 0;//Differential Types of Temperature Sensor Option, 0 : NTAT   ;  1 : Channel 3 Input Buffer Enable
    BX_ADC_CFG->Temperature_Sensor = 0;//Temperature Sensor Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Battery_Monitor = 1;//VBAT Voltage Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Reserved2 = 0;
}
```

需要删掉的代码：

```c
static uint16_t AvgArray( uint16_t * numbers )
{
    uint32_t sum = 0;
    uint32_t avg = 0;
    for( uint32_t i = ADC_DEL_NUM; i <= ADC_SAMPLE_NUM - ADC_DEL_NUM - ADC_DEL_NUM; i++ ) {
        sum += numbers[i];
    }
    avg = sum / ( ADC_SAMPLE_NUM - ADC_DEL_NUM - ADC_DEL_NUM );
    if( sum - avg * ( ADC_SAMPLE_NUM - ADC_DEL_NUM - ADC_DEL_NUM ) >= ( ADC_SAMPLE_NUM - ADC_DEL_NUM - ADC_DEL_NUM ) / 2 ) {
        avg++;
    }
    return ( uint16_t )avg;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_setting_tempSensor_init( void )
{
    //init adc reg_rg
    BX_ADC_CFG->ADC_COMP_Current = 0;//ADC Comparator Current Option,000: 1uA  ; 001: 1.3uA  ; 010: 1.3uA ;  011: 1.6uA; 100: 1.3uA  ; 101: 1.6uA  ; 110:1.6uA ;  111:1.9uA
    BX_ADC_CFG->ADC_CLK_DIV = 0;//00 :  DIV1               01 :  DIV2            10 :  DIV4              11 :  DIV8
    BX_ADC_CFG->ADC_REFP = 0 ; //ADC REFN Voltage Option, 00 : 2.8V               01 :2.6V             10 : 2.4V             11 :2.2V
    BX_ADC_CFG->ADC_REF_BUF_Current = 3 ; //ADC Buffer Current Option, 00 : 0.5uA               01 : 1.5uA             10 : 3.5uA             11 : 7.5uA
    BX_ADC_CFG->Reserved0 = 0 ;
    BX_ADC_CFG->LV_VCM = 1 ; //ADC VREF Low Voltage Mode , 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Force_ADC_CH_VDD_to_INT = 1; //Force VDD_3V of ADC Channel Tie to VDD_3V_INT, 0 : Tie to VDD_3V_ADC  ;  1 : Tie to VDD_3V_INT
    BX_ADC_CFG->Sinlge_ended_Mode = 1 ; //ADC Input Single-ended Mode, 0 : Differential Mode  ;  1 : Single-ended Mode
    BX_ADC_CFG->External_Input_Buffer = 0;//Double VCM Buffer Current Bias, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Temperature_Sensor_Type = 0;//Differential Types of Temperature Sensor Option, 0 : NTAT   ;  1 : Channel 3 Input Buffer Enable
    BX_ADC_CFG->Temperature_Sensor = 1;//Temperature Sensor Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Battery_Monitor = 0;//VBAT Voltage Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Reserved2 = 0;
}
```

```c
bx_err_t bx_drv_adc_get_value( void * hdl, u8 channel, int32_t * value )
{
    CHECK_HANDLE( hdl );
    CHECK_CHANNEL( channel );
    CHECK_POINTER( value );

    uint16_t adc_val[ADC_SAMPLE_NUM];
    uint16_t cal_param = 0;

    int32_t adc_val_cal = 0;

    cal_param = m_adc_beta_offset_904[adc_cp_RO] + GPADC_BASE_VAL;

    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.
    rf_setting_single_mode_adc();

    for( uint8_t i = 0; i < ADC_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t ) ( channel << ADC_SSM_CH_NUM_POS ) );
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START );

        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS );

        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS );
    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off

    qsort( adc_val, ADC_SAMPLE_NUM, sizeof( adc_val[0] ), adc_comparator );
    adc_val_cal += cal_param * adc_val[1] + 511000 - cal_param * 766;
    adc_val_cal += cal_param * adc_val[2] + 511000 - cal_param * 766;
    adc_val_cal += cal_param * adc_val[3] + 511000 - cal_param * 766;
    adc_val_cal += cal_param * adc_val[4] + 511000 - cal_param * 766;

    * value = adc_val_cal;
    return BX_OK;
}
```

```c
bx_err_t bx_drv_adc_get_battery( void * hdl, u32 * bat_value )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( bat_value );

    uint16_t adc_val[BAT_SAMPLE_NUM];
    uint16_t adc_val_16;
    uint32_t adc_battery_value = 0;


    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.

    rf_setting_battery_monitor_adc();

    for( uint8_t i = 0; i < BAT_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t )( 3 << ADC_SSM_CH_NUM_POS ) ); //set battery channel
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START ); //start adc
        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS ); //wait for adc done
        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS ); //read adc data

    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off

	rf_setting_single_mode_adc();
    qsort( adc_val, BAT_SAMPLE_NUM, sizeof( adc_val[0] ), adc_comparator );

    adc_val_16 = AvgArray( adc_val );

    adc_battery_value = app_adc_2_battery_volt( adc_val_16 );

    *bat_value = adc_battery_value;

    return BX_OK;
}
```

```c
bx_err_t bx_drv_adc_get_chip_temperature( void * hdl, u32 * temp_value )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( temp_value );

    uint16_t adc_val[TMP_SAMPLE_NUM];
    uint16_t adc_val_16;
    uint32_t adc_temp_value = 0;
    uint32_t adc_val_cal = 0;

    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.
    rf_setting_temperature_adc();

    for( uint8_t i = 0; i < TMP_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t )( 3 << ADC_SSM_CH_NUM_POS ) ); //set tempSensor channel
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START ); //start adc
        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS ); //wait for adc done
        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS ); //read adc data

    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off

	rf_setting_single_mode_adc();
    qsort( adc_val, BAT_SAMPLE_NUM, sizeof( adc_val[0] ), adc_comparator );

    adc_val_16 = AvgArray( adc_val );

    adc_val_cal = ( int32_t )adc_val_16 * ( m_bat[adc_cp_RO] + M_BAT_BASE );
    //adc_temp_value = (adc_val_cal - 448230)/720;
    adc_temp_value = ( adc_val_cal - 448230 ) / 72;

    *temp_value = adc_temp_value;

    return BX_OK;
}
```

### 2.9、bx_drv_gpio.h

增加代码

```c
/* exported types ------------------------------------------------------------*/
typedef void( *gpio_intr_cb )( void * hdl, u8 pin_num, u8 reason );

bx_err_t    bx_drv_gpio_clr_intr( void * hdl );
bx_err_t    bx_drv_gpio_enable_intr( void * hdl );
bx_err_t    bx_drv_gpio_disable_intr( void * hdl );
bx_err_t    bx_drv_gpio_set_intr_callback( void * hdl, gpio_intr_cb cb );

bx_err_t    bx_drv_gpio_disable_ext_intr( void * hdl, u8 pin_num );
bx_err_t    bx_drv_gpio_enable_ext_intr( void * hdl, u8 pin_num );
```

### 2.10、bx_drv_iic.h

新增代码

```c
bx_err_t    bx_drv_iic_read_ex( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len,s32 timeout_ms );
bx_err_t    bx_drv_iic_read_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len );
bx_err_t    bx_drv_iic_write_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len );
```

### 2.11、bx_drv_pwm.h

新增代码

```c
bx_err_t    bx_drv_pwm_set_clock_div( u8 div );
```

### 2.12、bx_drv_tim.h

新增代码

```c
typedef void( *timer_intr_cb )(void);

bx_err_t 	bx_drv_timer_set_intr_callback( void * hdl, timer_intr_cb cb );
```

### 2.13、bx_drv_uart.h

新增代码

```c
bx_err_t    bx_drv_uart_enable_intr( void * hdl );
bx_err_t    bx_drv_uart_disable_intr( void * hdl );

bx_err_t    bx_drv_uart_intr_read_stop( void * hdl );
```

### 2.14、bx_gpio_type_def.h

新增代码

```c
    BX_GPIO_MODE_NO_IT,
    BX_GPIO_MODE_NO_EIT,

    enum bx_intr_reason{
    BX_GPIO_INTR_NONE,
    BX_GPIO_INTR_LOW,                       /*!< Interrupted due to low level  */
    BX_GPIO_INTR_HIGH,                      /*!< Interrupted due to high level  */
    BX_GPIO_INTR_RISING,                    /*!< Interrupted due to rising  */
    BX_GPIO_INTR_FALLING,                   /*!< Interrupted due to falling  */
    BX_GPIO_INTR_RISING_FALLING,            /*!< Interrupted due to rising or falling  */
};


```

### 2.14、bx_kernel.h

```
void     bx_cancel( s32 svc, u32 msg );
bx_err_t bx_get( s32 svc, u32 prop, u32 param0, u32 param1 );
bx_err_t bx_dwork( void (*cb)(void *),void * data,u32 time, s32 num );
void     bx_dwork_cancel( void (func)(void *) );

void bx_kernel_show_data( void );

```



## 3、更改服务文件

### 3.1、bx_service_adc

无

### 3.2、bx_service_gpio

需要删除的代码

```c
void GPIO_IRQHandler( void )
{
    uint32_t int_stat = BX_GPIOA->IS;
    BX_GPIOA->EOI |= int_stat;
    bx_public( gpioa_svc.id, BXM_GPIO_INTR, int_stat, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u32 ext_int_stat_2_pin_state( u32 ext_int_stat )
{
    u32 ret = 0;
    u32 temp = 0;
    for( u32 i = 0; i < 5; i++ ) {
        if( ext_int_stat & ( 0x01 << i ) ) {
            switch( i ) {
                case 0:
                    temp = 0x01 << 15;
                    break;

                case 1:
                    temp = 0x01 << 16;
                    break;

                case 2:
                    temp = 0x01 << 17;
                    break;

                case 3:
                    temp = 0x01 << 22;
                    break;

                case 4:
                    temp = 0x01 << 23;
                    break;

                default:
                    break;
            }
        }
        ret |= temp;
    }
    return ret;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void EXT_INTR_IRQHandler( void )
{
    uint8_t ext_int_stat = BX_FIELD_RD( BX_AWO->EIVAL, AWO_EIVAL_VAL ) ;
    BX_AWO->EICLR |= ext_int_stat;
    u32 pin_state = ext_int_stat_2_pin_state( ext_int_stat );

    bx_public( gpioa_svc.id, BXM_GPIO_EXT_INTR, pin_state, 0 );
}
```



### 3.3、bx_service_iic

无

### 3.4、bx_service_pwm

无

### 3.5、bx_service_spi

无

### 3.6、bx_service_tim

无

### 3.7、bx_service_uart

无

## 4、修改bx_kernel.c文件

#### 修改前：

```c
struct bx_delay_msg {
    s32     src;
    s32     dst;
    u32     msg;
    u32     param0;
    u32     param1;
    //kernel timer id
    u16     bkt_id;
    bool    used;
};
```

```c
/* private variables ---------------------------------------------------------*/
static struct   bx_msg_handle           msg_hdl;
static struct   bx_delay_msg_handle     dly_msg_hdl;
static struct   bx_service_handle       service_hdl;
static struct   bx_subject_hub          subject_hub;

//当前的服务
volatile static s32     current_service_id;
volatile static s32     current_msg_source_id;
volatile static bool    kernel_is_busy;
```

```c
static struct bx_msg * get_unused_msg( void )
{
    if( msg_hdl.count >= BXKE_MSG_CONFIG_MAX_COUNT ) {
        return NULL;
    }
    u32 index = ( msg_hdl.start + msg_hdl.count ) % BXKE_MSG_CONFIG_MAX_COUNT;
    msg_hdl.count++;
    return &msg_hdl.hub[index];
}
```

```c
static struct bx_msg * get_next_msg( void )
{
    if( msg_hdl.count == 0 ) {
        return NULL;
    }
    u32 index = msg_hdl.start;
    msg_hdl.start++;
    msg_hdl.start %= BXKE_MSG_CONFIG_MAX_COUNT;
    msg_hdl.count--;
    return &msg_hdl.hub[index];
}
```

```c
static __inline u16 get_kernel_timer_id( u32 dst, u32 msg )
{
    for( uint32_t i = 0 ; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        struct bx_delay_msg * pmsg = &dly_msg_hdl.hub[i];
        if( pmsg->dst == dst && pmsg->msg == msg  ) {
            return pmsg->bkt_id;
        }
    }
    return 0;
}
```

```c
static __inline bx_err_t post( s32 src, s32 dst, u32 msg, u32 param0, u32 param1 )
{
    struct bx_msg * pmsg = get_unused_msg();
    if( !pmsg ) {
        return BX_ERR_FULL;
    }
    GLOBAL_DISABLE_IRQ();
    pmsg->src = src;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    kernel_is_busy = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
```

```c
void bx_kernel_init( void )
{
    memset( &msg_hdl, 0, sizeof( struct bx_msg_handle ) );
    memset( &dly_msg_hdl, 0, sizeof( struct bx_delay_msg_handle ) );
    kernel_is_busy = false;
    bx_kernel_timer_init();
}
```

```c
void bx_kernel_schedule( void )
{
    while( 1 ) {
        struct bx_msg * pmsg = get_next_msg();
        if( pmsg == NULL ) {
            kernel_is_busy = false;
            // do something to notify app
            return;
        }
        
        #if ( BX_USE_WDT > 0 )
        BX_MODIFY_REG( BX_WDT->CR, WDT_CR_VAL, 0X76 );
        #endif
        
        msg_handle_f func = service_hdl.hub[pmsg->dst].msg_handle_func ;
        current_service_id = pmsg->dst;
        current_msg_source_id = pmsg->src;
        
        if( func == NULL ) {
            // do something to notify app
            continue;
        }
        bx_err_t err = func( pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        if( err == BX_OK ) {
            // do something to notify app
        } else if ( err == BX_ERR_BUSY ) {
            //把消息再扔进队列
            post( pmsg->src,pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        } else {
            // do something to notify app
            bxsh_logln("excute err:%u,%u,%u",pmsg->dst, pmsg->msg,err);
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_post( s32 dst, u32 msg, u32 param0, u32 param1 )
{
    return post(current_service_id,dst,msg,param0,param1);
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_defer( s32 dst, u32 msg, u32 param0, u32 param1, u32 time )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( time, 1 );
    if( tm_id == 0 ) {
        bxsh_logln("bx_defer BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   : period unit ms
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_repeat( s32 dst, u32 msg, u32 param0, u32 param1, u32 period )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( period, BX_FOREVER );
    if( tm_id == 0 ) {
        bxsh_logln("bx_repeat BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_repeatn( s32 dst, u32 msg, u32 param0, u32 param1, u32 period, s32 num )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( period, num );
    if( tm_id == 0 ) {
        bxsh_logln("bx_repeatn BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_cancel( s32 dst, u32 msg )
{
    u16 id = get_kernel_timer_id( dst, msg );
    if( id == 0 ) {
        return BX_OK;
    }
    bx_kernel_timer_stop( id );
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );
    pmsg->used = false;
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bx_register( struct bx_service * p_svc )
{
    if( service_hdl.count < BXKE_SERVICE_CONFIG_MAX_COUNT ) {
        GLOBAL_DISABLE_IRQ();
        u32 index = service_hdl.count;
        service_hdl.hub[index].prop_set_func = p_svc->prop_set_func;
        service_hdl.hub[index].prop_get_func = p_svc->prop_get_func;
        service_hdl.hub[index].msg_handle_func = p_svc->msg_handle_func;
        service_hdl.hub[index].name = p_svc->name;
        service_hdl.count++;
        GLOBAL_ENABLE_IRQ();
        return index;
    } else {
        bxsh_logln("bx_register BX_ERR_NOMEM");
        return -1;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_subscibe( s32 dst, u32 msg, u32 param0, u32 param1 )
{
    if( subject_hub.count >= BX_SUBSCIBE_MAX_COUNT ) {
        return false;
    }
    
    u32 count = subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( subject_hub.hub[i].src != current_service_id ) {
            continue;
        }
        if( subject_hub.hub[i].dst != dst ) {
            continue;
        }
        if( subject_hub.hub[i].msg == msg ) {
            return BX_OK;
        }
    }
    
    GLOBAL_DISABLE_IRQ();

    subject_hub.hub[subject_hub.count].src = current_service_id;
    subject_hub.hub[subject_hub.count].dst = dst;
    subject_hub.hub[subject_hub.count].msg = msg;
    subject_hub.count++;

    GLOBAL_ENABLE_IRQ();

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_subscibeex( s32 src, s32 dst, u32 msg )
{
    if( subject_hub.count >= BX_SUBSCIBE_MAX_COUNT ) {
        return false;
    }
    
    u32 count = subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( subject_hub.hub[i].src != src ) {
            continue;
        }
        if( subject_hub.hub[i].dst != dst ) {
            continue;
        }
        if( subject_hub.hub[i].msg == msg ) {
            return BX_OK;
        }
    }
    
    GLOBAL_DISABLE_IRQ();

    subject_hub.hub[subject_hub.count].src = src;
    subject_hub.hub[subject_hub.count].dst = dst;
    subject_hub.hub[subject_hub.count].msg = msg;
    subject_hub.count++;

    GLOBAL_ENABLE_IRQ();

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_public( s32 src, u32 msg, u32 param0, u32 param1 )
{
    bx_err_t err;
    u32 count = subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( subject_hub.hub[i].dst != src ) {
            continue;
        }
        if( subject_hub.hub[i].msg == msg ) {
             err = post( src, subject_hub.hub[i].src, msg, param0, param1 );
            if( err != BX_OK ) {
                return err;
            }
        }
    }
    return BX_ERR_EMPTY;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :不可在中断中使用
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_set( s32 dst, u32 prop, u32 param0, u32 param1 )
{
//    if( __get_IPSR() != 0 ) {
//        return BX_ERR_PERM;
//    }
    if( (u32)dst > service_hdl.count || service_hdl.hub[dst].prop_set_func == NULL ) {
        return BX_ERR_NOTSUP;
    }

    return service_hdl.hub[dst].prop_set_func(dst, prop, param0, param1 );
        
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_get( s32 dst, u32 prop, u8 * buff, u32 len )
{
//    if( __get_IPSR() != 0 ) {
//        return BX_ERR_PERM;
//    }
    if( (u32)dst > service_hdl.count || service_hdl.hub[dst].prop_get_func == NULL ) {
        return false;
    }

    return service_hdl.hub[dst].prop_get_func(dst, prop, ( u32 )buff, len );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_call( s32 dst,u32 msg,u32 param0,u32 param1)
{
//    if( __get_IPSR() != 0 ) {
//        return BX_ERR_PERM;
//    }
    if( (u32)dst > service_hdl.count || service_hdl.hub[dst].msg_handle_func == NULL ) {
        return BX_ERR_EMPTY;
    }
    return service_hdl.hub[dst].msg_handle_func(dst, msg, param0, param1 );
}
```

```c
u32 bx_service_get_count( void )
{
    return service_hdl.count;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
struct bx_service * bx_get_service( s32 id )
{
    if( id >= service_hdl.count || id < 0   ) {
        return NULL;
    }
    return &service_hdl.hub[id];
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bx_msg_source( void )
{
    return current_msg_source_id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_ke_busy(void)
{
    return kernel_is_busy;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_timer_timeout_callback( u16 id, bool end_of_repeat )
{
    //bxsh_logln( "id:%X %X", id, BKT_ID_TO_INDEX(id) );

    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( dly_msg_hdl.hub[index] );

    //bxsh_logln("%08X:%08x",pmsg->dst,pmsg->msg);
    if( pmsg->used ) {
        post( pmsg->src,pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
    }
    if( end_of_repeat ) {
        pmsg->used = false;
    }
}
```



#### 修改后：

新增代码

```c
#define KERNEL_DATA_SECTION __attribute__((section("kernel_data_section")))

#define KERNEL_DATA_START   (0x12345678)
#define KERNEL_DATA_END     (0x9ABCEDF0)
```

```c
struct bx_delay_msg {
    s32     src;
    s32     dst;
    u32     msg;
    u32     param0;
    u32     param1;
    
    void    (*cb)( void * );
    void *  data;
    
    //kernel timer id
    u16     bkt_id;
    bool    used;
};
```

```c
struct bx_kernel_data {
    u32 start;
    bool    kernel_is_busy;
    s32     current_msg_source_id;
    s32     current_service_id;
    struct  bx_msg_handle           msg_hdl;
    struct  bx_delay_msg_handle     dly_msg_hdl;
    struct  bx_service_handle       service_hdl;
    struct  bx_subject_hub          subject_hub;
    u32 end;
};
```

新增代码

```c
KERNEL_DATA_SECTION static struct bx_kernel_data bx_ke_env;
```

```c
static struct bx_msg * get_unused_msg( void )
{
    if( bx_ke_env.msg_hdl.count >= BXKE_MSG_CONFIG_MAX_COUNT ) {
        return NULL;
    }
    u32 index = ( bx_ke_env.msg_hdl.start + bx_ke_env.msg_hdl.count ) % BXKE_MSG_CONFIG_MAX_COUNT;
    bx_ke_env.msg_hdl.count++;
    return &bx_ke_env.msg_hdl.hub[index];
}
```

```c
static struct bx_msg * get_next_msg( void )
{
    if( bx_ke_env.msg_hdl.count == 0 ) {
        return NULL;
    }
    u32 index = bx_ke_env.msg_hdl.start;
    bx_ke_env.msg_hdl.start++;
    bx_ke_env.msg_hdl.start %= BXKE_MSG_CONFIG_MAX_COUNT;
    bx_ke_env.msg_hdl.count--;
    return &bx_ke_env.msg_hdl.hub[index];
}
```

```c
static __inline u16 get_kernel_timer_id( u32 dst, u32 msg )
{
    for( uint32_t i = 0 ; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        struct bx_delay_msg * pmsg = &bx_ke_env.dly_msg_hdl.hub[i];
        if( pmsg->dst == dst && pmsg->msg == msg  ) {
            return pmsg->bkt_id;
        }
    }
    return 0;
}
```

新增代码

```c
static __inline u16 get_kernel_timer_id_by_callback( void (*cb)(void * data) )
{
    for( uint32_t i = 0 ; i < BXKE_DELAY_MSG_CONFIG_MAX_COUNT; i++ ) {
        struct bx_delay_msg * pmsg = &bx_ke_env.dly_msg_hdl.hub[i];
        if( pmsg->cb == cb ) {
            return pmsg->bkt_id;
        }
    }
    return 0;
}
```

```c
static __inline bx_err_t post( s32 src, s32 dst, u32 msg, u32 param0, u32 param1 )
{
    struct bx_msg * pmsg = get_unused_msg();
    if( !pmsg ) {
        return BX_ERR_FULL;
    }
    GLOBAL_DISABLE_IRQ();
    pmsg->src = src;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    bx_ke_env.kernel_is_busy = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
```

新增代码

```c
#if ( BX_ENABLE_LOG > 0 )
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
char default_name[]="err name";
char * get_service_name(s32 id)
{
    if(id>= bx_ke_env.service_hdl.count )
        return default_name;
    return bx_ke_env.service_hdl.hub[id].name;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_show_data( void )
{
    GLOBAL_DISABLE_IRQ();
    bx_logln("========================= kernel data start ============================");
    bx_logln("start:%08X",bx_ke_env.start);
    bx_logln("end:%08X",bx_ke_env.end);
    bx_logln("service %u:",bx_ke_env.service_hdl.count);
    if( bx_ke_env.service_hdl.count > 0 ) {
        bx_logln("--------------------------------------");
        bx_logln("id\tname");
        for( u32 i=0;i<bx_ke_env.service_hdl.count;i++ ) {
            bx_logln( "%u\t%s\t",get_service_name(i) );
        }
        bx_log("current service :%u\t",bx_ke_env.current_service_id);
        bx_logln("%s",get_service_name(bx_ke_env.current_service_id));
        
        bx_log("current msg source :%u\t",bx_ke_env.current_msg_source_id);
        bx_logln("%s",get_service_name(bx_ke_env.current_msg_source_id));
        bx_logln("\n\n");
    }
    
    
    bx_logln("subject %u:",bx_ke_env.subject_hub.count);
    if( bx_ke_env.subject_hub.count > 0 ) {
        bx_logln("--------------------------------------");
        bx_logln("source name\t\t dest name \t\t msg");
        for( u32 i=0;i<bx_ke_env.subject_hub.count;i++ ) {
            u32 src_id = bx_ke_env.subject_hub.hub[i].src;
            u32 dst_id = bx_ke_env.subject_hub.hub[i].dst;
            bx_log( "%s\t",get_service_name(src_id) );
            bx_log( "%s\t",get_service_name(dst_id) );
            bx_logln("%u",bx_ke_env.subject_hub.hub[i].msg);
        }
        bx_logln("\n\n");
    }
    
    bx_logln("msg %u:",bx_ke_env.msg_hdl.count);
    if( bx_ke_env.msg_hdl.count > 0 ) {
        bx_logln("--------------------------------------");
        bx_logln("source name\t\t dest name \t\t msg");
        for( u32 i=bx_ke_env.msg_hdl.start;i<bx_ke_env.msg_hdl.count;i++ ) {
            u32 src_id = bx_ke_env.msg_hdl.hub[i].src;
            u32 dst_id = bx_ke_env.msg_hdl.hub[i].dst;
            bx_log( "%s\t",get_service_name(src_id) );
            bx_log( "%s\t",get_service_name(dst_id) );
            bx_logln("%u",bx_ke_env.msg_hdl.hub[i].msg);
        }
        bx_logln("\n\n");
    }
    
    bx_logln("delay msg :");
    bx_logln("--------------------------------------");
    bx_logln("source\t\t dest\t\t msg\t period\t repeat");
    for( u32 i=0;i<BXKE_DELAY_MSG_CONFIG_MAX_COUNT;i++ ) {
        struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[i] );
        if( pmsg->used ) {
            bx_log( "%s\t",get_service_name(pmsg->src) );
            bx_log( "%s\t",get_service_name(pmsg->dst) );
            bx_log("%u\t",pmsg->msg);
            u16 tm_id = get_kernel_timer_id( pmsg->dst, pmsg->msg );
            struct kernel_timer_config * cfg = bx_kernel_timer_get_config(tm_id);
            bx_log("%ums\t",cfg->time * 10);
            bx_logln("%d\t",cfg->repeat);
        }
    }
    bx_logln("========================= kernel data end ============================");
    bx_logln("\n\n");
    GLOBAL_ENABLE_IRQ();
}
#endif
```

```c
void bx_kernel_init( void )
{
    memset( &bx_ke_env, 0, sizeof( struct bx_kernel_data ) );
    bx_ke_env.start = KERNEL_DATA_START;
    bx_ke_env.end = KERNEL_DATA_END;
    bx_kernel_timer_init();
}
```

```c
void bx_kernel_schedule( void )
{
    while( 1 ) {
        if( bx_ke_env.start != KERNEL_DATA_START || bx_ke_env.end != KERNEL_DATA_END ) {
            bash_logln("mem overflow , kernel data err");
            //bx_err(  );
            while(1);
        }
        struct bx_msg * pmsg = get_next_msg();

    #if ( BX_USE_WDT > 0 )
        BX_MODIFY_REG( BX_WDT->CR, WDT_CR_VAL, 0X76 );
    #endif

        if( pmsg == NULL ) {
            bx_ke_env.kernel_is_busy = false;
            // do something to notify app
            return;
        }
        
        msg_handle_f func = bx_ke_env.service_hdl.hub[pmsg->dst].msg_handle_func ;
        bx_ke_env.current_service_id = pmsg->dst;
        bx_ke_env.current_msg_source_id = pmsg->src;
        
        if( func == NULL ) {
            // do something to notify app
            continue;
        }
        bx_err_t err = func( pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        if( err == BX_OK ) {
            // do something to notify app
        } else if ( err == BX_ERR_BUSY ) {
            //把消息再扔进队列
            post( pmsg->src,pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        } else {
            // do something to notify app
            bxsh_logln("excute err:%u,%u,%u",pmsg->dst, pmsg->msg,err);
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_post( s32 dst, u32 msg, u32 param0, u32 param1 )
{
    return post(bx_ke_env.current_service_id,dst,msg,param0,param1);
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_defer( s32 dst, u32 msg, u32 param0, u32 param1, u32 time )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( time, 1 );
    if( tm_id == 0 ) {
        bxsh_logln("bx_defer BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = bx_ke_env.current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   : period unit ms
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_repeat( s32 dst, u32 msg, u32 param0, u32 param1, u32 period )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( period, BX_FOREVER );
    if( tm_id == 0 ) {
        bxsh_logln("bx_repeat BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = bx_ke_env.current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_repeatn( s32 dst, u32 msg, u32 param0, u32 param1, u32 period, s32 num )
{
    u16 tm_id = get_kernel_timer_id( dst, msg );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( period, num );
    if( tm_id == 0 ) {
        bxsh_logln("bx_repeatn BX_ERR_NOMEM");
        return BX_ERR_NOMEM;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = bx_ke_env.current_service_id;
    pmsg->dst = dst;
    pmsg->msg = msg;
    pmsg->param0 = param0;
    pmsg->param1 = param1;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_cancel( s32 dst, u32 msg )
{
    u16 id = get_kernel_timer_id( dst, msg );
    if( id == 0 ) {
        return ;
    }
    bx_kernel_timer_stop( id );
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );
    GLOBAL_DISABLE_IRQ();
    pmsg->used = false;
    GLOBAL_ENABLE_IRQ();
    return ;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bx_register( struct bx_service * p_svc )
{
    if( bx_ke_env.service_hdl.count < BXKE_SERVICE_CONFIG_MAX_COUNT ) {
        GLOBAL_DISABLE_IRQ();
        u32 index = bx_ke_env.service_hdl.count;
        bx_ke_env.service_hdl.hub[index].prop_set_func = p_svc->prop_set_func;
        bx_ke_env.service_hdl.hub[index].prop_get_func = p_svc->prop_get_func;
        bx_ke_env.service_hdl.hub[index].msg_handle_func = p_svc->msg_handle_func;
        bx_ke_env.service_hdl.hub[index].name = p_svc->name;
        bx_ke_env.service_hdl.count++;
        GLOBAL_ENABLE_IRQ();
        return index;
    } else {
        bxsh_logln("bx_register BX_ERR_NOMEM");
        return -1;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_subscibe( s32 dst, u32 msg, u32 param0, u32 param1 )
{
    if( bx_ke_env.subject_hub.count >= BX_SUBSCIBE_MAX_COUNT ) {
        return false;
    }
    
    u32 count = bx_ke_env.subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( bx_ke_env.subject_hub.hub[i].src != bx_ke_env.current_service_id ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].dst != dst ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].msg == msg ) {
            return BX_OK;
        }
    }
    
    GLOBAL_DISABLE_IRQ();

    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].src = bx_ke_env.current_service_id;
    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].dst = dst;
    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].msg = msg;
    bx_ke_env.subject_hub.count++;

    GLOBAL_ENABLE_IRQ();

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_subscibeex( s32 src, s32 dst, u32 msg )
{
    if( bx_ke_env.subject_hub.count >= BX_SUBSCIBE_MAX_COUNT ) {
        return false;
    }
    
    u32 count = bx_ke_env.subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( bx_ke_env.subject_hub.hub[i].src != src ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].dst != dst ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].msg == msg ) {
            return BX_OK;
        }
    }
    
    GLOBAL_DISABLE_IRQ();

    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].src = src;
    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].dst = dst;
    bx_ke_env.subject_hub.hub[bx_ke_env.subject_hub.count].msg = msg;
    bx_ke_env.subject_hub.count++;

    GLOBAL_ENABLE_IRQ();

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_public( s32 src, u32 msg, u32 param0, u32 param1 )
{
    bx_err_t err;
    u32 count = bx_ke_env.subject_hub.count;
    for( u32 i = 0; i < count; i++ ) {
        if( bx_ke_env.subject_hub.hub[i].dst != src ) {
            continue;
        }
        if( bx_ke_env.subject_hub.hub[i].msg == msg ) {
            err = post( src, bx_ke_env.subject_hub.hub[i].src, msg, param0, param1 );
            if( err != BX_OK ) {
                return err;
            }
        }
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :不可在中断中使用
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_set( s32 dst, u32 prop, u32 param0, u32 param1 )
{
    if( (u32)dst > bx_ke_env.service_hdl.count || bx_ke_env.service_hdl.hub[dst].prop_set_func == NULL ) {
        return BX_ERR_NOTSUP;
    }
    GLOBAL_DISABLE_IRQ();
    bx_err_t ret = bx_ke_env.service_hdl.hub[dst].prop_set_func(dst, prop, param0, param1 );
    GLOBAL_ENABLE_IRQ();
    return ret;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_get( s32 dst, u32 prop, u32 param0, u32 param1 )
{
    if( (u32)dst > bx_ke_env.service_hdl.count || bx_ke_env.service_hdl.hub[dst].prop_get_func == NULL ) {
        return false;
    }
    GLOBAL_DISABLE_IRQ();
    bx_err_t ret = bx_ke_env.service_hdl.hub[dst].prop_get_func(dst, prop, param0, param1 );
    GLOBAL_ENABLE_IRQ();
    return ret;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_call( s32 dst,u32 msg,u32 param0,u32 param1)
{
//    if( __get_IPSR() != 0 ) {
//        return BX_ERR_PERM;
//    }
    if( (u32)dst > bx_ke_env.service_hdl.count || bx_ke_env.service_hdl.hub[dst].msg_handle_func == NULL ) {
        return BX_ERR_EMPTY;
    }
    return bx_ke_env.service_hdl.hub[dst].msg_handle_func(dst, msg, param0, param1 );
}
```

新增代码

```c
bx_err_t bx_dwork( void (*cb)(void *),void * data,u32 time, s32 num )
{
    u16 tm_id = get_kernel_timer_id_by_callback( cb );
    if( tm_id != 0 ) {
        //先取消原来的设置
        bx_kernel_timer_stop( tm_id );
    }

    //重新设置时间
    tm_id = bx_kernel_timer_creat( time, num );
    if( tm_id == 0 ) {
        bx_logln("bx_dwork ERR_NOMEM or INVAL");
        return BX_ERROR;
    }
    u16 index = bx_kernel_timer_id_to_array_index( tm_id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    GLOBAL_DISABLE_IRQ();
    pmsg->src = -1;
    pmsg->dst = -1;
    pmsg->msg = 0;
    pmsg->param0 = 0;
    pmsg->param1 = 0;
    pmsg->cb = cb;
    pmsg->data = data;
    pmsg->bkt_id = tm_id;
    pmsg->used = true;
    GLOBAL_ENABLE_IRQ();
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_dwork_cancel( void (*func)(void *) )
{
    u16 id = get_kernel_timer_id_by_callback( func );
    if( id == 0 ) {
        return ;
    }
    bx_kernel_timer_stop( id );
    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );
    GLOBAL_DISABLE_IRQ();
    pmsg->used = false;
    GLOBAL_ENABLE_IRQ();
    return ;
}
```

```c
u32 bx_service_get_count( void )
{
    return bx_ke_env.service_hdl.count;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
struct bx_service * bx_get_service( s32 id )
{
    if( id >= bx_ke_env.service_hdl.count || id < 0   ) {
        return NULL;
    }
    return &bx_ke_env.service_hdl.hub[id];
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bx_msg_source( void )
{
    return bx_ke_env.current_msg_source_id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_ke_busy(void)
{
    return bx_ke_env.kernel_is_busy;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_kernel_timer_timeout_callback( u16 id, bool end_of_repeat )
{
    //bxsh_logln( "id:%X %X", id, BKT_ID_TO_INDEX(id) );

    u16 index = bx_kernel_timer_id_to_array_index( id );
    struct bx_delay_msg * pmsg = &( bx_ke_env.dly_msg_hdl.hub[index] );

    //bxsh_logln("%08X:%08x",pmsg->dst,pmsg->msg);
    if( pmsg->used ) {
        if( end_of_repeat ) {
            pmsg->used = false;
        }
        if( pmsg->cb != NULL && pmsg->dst == -1 && pmsg->src == -1) {
            pmsg->cb( pmsg->data );
        }else if( pmsg->cb == NULL && pmsg->dst != -1 && pmsg->src != -1 ) {
            post( pmsg->src,pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1 );
        }else{
            bx_err( pmsg->dst, pmsg->msg, pmsg->param0, pmsg->param1,BX_ERR_INVAL );
        }
    }
}
```

## 5、修改rf参数

1、打开SDK3.3的components\bluex\ble\controller\driver\rf_setting路径，将rf_setting文件夹移植到SDK3.2同样路径下，并在mdk中添加该路径，将rf18_6文件夹删掉。

2、复制sdk3.3例程里的config文件夹，替换掉sdk3.2例程里的config。

3、打开工程编译，将bx/ble中报错的文件remove掉，在bx/ble中添加components\bluex\ble\controller\driver\rf_setting路径下的所有.c文件。

4、在cfg中添加工程文件cfg路径下的所有.h文件。

5、打开keil的Option for Target 'template',在Linker把config文件的user_link.txt添加进去。

## 6、与sdk3.3.1的版本匹配

1、remove掉bx/ble中报错的文件后，将sdk3.3.1的components\bluex\ble\controller\patch路径下的lld_scan_stop_patch_asm.s和llc_version_patch_asm.s文件添加进来。