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
#ifndef __QUEUED_ASYNC_FRAMEWORK_H__
#define __QUEUED_ASYNC_FRAMEWORK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_ring_queue.h"
#include "compiler.h"

/* exported types ------------------------------------------------------------*/

typedef void ( *queued_async_callback_t )( void *, void *, uint8_t );

typedef const struct {
    ring_queue_t * rq;
    void ( *pre_process )( void * );
    queued_async_callback_t common_callback;
} queued_async_framework_t;

typedef struct {
    ring_queue_t * rq[2];
    void ( *pre_process )( void * );
    queued_async_callback_t common_callback;
    bool current_high_priority;
} priority_queued_async_framework_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

#define DEF_QUEUED_ASYNC_PROCESS(name,queue_length,data_type,process_func,common_cb) \
    DEF_RING_QUEUE(name##_q,(queue_length),data_type);\
    queued_async_framework_t name = {\
        .rq = &name##_q,\
        .pre_process = (void (*)(void *))process_func,\
        .common_callback = (queued_async_callback_t)common_cb,\
    };

#define QUEUED_ASYNC_PROCESS_COMMON_CALLBACK(name,queue_length,data_type,process_func,common_cb) \
    _Static_assert(common_cb != NULL,"common callback must be valid");\
    DEF_QUEUED_ASYNC_PROCESS(name,queue_length,data_type,process_func,common_cb);

#define QUEUED_ASYNC_PROCESS_SPECIFIC_CALLBACK(name,queue_length,data_type,process_func) \
    typedef struct{\
        data_type data;\
        queued_async_callback_t callback;\
    }name##_async_process_q_t;\
    DEF_QUEUED_ASYNC_PROCESS(name,queue_length,name##_async_process_q_t,process_func,NULL);



#define DEF_PRIORITY_QUEUED_ASYNC_PROCESS(name,queue_length,high_priority_queue_length,data_type,process_func,common_cb) \
    DEF_RING_QUEUE(name##_q0,(queue_length), data_type);\
    DEF_RING_QUEUE(name##_q1,(high_priority_queue_length), data_type);\
    priority_queued_async_framework_t name = {\
        .rq = {&name##_q0,&name##_q1},\
        .pre_process = (void (*)(void *))process_func,\
        .common_callback = (queued_async_callback_t)common_cb,\
    };

#define PRIORITY_QUEUED_ASYNC_PROCESS_COMMON_CALLBACK(name,queue_length,high_priority_queue_length,data_type,process_func,common_cb) \
    _Static_assert(common_cb != NULL,"common callback must be valid");\
    DEF_PRIORITY_QUEUED_ASYNC_PROCESS(name,queue_length,high_priority_queue_length,data_type,process_func,common_cb)

/* exported functions --------------------------------------------------------*/

void    *   queued_async_process_get_current( queued_async_framework_t * inst );
uint16_t    queued_async_process_get_amount( queued_async_framework_t * inst );
bool        queued_async_process_start( queued_async_framework_t * inst, void * data, queued_async_callback_t cb );
void        queued_async_process_end( queued_async_framework_t * inst, void * cb_dummy, uint8_t cb_status );

void    *   priority_queued_async_process_get_current( priority_queued_async_framework_t * inst );
uint16_t    priority_queued_async_process_get_amount( priority_queued_async_framework_t * inst, bool high_priority );
bool        priority_queued_async_process_start( priority_queued_async_framework_t * inst, bool high_priority, void * data, queued_async_callback_t cb );
void        priority_queued_async_process_end( priority_queued_async_framework_t * inst, void * cb_dummy, uint8_t cb_status );


#ifdef __cplusplus
}
#endif

#endif /* __QUEUED_ASYNC_FRAMEWORK_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
