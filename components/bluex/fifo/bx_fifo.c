/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "bx_fifo.h"
#include <string.h>

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
#define FIFO_ASSERT( p )                 ( ( void ) 0U )
//#define FIFO_ASSERT( p )                 if( !(p) ) while(1)

#define FIFO_IS_VALID(b)                 ((b) != NULL && (b)->data != NULL && (b)->max_len > 0)
#define FIFO_MIN(x, y)                   ((x) < (y) ? (x) : (y))
#define FIFO_MAX(x, y)                   ((x) > (y) ? (x) : (y))

/* exported variables --------------------------------------------------------*/

/* import function prototypes ------------------------------------------------*/



/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :   Initialize buffer handle to default values with size and buffer data array
 * @note    :
 * @param   :   
 * @param   :   
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_fifo_init( struct bx_fifo * pfifo, uint8_t * data, uint32_t data_size )
{
    FIFO_ASSERT(pfifo!=NULL);
    FIFO_ASSERT(data!=NULL);
    FIFO_ASSERT(data_size);
    
    pfifo->data = data;
    pfifo->max_len = data_size;
    pfifo->head = 0;
    pfifo->tail = 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :   Resets buffer to default values. Buffer size is not modified
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_fifo_clear( struct bx_fifo * pfifo )
{
    if (FIFO_IS_VALID(pfifo)) {
        pfifo->head = 0;
        pfifo->tail = 0;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :   Get available size in buffer for write operation
 * @note    :
 * @param   :
 * @retval  :   Number of free bytes in memory
-----------------------------------------------------------------------------*/
uint32_t bx_fifo_get_free_len( struct bx_fifo * pfifo )
{
    uint32_t size, tail, head;

    if (!FIFO_IS_VALID(pfifo)) {
        return 0;
    }

    /* Use temporary values in case they are changed during operations */
    tail = pfifo->tail;
    head = pfifo->head;
    if (tail == head) {
        size = pfifo->max_len;
    } else if (head > tail) {
        size = head - tail;
    } else {
        size = pfifo->max_len - (tail - head);
    }

    /* Buffer free size is always 1 less than actual size */
    return size - 1;
}
/** ---------------------------------------------------------------------------
 * @brief   :   Get number of bytes currently available in buffer
 * @note    :
 * @param   :
 * @retval  :   Number of bytes ready to be read
-----------------------------------------------------------------------------*/
uint32_t bx_fifo_get_len( struct bx_fifo * pfifo )
{
    uint32_t tail, head, size;

    if (!FIFO_IS_VALID(pfifo)) {
        return 0;
    }

    /* Use temporary values in case they are changed during operations */
    tail = pfifo->tail;
    head = pfifo->head;
    if (tail == head) {
        size = 0;
    } else if (tail > head) {
        size = tail - head;
    } else {
        size = pfifo->max_len - (head - tail);
    }
    return size;
}
/** ---------------------------------------------------------------------------
 * @brief   :   ���� Fifo �еĲ�������
 * @note    :
 * @param   :   throwlen  �����ĳ��ȣ������ȴ��ڱ����˵����ݳ��ȣ���������
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_fifo_throw( struct bx_fifo * pfifo, uint32_t throwlen )
{
    FIFO_ASSERT(pfifo!=NULL);
    if( throwlen > 0 ) {
        if( bx_fifo_get_len(pfifo) <= throwlen ) {
            pfifo->head = pfifo->tail;
        } else {
            pfifo->head = ( pfifo->head + throwlen ) % pfifo->max_len;
        }
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :   Write data to buffer.
 * @param   :   [in]pfifo   handle
 * @param   :   [in]data    Pointer to data to write into buffer
 * @param   :   [in]len     Number of bytes to write
 * @retval  :   Number of bytes written to buffer.
 * @note    :   When returned value is less than `len`, there was no enough 
                memory available to copy full data array
-----------------------------------------------------------------------------*/
bool bx_fifo_push( struct bx_fifo * pfifo, uint8_t * data, uint32_t len )
{
    uint32_t tocopy, free;
    const uint8_t* d = data;

    if (!FIFO_IS_VALID(pfifo) || data == NULL || len == 0) {
        return false;
    }

    /* Calculate maximum number of bytes available to write */
    free = bx_fifo_get_free_len(pfifo);
    if (free < len) {
        return false;
    }

    /* Step 1: Write data to linear part of buffer */
    tocopy = FIFO_MIN(pfifo->max_len - pfifo->tail, len);
    memcpy(&pfifo->data[pfifo->tail], d, tocopy);
    pfifo->tail += tocopy;
    len -= tocopy;

    /* Step 2: Write data to beginning of buffer (overflow part) */
    if (len > 0) {
        memcpy(pfifo->data, &d[tocopy], len);
        pfifo->tail = len;
    }

    /* Step 3: Check end of buffer */
    if (pfifo->tail >= pfifo->max_len) {
        pfifo->tail = 0;
    }
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :   ��fifo����������
 * @note    :   ����������������ʱ�������ݽ����Ǿ�����
 * @param   :   data[in]    ָ��Ҫ����fifo�е�����
 * @param   :   len[in]     Ҫ����fifo�е����ݵĳ���
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_fifo_pushex( struct bx_fifo * pfifo, uint8_t * data, uint32_t len )
{
    uint32_t tocopy;
    const uint8_t* d = data;

    if (!FIFO_IS_VALID(pfifo) || data == NULL || len == 0) {
        return;
    }
    /* Step 1: Write data to linear part of buffer */
    tocopy = FIFO_MIN(pfifo->max_len - pfifo->tail, len);
    memcpy(&pfifo->data[pfifo->tail], d, tocopy);
    pfifo->tail += tocopy;
    len -= tocopy;

    /* Step 2: Write data to beginning of buffer (overflow part) */
    if (len > 0) {
        memcpy(pfifo->data, &d[tocopy], len);
        pfifo->tail = len;
    }

    /* Step 3: Check end of buffer */
    if (pfifo->tail >= pfifo->max_len) {
        pfifo->tail = 0;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :   ��Fifo�е�������
 * @note    :
 * @param   :   data[out]   ָ��fifo�е��������ݵı����ַ
 * @param   :   len[in]     Ҫ��fifo�е��������ݵĳ���
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_fifo_pop( struct bx_fifo * pfifo, uint8_t * data, uint32_t len )
{
    uint32_t tocopy, full;
    uint8_t* d = data;

    if (!FIFO_IS_VALID(pfifo) || data == NULL || len == 0) {
        return 0;
    }

    /* Calculate maximum number of bytes available to read */
    full = bx_fifo_get_len(pfifo);
    if (full < len) {
        return false;
    }

    /* Step 1: Read data from linear part of buffer */
    tocopy = FIFO_MIN(pfifo->max_len - pfifo->head, len);
    memcpy(d, &pfifo->data[pfifo->head], tocopy);
    pfifo->head += tocopy;
    len -= tocopy;

    /* Step 2: Read data from beginning of buffer (overflow part) */
    if (len > 0) {
        memcpy(&d[tocopy], pfifo->data, len);
        pfifo->head = len;
    }

    /* Step 3: Check end of buffer */
    if (pfifo->head >= pfifo->max_len) {
        pfifo->head = 0;
    }
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :   ������������
 * @note    :
 * @param   :
 * @retval  :   �ɹ������棬ʧ�ܷ��ؼ�
-----------------------------------------------------------------------------*/
bool bx_fifo_pop_all( struct bx_fifo * pfifo, uint8_t * data, uint32_t * pop_len )
{
    FIFO_ASSERT(pop_len!=NULL);
    *pop_len = bx_fifo_get_len(pfifo);
    return bx_fifo_pop( pfifo, data, *pop_len );
}
/** ---------------------------------------------------------------------------
 * @brief   :   ��fifo�в��ҵ�һ��ƥ����ڴ���find_data
 * @note    :
 * @param   :   find_data[in]   Ҫ���ҵ��ڴ���
 * @param   :   len[in]         �ڴ���ĳ���
 * @retval  :   ���� find_data �� fifo ��ǰλ��(head)�ľ���(Ԫ����) , -1��ʾ��ǰfifo
                ���Ҳ������ڴ���
-----------------------------------------------------------------------------*/
int bx_fifo_first( struct bx_fifo * pfifo, uint8_t * find_data, uint32_t len )
{
    FIFO_ASSERT(pfifo!=NULL);

    if ( find_data == NULL || len == 0 || len > bx_fifo_get_len(pfifo)  ) {
        return -1;
    }

    struct bx_fifo fifo1 = *pfifo;
    struct bx_fifo fifo2 = *pfifo;
    uint8_t data;
    uint32_t match_count = 0;
    int32_t distance = 0 ;
    while ( bx_fifo_pop( &fifo2, &data, 1 ) ) {
        if ( data == find_data[match_count] ) {
            match_count++;
            if ( match_count == len ) {
                return distance;
            }
        } else {
            distance++;
            match_count = 0;
            bx_fifo_throw( &fifo1, 1 );
            fifo2 = fifo1;
        }
    }
    return -1;
}

/** ---------------------------------------------------------------------------
 * @brief   :   ��������ֱ������ end_data �ڴ�����ֹͣ����
 * @note    :   ���ڴ���Ϊ��ʱ,Ч����bx_fifo_pop_allһ��
 * @param   :   end_data[in]        �������ڴ���
 * @param   :   end_data_len[in]    �������ڴ���ĳ���
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_fifo_pop_until( struct bx_fifo * pfifo,
                        uint8_t * data,
                        uint8_t * end_data,
                        uint32_t end_data_len )
{
    bx_fifo_first( pfifo, end_data, end_data_len );
    return false;
}
/** ---------------------------------------------------------------------------
 * @brief   :   ��������ֱ������ end_data �ڴ�����ֹͣ����
 * @note    :   ���ڴ���Ϊ��ʱ,Ч���� bx_fifo_clear һ��
 * @param   :   end_data[in]        �������ڴ���
 * @param   :   end_data_len[in]    �������ڴ���ĳ���
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_fifo_throw_until(   struct bx_fifo * pfifo,
                            uint8_t * end_data,
                            uint32_t end_data_len )
{
    int distance = bx_fifo_first( pfifo, end_data, end_data_len );
    if( distance < 0 ) {
        bx_fifo_clear( pfifo );
    }
    bx_fifo_throw( pfifo, distance );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
