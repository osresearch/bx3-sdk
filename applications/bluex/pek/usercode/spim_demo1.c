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

#include "apollo_00_reg.h"
#include "spim_demo.h"
#include "shell_api.h"
/* private define ------------------------------------------------------------*/

#define SPIM_FIFO_DEPTH 32

static __IO uint8_t spim_tx_len = 0;
static __IO uint8_t spim_rx_len = 0;
static uint8_t * spim_tx_buff = 0;
static uint8_t * spim_rx_buff = 0;

uint8_t spim_hw_cs_mask = 0;//hardware CS pin mask
uint8_t spim_cs_sel_mask = 0;

#define W25X_DeviceID                   0xAB
#define Dummy_Byte                0xFF

#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99
#define READ_STATUS_REG1_CMD                  0x05
#define READ_ID_CMD                          0x90


#define BX_SPIM_CLK         GPIO_PIN_4
#define BX_SPIM_MOSI        GPIO_PIN_6
#define BX_SPIM_MISO        GPIO_PIN_5
#define BX_SPIM_CS          GPIO_PIN_3

#define BX_SPIM             BX_SPIM0

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/



static void prv_user_delay( uint32_t val )
{
    for( uint32_t i = 0; i < val; i++ )
        for( uint32_t j = 0; j < 5000; j++ );
}

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void prv_spim_init( void )
{
    __disable_irq();

    //master
    //step 1:init clk
    BX_SET_BIT( BX_PER->SRST, PER_SRST_CLR_SPIM0 );
    BX_SET_BIT( BX_PER->SRST, PER_SRST_SET_SPIM0 );
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_SPIM0 );
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_SPIM0 );

//    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
//    BX_GPIOA->DIR |= GPIO_PIN_4; //CLK
//    BX_GPIOA->OD |= GPIO_PIN_4;
//    BX_GPIOA->DIR &= ~GPIO_PIN_6;  //MOSI
//    BX_GPIOA->OD |= GPIO_PIN_6;
//    BX_GPIOA->DIR |= GPIO_PIN_3;  //CS
//    BX_GPIOA->OD &= ~GPIO_PIN_3;

//    BX_GPIOA->DIR &= ~( GPIO_PIN_5 ); //MISO
//    BX_AWO->GPIOIS |= ( GPIO_PIN_5 | GPIO_PIN_6);
//    BX_AWO->GPIOIE |= ( GPIO_PIN_5 | GPIO_PIN_6);
//    BX_AWO->GPIOPS |= ( GPIO_PIN_5 | GPIO_PIN_6);
//    BX_AWO->GPIOPE |= ( GPIO_PIN_5 | GPIO_PIN_6);

    //set pin
//  BX_AWO->GPIOIE |= BX_SPIM_CLK;
//  BX_AWO->GPIOIE |= BX_SPIM_MOSI;
//  BX_AWO->GPIOIE |= BX_SPIM_MISO;
//  BX_AWO->GPIOIE |= BX_SPIM_CS;


    BX_SET_BIT( BX_CPU->PSEN, CPU_PSEN_SPIM0 );

    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_DFS32, ( uint32_t ) SPIM_CTRL_DFS32_T_8_BITS );  //set Data Frame Size  mode
    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_SCPH, ( uint32_t ) SPIM_CTRL_SCPH_T_MIDDLE ); //set Serial Clock Phase
    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_SCPOL, ( uint32_t ) SPIM_CTRL_SCPOL_T_LOW ); //set Serial Clock Polarity


    BX_MODIFY_REG( BX_SPIM->BRS, SPIM_BRS_CD, ( uint32_t ) 160 );//Baud Rate Select

    //set interrupt mask
    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_MMC );
    BX_CLR_BIT( BX_SPIM->IM, SPIM_IM_RFF );
    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_RFO );
    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_RFU );
    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_TFO );
    BX_CLR_BIT( BX_SPIM->IM, SPIM_IM_TFE );

    NVIC_ClearPendingIRQ( SPIM0_IRQn );  //clear  interrupt
    NVIC_EnableIRQ( SPIM0_IRQn );        //enable interrupt
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_SPIM0 );
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_SPIM0 );

    __enable_irq();
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :   return read length
-----------------------------------------------------------------------------*/

void prv_spim_transmit( uint8_t cs_sel_mask, void * tx_data, uint32_t len )
{
    spim_tx_buff = tx_data;
    spim_tx_len = len;
    spim_rx_len = 0;
    spim_cs_sel_mask = cs_sel_mask;
    spim_hw_cs_mask = 0x1;

    BX_CLR_BIT( BX_SPIM->SSIE, SPIM_SSIE_BIT );

    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_TM, ( uint32_t ) SPIM_CTRL_TM_T_TX );

    //set transmit FIFO threshold
    BX_MODIFY_REG( BX_SPIM->TXFTL, SPIM_TXFTL_VAL, ( uint32_t ) ( SPIM_FIFO_DEPTH / 2 ) );
    //set interrupt mask
    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_TFE );


    /*set ssie enable*/
    BX_SET_BIT( BX_SPIM->SSIE, SPIM_SSIE_BIT );

    while( spim_tx_len > 0 ) {
        bxs_printfln( "%02x", spim_tx_len );
    }
}

void prv_spim_receive( uint8_t cs_sel_mask, void * rx_data, uint32_t len )
{

    spim_rx_buff = rx_data;
    spim_tx_len = 0;
    spim_rx_len = len;
    spim_cs_sel_mask = cs_sel_mask;
    spim_hw_cs_mask = 0x1;

    BX_CLR_BIT( BX_SPIM->SSIE, SPIM_SSIE_BIT );

    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_TM, ( uint32_t ) SPIM_CTRL_TM_T_EEPROM_READ );

//    if( BX_READ_BIT( BX_SPIM->SSIE, SPIM_SSIE_BIT ) == 0 ) {
//        BX_MODIFY_REG( BX_SPIM->NDF, SPIM_NDF_VAL, ( uint32_t ) ( spim_rx_len - 1 ) );
//    }

    if( len > SPIM_FIFO_DEPTH ) {
        BX_MODIFY_REG( BX_SPIM->RXFTL, SPIM_RXFTL_VAL, ( uint32_t ) ( SPIM_FIFO_DEPTH / 2 - 1 ) );
    } else {
        BX_MODIFY_REG( BX_SPIM->RXFTL, SPIM_RXFTL_VAL, ( uint32_t ) ( len - 1 ) );
    }

    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_RFF );

    /*set ssie enable*/
    BX_SET_BIT( BX_SPIM->SSIE, SPIM_SSIE_BIT );

    while( spim_rx_len > 0 );

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_spim_transmit_receive( uint8_t cs_sel_mask, void * tx_data, uint32_t tx_len, void * rx_data, uint32_t rx_len )
{

    spim_tx_buff = tx_data;
    spim_rx_buff = rx_data;
    spim_tx_len = tx_len;
    spim_rx_len = rx_len;
    spim_cs_sel_mask = cs_sel_mask;


    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_DFS32, ( uint32_t ) SPIM_CTRL_DFS32_T_8_BITS );

    //BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_TM, ( uint32_t ) SPIM_CTRL_TM_T_TXRX );

    BX_MODIFY_REG( BX_SPIM->CTRL, SPIM_CTRL_TM, ( uint32_t ) SPIM_CTRL_TM_T_EEPROM_READ );

    /*start transfer*/
    BX_MODIFY_REG( BX_SPIM->TXFTL, SPIM_TXFTL_VAL, ( uint32_t ) ( SPIM_FIFO_DEPTH / 2 ) );
    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_TFE  );

    uint32_t len = rx_len > SPIM_FIFO_DEPTH ? SPIM_FIFO_DEPTH / 2 - 1 : rx_len - 1;
    BX_MODIFY_REG( BX_SPIM->RXFTL, SPIM_RXFTL_VAL, ( uint32_t ) len );
    BX_SET_BIT( BX_SPIM->IM, SPIM_IM_RFF  );

    spim_rx_len = rx_len;
    /*set ssie enable*/
    BX_SET_BIT( BX_SPIM->SSIE, SPIM_SSIE_BIT );
    while( spim_rx_len > 0 );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void w25x_init( void )
{
    uint8_t status;
    uint8_t cmd[2] = {RESET_ENABLE_CMD, RESET_MEMORY_CMD};
    uint8_t cmd1[1] = {READ_STATUS_REG1_CMD};
    BX_GPIOA->OD &= ~GPIO_PIN_3;
    prv_spim_transmit( 1, cmd, 2 );

    prv_spim_transmit( 1, cmd1, 1 );
    prv_spim_receive( 1, &status, 1 );
//  BX_GPIOA->OD |= GPIO_PIN_3;

}


uint8_t read_deviceID( void )
{
    uint8_t temp[2] = {0xff, 0xff};
    uint8_t cmd[4] = {0};
    BX_GPIOA->OD &= ~GPIO_PIN_3;
    cmd[0] = READ_ID_CMD;
    prv_spim_receive( 1, temp, 2 );

//    prv_spim_transmit( 1, cmd, 4 );
//    bxs_printfln("prv_spim_transmit done");
//    //prv_spim_transmit_receive( 1,temp,2, temp, 2 );
//    prv_spim_transmit(1,temp, 2);
//    bxs_printfln("prv_spim_transmit done");

//  BX_GPIOA->OD |= GPIO_PIN_3;

    return temp[0];

}



/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_spim_cmd_handler( char argc, char * argv )
{
    char ch[1];
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxs_printfln( "useage: help [options]" );
            bxs_printfln( "options:" );
            bxs_printfln( "\t init \t: spim init" );
            bxs_printfln( "\t -r + addr \t: read 1 byte " );
            bxs_printfln( "\t -w + addr + data\t: write 1 byte " );
        } else if ( !strcmp( "init", &argv[argv[1]] ) ) {
            prv_spim_init();
        } else if ( !strcmp( "-r", &argv[argv[1]] ) ) {
//            uint8_t data;
//            prv_spim_receive(1,&data,1);
//            bxs_printfln( "data :%02x", data );
//            w25x_init();
            uint32_t addr = read_deviceID();
            bxs_printfln( "addr :%02x", addr );

        } else if ( !strcmp( "-w", &argv[argv[1]] ) ) {
            uint32_t value;
            uint8_t data;
            if( sscanf( &argv[argv[2]], "%10u%1s", &value, ch ) == 1 ) {
            } else if( sscanf( &argv[argv[2]], "%*[0]%*[x|X]%8X%1s", &value, ch ) == 1 ) {
            } else if( sscanf( &argv[argv[2]], "%10u%1s", &value, ch ) == 1 ) {
            } else {
                shell_printf( "addr err\r\n" );
                return;
            }
            data = value;
            bxs_printfln( "data : %02x", data );
            prv_spim_transmit( 1, &data, 1 );

        } else {
            bxs_option_unsupport( &argv[argv[0]] );
        }
    } else {
        bxs_arg_err( &argv[argv[0]] );
    }
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void spim_add_shell_cmd( void )
{
    bxs_add_cmd( "spim", prv_spim_cmd_handler, "spim test" );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void spim_rx_full_isr( void )
{

    while( BX_READ_BIT( BX_SPIM1->STA, SPIM_STA_RFNE ) >> SPIM_STA_RFNE_POS ) {
        if( BX_READ_BIT( BX_SPIM1->CTRL, SPIM_CTRL_DFS32 ) <= SPIM_CTRL_DFS32_T_8_BITS ) {
            *spim_rx_buff = BX_SPIM1->DATA;
            spim_rx_buff += 1;
        } else if( BX_READ_BIT( BX_SPIM1->CTRL, SPIM_CTRL_DFS32 ) <= SPIM_CTRL_DFS32_T_16_BITS ) {
            *spim_rx_buff = BX_SPIM1->DATA;
            spim_rx_buff += 2;
        } else {
            *spim_rx_buff = BX_SPIM1->DATA;
            spim_rx_buff += 4;
        }
        --spim_rx_len;

    }
    if( spim_rx_len > 0 ) {
        BX_SPIM1->RXFTL = spim_rx_len > SPIM_FIFO_DEPTH ? SPIM_FIFO_DEPTH / 2 - 1 : spim_rx_len - 1;
    } else {
        BX_CLR_BIT( BX_SPIM1->SSIE, SPIM_SSIE_BIT );
        BX_MODIFY_REG( BX_SPIM1->SE, SPIM_SE_VAL, ( uint32_t ) 0 );
    }


}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void spim_tx_empty_isr( void )
{

    if( spim_tx_len ) {
        while( BX_READ_BIT( BX_SPIM1->STA, SPIM_STA_TFNF ) >> SPIM_STA_TFNF_POS ) {
            if( BX_READ_BIT( BX_SPIM1->CTRL, SPIM_CTRL_DFS32 ) <= SPIM_CTRL_DFS32_T_8_BITS ) {
                BX_SPIM1->DATA = *spim_tx_buff;
                spim_tx_buff += 1;
            } else if( BX_READ_BIT( BX_SPIM1->CTRL, SPIM_CTRL_DFS32 ) <= SPIM_CTRL_DFS32_T_16_BITS ) {
                BX_SPIM1->DATA = *spim_tx_buff;
                spim_tx_buff += 2;
            } else {
                BX_SPIM1->DATA = *spim_tx_buff;
                spim_tx_buff += 4;
            }
            --spim_tx_len;

            if( spim_tx_len == 0 ) {
                //LOG_I( "=======spim tx end========\n" );
                break;
            }
        }

        if( ( BX_READ_BIT( BX_SPIM1->STA, SPIM_STA_BUSY ) == 0 ) && ( BX_READ_REG( BX_SPIM1->SE ) == 0 ) ) {
            if( spim_hw_cs_mask ) {
                BX_MODIFY_REG( BX_SPIM1->SE, SPIM_SE_VAL, ( uint32_t ) spim_cs_sel_mask );
            } else {
                BX_MODIFY_REG( BX_SPIM1->SE, SPIM_SE_VAL, ( uint32_t ) 0xFF );
            }
        }
    } else {
        if( BX_READ_REG( BX_SPIM1->TXFL ) ) {
            BX_MODIFY_REG( BX_SPIM1->TXFTL, SPIM_TXFTL_VAL, ( uint32_t ) 0 );
        } else {
            BX_CLR_BIT( BX_SPIM1->IM, SPIM_IM_TFE );
            if( BX_READ_BIT( BX_SPIM1->CTRL, SPIM_CTRL_TM ) == SPIM_CTRL_TM_T_TX ) {
                while( BX_READ_BIT( BX_SPIM1->STA, SPIM_STA_BUSY ) == 1 );
                BX_CLR_BIT( BX_SPIM1->SSIE, SPIM_SSIE_BIT );
                BX_MODIFY_REG( BX_SPIM1->SE, SPIM_SE_VAL, ( uint32_t ) 0 );
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
void SPIM1_IRQHandler( void )
{
    uint32_t irq_stat = BX_SPIM1->IS;

    if( irq_stat == 0 ) {
        return;
    }

    if( irq_stat & SPIM_IS_MMC ) {
        irq_stat &= ~SPIM_MMCIC_BIT;
    }
    if( irq_stat & SPIM_IS_RFF ) {
        spim_rx_full_isr();
    }
    if( irq_stat & SPIM_IS_RFO ) {
        irq_stat &= ~SPIM_RXFOIC_BIT;
    }
    if( irq_stat & SPIM_IS_RFU ) {
        irq_stat &= ~SPIM_RXFUIC_BIT;
    }
    if( irq_stat & SPIM_IS_TFE ) {
        spim_tx_empty_isr();
    }
    if( irq_stat & SPIM_IS_TFO ) {

        irq_stat &= ~SPIM_TXFOIC_BIT;
    }

    if( BX_READ_BIT( BX_SPIM1->SSIE, SPIM_SSIE_BIT ) == 0 ) {
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_SPIM1 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_SPIM1 );
    }
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
