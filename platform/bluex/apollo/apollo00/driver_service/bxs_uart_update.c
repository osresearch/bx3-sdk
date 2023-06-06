#include <stdint.h>
#include "plf.h"
#include "bx_kernel.h"
#include "bx_log.h"
#include "arch_init.h"
#include "bx_pm.h"
#include "co_math.h"
#include "ota_image.h"
#include "arch.h"
#include "bxs_uart_update.h"
#include "bxd_uart.h"
#include "flash_wrapper.h"

extern app_info_t app_info;
static data_from_uart_t uart_update_buff;
static uart_update_env_t uart_update_env;
static uint8_t uart_update_response[4][3] = 
{
    {'B','X','S'},  //start
    {'B','X','A',}, //ack
    {'B','X','N',}, //nack
    {'B','X','E',}, //error
};
static uint8_t flash_rb_buf[FLASH_PAGE_SIZE]; // read back buffer
int32_t uart_update_service_id = 0;

/* init */
void uart_update_service_init(void)
{
    uart_update_env.status = UART_UPDATE_STATUS_IDLE;
    uart_update_env.image_crc32 = 0;
    uart_update_env.image_size = 0;
    /* uart init*/
    bxd_uart_open( BX_UART1 );
    bxd_uart_set_tx_pin( BX_UART1, UART_TX_PIN );
    bxd_uart_set_rx_pin( BX_UART1, UART_RX_PIN );
    bxd_uart_set_data_bit( BX_UART1, BX_UART_DB_8B );
    bxd_uart_set_speed( BX_UART1, UART_BAUD );
    bxd_uart_set_stop_bit( BX_UART1, BX_UART_SB_ONE );
    bxd_uart_set_parity( BX_UART1, BX_UART_PARITY_NONE );
    BX_UART1->IF |= UART_IF_FIFO_EN;
}

/* uart update start */
void uart_update_start(void)
{
    bx_pm_lock(BX_PM_UART);
    if(uart_update_env.status == UART_UPDATE_STATUS_IDLE)
    {
        uart_update_env.status = UART_UPDATE_STATUS_START;
        post_msg2uart_update_service(BXM_UART_UPDATE_READ_START, 0, 0);
    }
    else
    {
        LOG_RAW("uart_update status error\r\n");
    }
}

/* rx */
static void uart_rx_payload_finish(void *param)
{
    post_msg2uart_update_service(BXM_UART_UPDATE_READ_FINISH, 0, 0);
}

static void uart_rx_header_finish(void *param)
{
    bxd_uart_intr_read(BX_UART1, (uint8_t *)&uart_update_buff.data, uart_update_buff.header.length, uart_rx_payload_finish);
}

void uart_update_uart_read_start(void)
{
    /* uart start read header */
    bxd_uart_intr_read(BX_UART1, (uint8_t *)&uart_update_buff, sizeof(uart_update_header_type), uart_rx_header_finish);
}

/* rx end */
static void uart_update_erase_flash(uint32_t offset,uint32_t image_limit)
{
    uint8_t sector_num = CEILING(image_limit,BLOCK_4K_SECTOR);
    uint8_t i;
    for(i=0;i<sector_num;++i)
    {
        flash_erase(offset,Sector_Erase);//must be sector erase ,cannot erase boot_ram.
        offset += BLOCK_4K_SECTOR;
    }
}

static void cmd_request_uart_update(void)
{
    request_uart_upate_type * request_cmd = (request_uart_upate_type*)uart_update_buff.data;
    uart_update_env.status = UART_UPDATE_STATUS_BUSY;
    uart_update_env.program_length = 0;
    uart_update_env.image_crc32 = request_cmd->crc32;
    uart_update_env.image_size = request_cmd->image_length;
    LOG_RAW("app_info.ota_base = 0x%x\r\n", app_info.ota_base);
    LOG_RAW("image_crc32 = 0x%x\r\n", uart_update_env.image_crc32);
    LOG_RAW("image_size = 0x%x\r\n", uart_update_env.image_size);

    uart_update_erase_flash(app_info.ota_base , uart_update_env.image_size + sizeof(ota_image_header_t));
    bxd_uart_write(BX_UART1, uart_update_response[DOWNLOAD_START], 3);
}

static void cmd_write_data(void)
{
    uint32_t addr = (app_info.ota_base + sizeof(ota_image_header_t));
    addr += uart_update_env.program_length;
    flash_program(addr, uart_update_buff.header.length, uart_update_buff.data);
    flash_multi_read(addr, uart_update_buff.header.length, flash_rb_buf);
    uart_update_env.program_length += uart_update_buff.header.length;
    if(memcmp(uart_update_buff.data, flash_rb_buf, uart_update_buff.header.length) != 0)
    {
        //Ð£ÑéÊ§°Ü
        bxd_uart_write(BX_UART1, uart_update_response[DOWNLOAD_NACK], 3);
        LOG_RAW("cmd_write_data error = 0x%x\r\n", addr);
        post_msg2uart_update_service(BXM_UART_UPDATE_FINISH, 0, 0);
    }
    else
    {
        bxd_uart_write(BX_UART1, uart_update_response[DOWNLOAD_ACK], 3);
    }
    
}

static void cmd_finish_uart_update(void)
{
    bxd_uart_write(BX_UART1, uart_update_response[DOWNLOAD_ACK], 3);
    uart_update_env.status = UART_UPDATE_STATUS_FINISH;
    ota_image_header_struct_t header;
    header.valid_flag   = OTA_AVAILABLE_FLAG;
    header.crc32        = uart_update_env.image_crc32;
    header.image_length = uart_update_env.image_size;
    flash_program(app_info.ota_base,sizeof(header),(void*)&header);

    post_msg2uart_update_service(BXM_UART_UPDATE_FINISH, uart_update_buff.data[0], 0);
}

void uart_update_uart_read_finish(void)
{
    if(uart_update_buff.header.header_flag != UART_UPDATE_HEADER)
    {
        bxd_uart_write(BX_UART1, uart_update_response[DOWNLOAD_ERROR], 3);
        post_msg2uart_update_service(BXM_UART_UPDATE_FINISH, 0, 0);
    }
    else
    {
        switch(uart_update_buff.header.cmd)
        {
            case REQUEST_UART_UPDATE ://     0x01
            {
                cmd_request_uart_update();
            }
            break;

            case WRITE_FIRMWARE_DATA ://     0x02
            {
                cmd_write_data();
            }
            break;

            case FINISH_UART_UPDATE ://     0x03
            {
                cmd_finish_uart_update();
            }
            break;

            default:
            {
                bxd_uart_write(BX_UART1, uart_update_response[DOWNLOAD_ERROR], 3);
                post_msg2uart_update_service(BXM_UART_UPDATE_FINISH, 0, 0);
            }
            break;
        }
    }
    if(uart_update_env.status != UART_UPDATE_STATUS_FINISH)
        post_msg2uart_update_service(BXM_UART_UPDATE_READ_START, 0, 0);
}

static void uart_update_finish(uint8_t is_reset)
{
    LOG_RAW("is_reset = %d\r\n", is_reset);
    uart_update_env.status = UART_UPDATE_STATUS_IDLE;
    bx_pm_unlock(BX_PM_UART);
    if(is_reset > 0)
        platform_reset(0);
}


static bx_err_t uart_update_service_msg_handle( s32 svc_id, u32 msg, u32 param0, u32 param1 )
{
    if ( uart_update_service_id != svc_id )
    {
        return BX_ERR_NOTSUP;
    }
    switch( msg )
    {
        case BXM_UART_UPDATE_INIT:
        {
            LOG_RAW("BXM_UART_UPDATE_SERVER_INIT\r\n");
            uart_update_service_init();
            return BX_OK;
        }

        case BXM_UART_UPDATE_START:
        {
            LOG_RAW("BXM_UART_UPDATE_START\r\n");
            uart_update_start();
            return BX_OK;
        }

        case BXM_UART_UPDATE_READ_START:
        {
            uart_update_uart_read_start();
            return BX_OK;
        }

        case BXM_UART_UPDATE_READ_FINISH:
        {
            uart_update_uart_read_finish();
            return BX_OK;
        }

        case BXM_UART_UPDATE_FINISH:
        {
            LOG_RAW("BXM_UART_UPDATE_FINISH\r\n");
            uart_update_finish((uint8_t)param0);
            return BX_OK;
        }
        default:
        {
            return BX_ERR_NOTSUP;
        }
    }
}

void bx_uart_updat_service_creat(void)
{
    struct bx_service svc;
    svc.name = "uart_update_service";
    svc.msg_handle_func = uart_update_service_msg_handle;
    svc.prop_get_func = NULL;
    svc.prop_set_func = NULL;
    uart_update_service_id = bx_register( &svc );
    if( uart_update_service_id == -1 ) {
        LOG(LOG_LVL_ERROR,"svc id alloc failed\n");
    }

    post_msg2uart_update_service(BXM_UART_UPDATE_INIT, 0, 0);
}

void post_msg2uart_update_service(uint32_t msg, uint32_t param0, uint32_t param1)
{
    bx_post(uart_update_service_id, msg, param0, param1);
}

static bxd_uart_env_t bxd_uart_env[1];
bx_err_t bxd_uart_intr_read( void * hdl, uint8_t * buff, uint32_t len, void (*callback) (void*) )
{
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    bxd_uart_env[0].rx_size = len;
    bxd_uart_env[0].p_rx_buff = buff;
    bxd_uart_env[0].rx_cplt_cb = callback;

    bxd_uart_enable_intr(hdl);
    BX_SET_BIT( BX_UARTx->DI, UART_DI_IE_RDA_AND_IDLE );
    BX_SET_BIT( BX_UARTx->IF, UART_IF_FIFO_EN );
    return BX_OK;
}

void UART1_IRQHandler( void )
{
    u8 irq_status = BX_READ_REG( BX_UART1->IF ) & 0x0F;

    switch( irq_status ) {
        case BX_UART_IRQ_RLS:
        case BX_UART_IRQ_CT:
        case BX_UART_IRQ_RDA: {
            while( 1 == BX_READ_BIT( BX_UART1->LS, UART_LS_DATA_READY ) ) {
                *bxd_uart_env[0].p_rx_buff = BX_UART1->RTD;
                bxd_uart_env[0].rx_size--;
                bxd_uart_env[0].p_rx_buff++;
                if( bxd_uart_env[0].rx_size == 0)
                {
                    BX_UART1->DI = 0;
                    bxd_uart_env[0].rx_cplt_cb( 0 );
                }
            }
        }
        break;

        default:
            break;
    }
}


















