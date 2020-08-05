/**
  ******************************************************************************
  * @file   :   .h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BX_FIFO_H__
#define __BX_FIFO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* exported paras ------------------------------------------------------------*/\

/* exported types ------------------------------------------------------------*/
struct bx_fifo{
    uint32_t            max_len;    /* fifo的最大长度 */
    uint32_t            data_len;   /* 当前fifo的长度 */
    uint32_t            head;
    uint32_t            tail;
    uint8_t *           data;       /* 指向fifo的缓存区 */
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/
void        bx_fifo_init( struct bx_fifo * pfifo,uint8_t * data, uint32_t data_size);

void        bx_fifo_clear( struct bx_fifo * pfifo );

uint32_t    bx_fifo_get_free_len( struct bx_fifo * pfifo );

void        bx_fifo_throw( struct bx_fifo * pfifo , uint32_t throwlen);

bool        bx_fifo_push(struct bx_fifo * pfifo,uint8_t * data, uint32_t len );

void        bx_fifo_pushex( struct bx_fifo * pfifo, uint8_t * data, uint32_t len );
    
bool        bx_fifo_pop(struct bx_fifo * pfifo, uint8_t * data, uint32_t len );

bool        bx_fifo_pop_all(struct bx_fifo * pfifo, uint8_t * data, uint32_t * pop_len );

int         bx_fifo_first( struct bx_fifo * pfifo, uint8_t * data, uint32_t len );

bool        bx_fifo_pop_until( struct bx_fifo * pfifo, uint8_t * data,uint8_t * end_data, uint32_t end_data_len );

void        bx_fifo_throw_until( struct bx_fifo * pfifo, uint8_t * end_data, uint32_t end_data_len );


#ifdef __cplusplus
}
#endif

#endif /* __BX_FIFO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
