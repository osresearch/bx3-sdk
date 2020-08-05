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
#ifndef __BX_RING_QUEUE_H__
#define __BX_RING_QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

/* exported types ------------------------------------------------------------*/

typedef struct {
    void * buf;
    uint16_t rd_idx;
    uint16_t wr_idx;
    uint16_t size;
    uint16_t count;
    uint8_t element_size;
} ring_queue_t;


/* exported variables --------------------------------------------------------*/

#define DEF_RING_QUEUE(name,length,type)    __attribute__((aligned(4))) uint8_t _##name##_buf[(length)*sizeof(type)];\
                                            ring_queue_t name ={\
                                                .buf = _##name##_buf,\
                                                .rd_idx = 0,\
                                                .wr_idx = 0,\
                                                .size = (length),\
                                                .count = 0,\
                                                .element_size = sizeof(type)}

#define EXTERN_RING_QUEUE(name) extern ring_queue_t name

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


void        bx_enqueue_specific( ring_queue_t * rq, void ( *copy )( uint8_t *, uint16_t, va_list * ), ... );
void        bx_enqueue( ring_queue_t *, void * );
void    *   bx_dequeue( ring_queue_t * );
//uint16_t bx_ring_queue_array_offset(ring_queue_t *,void *);
bool        bx_ring_queue_full( ring_queue_t * );
bool        bx_ring_queue_empty( ring_queue_t * );
void    *   bx_ring_queue_glance( ring_queue_t *, uint16_t );
uint16_t    bx_ring_queue_amount( ring_queue_t * );
void        bx_ring_queue_flush_all( ring_queue_t * );
uint16_t    bx_ring_queue_element_size( ring_queue_t * );

#ifdef __cplusplus
}
#endif

#endif /* __BX_RING_QUEUE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
