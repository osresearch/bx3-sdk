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

//0214
#include "bx_dbg.h"

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
static void spis_rx_full_isr( void )//slave spi rx接收中断回调函数
{
    while( BX_READ_BIT( BX_SPIS->STA, SPIS_STA_RFNE ) >> SPIS_STA_RFNE_POS ) {
        if( BX_READ_BIT( BX_SPIS->CTRL, SPIS_CTRL_DFS32 ) <= SPIS_CTRL_DFS32_T_8_BITS ) {
            *( uint8_t * )s_p_rx_buff = BX_SPIS->DATA;
            s_p_rx_buff += 1;
        } else if( BX_READ_BIT( BX_SPIS->CTRL, SPIS_CTRL_DFS32 ) <= SPIS_CTRL_DFS32_T_16_BITS ) {
            *( uint16_t * )s_p_rx_buff = BX_SPIS->DATA;
            s_p_rx_buff += 2;
        } else {
            *( uint32_t * )s_p_rx_buff = BX_SPIS->DATA;
            s_p_rx_buff += 4;

        }
        --s_rx_len;

        if( s_rx_len == 0 ) {
            break;
        }

    }
    if( s_rx_len > 0 ) {
        BX_SPIS->RXFTL = s_rx_len > SPI_FIFO_DEPTH ? SPI_FIFO_DEPTH / 2 - 1 : s_rx_len - 1;
    } else {
        BX_CLR_BIT( BX_SPIS->SSIE, SPIM_SSIE_BIT );
        bx_public( us_svc.id, BXM_USER_RECEIVE_DATA_END, 0, 0 );
    }

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void spis_tx_empty_isr( void )//slave spi tx发送中断回调函数
{

    if( s_tx_len ) {
        while( BX_READ_BIT( BX_SPIS->STA, SPIS_STA_TFNF ) >> SPIS_STA_TFNF_POS ) {
            if( BX_READ_BIT( BX_SPIS->CTRL, SPIS_CTRL_DFS32 ) <= SPIS_CTRL_DFS32_T_8_BITS ) {
                BX_SPIS->DATA = *( uint8_t * )s_p_tx_buff;
                s_p_tx_buff += 1;
            } else if( BX_READ_BIT( BX_SPIS->CTRL, SPIS_CTRL_DFS32 ) <= SPIS_CTRL_DFS32_T_16_BITS ) {
                BX_SPIS->DATA = *( uint16_t * )s_p_tx_buff;
                s_p_tx_buff += 2;
            } else {
                BX_SPIS->DATA = *( uint32_t * )s_p_tx_buff;
                s_p_tx_buff += 4;
            }
            --s_tx_len;
						
            if( s_tx_len == 0 ) {
                BX_MODIFY_REG( BX_SPIS->TXFTL, SPIS_TXFTL_VAL, ( uint32_t ) 0 );
                BX_SET_BIT( BX_SPIS->IM, SPIS_IM_TFE );                
                break;
            }
        }
     }
		 else {
        if( BX_READ_REG( BX_SPIS->TXFL ) ) {
            BX_MODIFY_REG( BX_SPIS->TXFTL, SPIS_TXFTL_VAL, ( uint32_t ) 0 );
        } else {
            BX_CLR_BIT( BX_SPIS->IM, SPIS_IM_TFE );
            if( BX_READ_BIT( BX_SPIS->CTRL, SPIS_CTRL_TM ) == SPIS_CTRL_TM_T_TX ) {
                while( BX_READ_BIT( BX_SPIS->STA, SPIS_STA_BUSY ) == 1 ) {
                    BX_CLR_BIT( BX_SPIS->SSIE, SPIS_SSIE_BIT );
                }              
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
void SPIS_IRQHandler( void )//slave spi interrupt handler
{
    {
        uint32_t irq_stat = BX_SPIS->IS;

        if( irq_stat == 0 ) {
            return;
        }

        if( irq_stat & SPIS_IS_MMC ) {
            BX_READ_REG( BX_SPIS->MMIC );
            LOG_W( "SPIS_IS_MMC\n" );
        }
        if( irq_stat & SPIS_IS_RFF ) {
					  //0215
					  LOG_W( "SPIS_IS_RFF\n" );
            spis_rx_full_isr();//slave spi rx接收中断回调函数
        }
        if( irq_stat & SPIS_IS_RFO ) {
            BX_READ_REG( BX_SPIS->RXFOIC );
            LOG_W( "SPIS_IS_RFO\n" );
        }
        if( irq_stat & SPIS_IS_RFU ) {
            BX_READ_REG( BX_SPIS->RXFUIC );
            LOG_W( "SPIS_IS_RFU\n" );
        }
        if( irq_stat & SPIS_IS_TFE ) {
					  //0215
					  LOG_W( "SPIS_IS_TFE\n" );
            spis_tx_empty_isr();//slave spi tx发送中断回调函数
        }
        if( irq_stat & SPIS_IS_TFO ) {
            BX_READ_REG( BX_SPIS->TXFOIC );
            LOG_W( "SPIS_IS_TFO\n" );
        }
    }
		
    if( BX_READ_BIT( BX_SPIS->SSIE, SPIS_SSIE_BIT ) == 0 ) {
        BX_PER->CLKG0 &= ~PER_CLKG0_32M_SET_SPIS;
        BX_PER->CLKG0 &= ~PER_CLKG0_PLL_SET_SPIS;
    }
}


/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



