/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "bx_fifo.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* import function prototypes ------------------------------------------------*/



/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :   data[in]        ָ��fifo�Ļ�����
 * @param   :   data_size[in]   fifo�Ļ������Ĵ�С
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_fifo_init( struct bx_fifo * pfifo, uint8_t * data, uint32_t data_size )
{
    //ASSERT(pfifo!=NULL);
    //ASSERT(data!=NULL);
    pfifo->data = data;
    pfifo->max_len = data_size;
    pfifo->head = 0;
    pfifo->tail = 0;
    pfifo->data_len = 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :   ���Fifo�ڵ�����
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_fifo_clear( struct bx_fifo * pfifo )
{
    //ASSERT(pfifo!=NULL);
    pfifo->head = 0;
    pfifo->tail = 0;
    pfifo->data_len = 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :   ��ȡFifo�п��пռ�ĳ���
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint32_t bx_fifo_get_free_len( struct bx_fifo * pfifo )
{
    //ASSERT(pfifo!=NULL);
    return pfifo->max_len - pfifo->data_len;
}
/** ---------------------------------------------------------------------------
 * @brief   :   ���� Fifo �еĲ�������
 * @note    :
 * @param   :   throwlen  �����ĳ��ȣ������ȴ��ڱ����˵����ݳ��ȣ���������
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_fifo_throw( struct bx_fifo * pfifo, uint32_t throwlen )
{
    //ASSERT(pfifo!=NULL);
    if( throwlen > 0 ) {
        if( pfifo->data_len <= throwlen ) {
            pfifo->head = pfifo->tail;
            pfifo->data_len = 0;
        } else {
            pfifo->head = ( pfifo->head + throwlen ) % pfifo->max_len;
            pfifo->data_len -= throwlen;
        }
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :   ��fifo����������
 * @note    :
 * @param   :   data[in]    ָ��Ҫ����fifo�е�����
 * @param   :   len[in]     Ҫ����fifo�е����ݵĳ���
 * @retval  :
-----------------------------------------------------------------------------*/
bool bx_fifo_push( struct bx_fifo * pfifo, uint8_t * data, uint32_t len )
{
    //ASSERT(pfifo!=NULL);
    //ASSERT(data!=NULL);
    if( pfifo->max_len - pfifo->data_len < len ) {
        return false;
    }

    for( uint32_t i = 0; i < len; i++ ) {
        pfifo->data[pfifo->tail] = data[i];
        pfifo->tail++;
        pfifo->tail = pfifo->tail % pfifo->max_len;
    }
    pfifo->data_len += len;
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
    //ASSERT(pfifo!=NULL);
    //ASSERT(data!=NULL);
    bool is_cover  = false;
    for( uint32_t i = 0; i < len; i++ ) {
        if( pfifo->tail == pfifo->head ) {
            is_cover = true;
        }
        pfifo->data[pfifo->tail] = data[i];
        pfifo->tail++;
        pfifo->tail = pfifo->tail % pfifo->max_len;

    }
    if( !is_cover ) {
        pfifo->data_len += len;
    } else {
        pfifo->head = pfifo->tail;
        pfifo->data_len = pfifo->max_len;
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
    //ASSERT(pfifo!=NULL);
    //ASSERT(data!=NULL);
    if( pfifo->data_len < len ) {
        return false;
    }

    for( uint32_t i = 0; i < len; i++ ) {
        data[i] = pfifo->data[pfifo->head];
        pfifo->head++;
        pfifo->head = pfifo->head % pfifo->max_len;
    }
    pfifo->data_len -= len;
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
    //ASSERT(pfifo!=NULL);
    //ASSERT(data!=NULL);
    //ASSERT(pop_len!=NULL);
    *pop_len = 0;
    if( pfifo->data_len > 0 ) {
        *pop_len = pfifo->data_len;
    }
    return bx_fifo_pop( pfifo, data, pfifo->data_len );
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
    //ASSERT(pfifo!=NULL);

    if ( find_data == NULL || len == 0 || len > pfifo->data_len  ) {
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
