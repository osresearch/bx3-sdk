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
#include "bx_apollo00_it.h"

#include "app.h"
#include "log.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void spim_rx_full_isr( void )//master spi rx接收中断回调函数
{
	while(BX_READ_BIT(BX_SPIM0->STA, SPIM_STA_RFNE)>>SPIM_STA_RFNE_POS)
	{
		if(BX_READ_BIT(BX_SPIM0->CTRL, SPIM_CTRL_DFS32) <= SPIM_CTRL_DFS32_T_8_BITS)
		{
			*(uint8_t *)m_p_rx_buff = BX_SPIM0->DATA;
			m_p_rx_buff += 1;
		}
		else if(BX_READ_BIT(BX_SPIM0->CTRL, SPIM_CTRL_DFS32) <= SPIM_CTRL_DFS32_T_16_BITS)
		{
			*(uint16_t *)m_p_rx_buff = BX_SPIM0->DATA;
			m_p_rx_buff += 2;
		}
		else
		{
			*(uint32_t *)m_p_rx_buff = BX_SPIM0->DATA;
			m_p_rx_buff += 4;
			
		}
		--m_rx_len;

		if(m_rx_len == 0){
			break;
		}

	}

	
	if(m_rx_len > 0)
		BX_SPIM0->RXFTL = m_rx_len > SPI_FIFO_DEPTH ? SPI_FIFO_DEPTH / 2 - 1:m_rx_len - 1;
	else{
		BX_CLR_BIT( BX_SPIM0->SSIE, SPIM_SSIE_BIT ); 
		BX_SET_REG( BX_SPIM0->SE, 0 ); 
		bx_public(us_svc.id,BXM_USER_RECEIVE_DATA_END,0,0);

	}

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void spim_tx_empty_isr( void )//master spi tx发送中断回调函数
{

   if(m_tx_len)
   	{
		while(BX_READ_BIT(BX_SPIM0->STA, SPIM_STA_TFNF)>>SPIM_STA_TFNF_POS)
		{
			if(BX_READ_BIT(BX_SPIM0->CTRL, SPIM_CTRL_DFS32) <= SPIM_CTRL_DFS32_T_8_BITS)
			{
				BX_SPIM0->DATA = *(uint8_t *)m_p_tx_buff;
				m_p_tx_buff += 1;
			}
			else if(BX_READ_BIT(BX_SPIM0->CTRL, SPIM_CTRL_DFS32) <= SPIM_CTRL_DFS32_T_16_BITS)
			{
				BX_SPIM0->DATA = *(uint16_t *)m_p_tx_buff;
				m_p_tx_buff += 2;
			}
			else
			{
				BX_SPIM0->DATA = *(uint32_t *)m_p_tx_buff;
				m_p_tx_buff += 4;
				
			}
			
			--m_tx_len;

			
			if(m_tx_len == 0)
			{
				BX_MODIFY_REG(BX_SPIM0->TXFTL, SPIM_TXFTL_VAL,(uint32_t) 0);
				BX_SET_BIT(BX_SPIM0->IM, SPIM_IM_TFE);

				break;
			}
		}
		if((BX_READ_BIT(BX_SPIM0->STA, SPIM_STA_BUSY) == 0)&&(BX_READ_REG(BX_SPIM0->SE) == 0))
		{
				BX_MODIFY_REG(BX_SPIM0->SE,SPIM_SE_VAL,( uint32_t ) 0x01);
		}
   	}
   else
   {
		if(BX_READ_REG(BX_SPIM0->TXFL))
		{
			BX_MODIFY_REG(BX_SPIM0->TXFTL, SPIM_TXFTL_VAL,(uint32_t) 0);
		}
		else
		{
			BX_CLR_BIT(BX_SPIM0->IM, SPIM_IM_TFE);
			if(BX_READ_BIT(BX_SPIM0->CTRL,SPIM_CTRL_TM) == SPIM_CTRL_TM_T_TX)
			{
				while(BX_READ_BIT(BX_SPIM0->STA,SPIM_STA_BUSY) == 1)
				BX_CLR_BIT(BX_SPIM0->SSIE, SPIM_SSIE_BIT);
				BX_MODIFY_REG(BX_SPIM0->SE, SPIM_SE_VAL,(uint32_t) 0 );
			}
		}
   }

}


/*========================= end of private function ==========================*/

/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void SPIM0_IRQHandler( void )// spim0中断向量函数
{
{
	uint32_t irq_stat = BX_SPIM0->IS;
	
    if(irq_stat == 0)  return;

	if(irq_stat & SPIM_IS_MMC)
	{
		BX_READ_REG(BX_SPIM0->MMIC);
		LOG_W("SPIM_IS_MMC\n");
	}
	if(irq_stat & SPIM_IS_RFF)
	{
	    spim_rx_full_isr();//master spi rx接收中断回调函数
	}
	if(irq_stat & SPIM_IS_RFO)
	{
		BX_READ_REG(BX_SPIM0->RXFOIC);
		LOG_W("SPIM_IS_RFO\n");
	}
	if(irq_stat & SPIM_IS_RFU)
	{
		BX_READ_REG(BX_SPIM0->RXFUIC);
		LOG_W("SPIM_IS_RFU\n");
	}
	if(irq_stat & SPIM_IS_TFE)
	{
	    spim_tx_empty_isr();//master spi tx发送中断回调函数
	}
	if(irq_stat & SPIM_IS_TFO)
	{	   
		BX_READ_REG(BX_SPIM0->TXFOIC);
		LOG_W("SPIM_IS_TFO\n");
	}
}
    if(BX_READ_BIT( BX_SPIM0->SSIE, SPIM_SSIE_BIT ) == 0)
    {
		BX_PER->CLKG0 &= ~PER_CLKG0_32M_SET_SPIM0;
    	BX_PER->CLKG0 &= ~PER_CLKG0_PLL_SET_SPIM0;
	}
}


/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



