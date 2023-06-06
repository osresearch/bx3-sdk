#ifndef __BXS_UART_UPDATE_H__
#define __BXS_UART_UPDATE_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "bx_msg_type_def.h"

#define UART_TX_PIN             12
#define UART_RX_PIN             13
//BX_UART_BD_115200     BX_UART_BD_921600       BX_UART_BD_2000000
#define UART_BAUD               BX_UART_BD_2000000
#define UART_UPDATE_HEADER      0xAD
#define BLOCK_4K_SECTOR         0x1000


#define DOWNLOAD_START      0
#define DOWNLOAD_ACK        1
#define DOWNLOAD_NACK       2
#define DOWNLOAD_ERROR      3


enum uart_update_cmd
{
    REQUEST_UART_UPDATE = 0x01,
    WRITE_FIRMWARE_DATA = 0x02,
    FINISH_UART_UPDATE = 0x03,
};

enum bx_msg_uart_update_server
{
    BXM_UART_UPDATE_SERVER_FIRST = BXM_FIRST_USER_MSG,
    BXM_UART_UPDATE_INIT,

    BXM_UART_UPDATE_START,

    BXM_UART_UPDATE_READ_START,
    BXM_UART_UPDATE_READ_FINISH,

    BXM_UART_UPDATE_FINISH,
};

typedef enum
{
    UART_UPDATE_STATUS_IDLE,
    UART_UPDATE_STATUS_START,
    UART_UPDATE_STATUS_BUSY,
    UART_UPDATE_STATUS_FINISH,
    UART_UPDATE_STATUS_MAX,
}uart_update_status_t;

typedef struct 
{
    uart_update_status_t status;
    uint32_t image_crc32;
    uint32_t image_size;
    uint32_t program_length;
}uart_update_env_t;

typedef struct 
{
    uint32_t crc32;
    uint32_t image_length;
}request_uart_upate_type;

typedef struct
{
    uint8_t header_flag;
    uint8_t cmd;
    uint16_t length;
}uart_update_header_type;

typedef struct
{
    uart_update_header_type header;
    uint8_t data[256];
}data_from_uart_t;

typedef struct
{
    uint8_t                         *p_tx_buff;
    uint32_t                        tx_size;
    uint8_t                         *p_rx_buff;
    uint32_t                        rx_size;
    void (* tx_cplt_cb)(void *);
    void (* rx_cplt_cb)(void *);
}bxd_uart_env_t;


void bx_uart_updat_service_creat(void);
void post_msg2uart_update_service(uint32_t msg, uint32_t param0, uint32_t param1);
bx_err_t bxd_uart_intr_read( void * hdl, uint8_t * buff, uint32_t len, void (*callback) (void*) );



#ifdef __cplusplus
}
#endif

#endif /* __BXS_UART_UPDATE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

