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
 * @param   :   data[in]        指向fifo的缓存区
 * @param   :   data_size[in]   fifo的缓存区的大小
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
 * @brief   :   清空Fifo内的数据
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
 * @brief   :   获取Fifo中空闲空间的长度
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
 * @brief   :   丢弃 Fifo 中的部分数据
 * @note    :
 * @param   :   throwlen  丢弃的长度，若长度大于保存了的数据长度，则丢弃所有
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
 * @brief   :   向fifo中推入数据
 * @note    :
 * @param   :   data[in]    指向要推入fifo中的数据
 * @param   :   len[in]     要推入fifo中的数据的长度
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
 * @brief   :   向fifo中推入数据
 * @note    :   当缓存区数据满的时候，新数据将覆盖旧数据
 * @param   :   data[in]    指向要推入fifo中的数据
 * @param   :   len[in]     要推入fifo中的数据的长度
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
 * @brief   :   从Fifo中弹出数据
 * @note    :
 * @param   :   data[out]   指向fifo中弹出的数据的保存地址
 * @param   :   len[in]     要从fifo中弹出的数据的长度
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
 * @brief   :   弹出所有数据
 * @note    :
 * @param   :
 * @retval  :   成功返回真，失败返回假
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
 * @brief   :   在fifo中查找第一个匹配的内存组find_data
 * @note    :
 * @param   :   find_data[in]   要查找的内存组
 * @param   :   len[in]         内存组的长度
 * @retval  :   返回 find_data 与 fifo 当前位置(head)的距离(元素数) , -1表示当前fifo
                中找不到此内存组
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
 * @brief   :   弹出数据直到遇到 end_data 内存组则停止弹出
 * @note    :   当内存租为空时,效果与bx_fifo_pop_all一样
 * @param   :   end_data[in]        结束的内存组
 * @param   :   end_data_len[in]    结束的内存组的长度
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
 * @brief   :   丢弃数据直到遇到 end_data 内存组则停止丢弃
 * @note    :   当内存租为空时,效果与 bx_fifo_clear 一样
 * @param   :   end_data[in]        结束的内存组
 * @param   :   end_data_len[in]    结束的内存组的长度
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
