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
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include <string.h>
#include "bxfs_write_cache.h"
#include "flash.h"
#include "log.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
static struct{
    uint32_t current_buf_offset;
    uint16_t idx;
    uint8_t buf[BXFS_WRITE_CACHE_SIZE];
}bxfs_wr_cache_env;

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxfs_nvm_write_through()
{
    if(bxfs_wr_cache_env.idx)
    {
        if(bxfs_wr_cache_env.idx < BXFS_WRITE_CACHE_SIZE)
        {
            memset(&bxfs_wr_cache_env.buf[bxfs_wr_cache_env.idx],0xff,BXFS_WRITE_CACHE_SIZE-bxfs_wr_cache_env.idx);
        }
        flash_page_program(bxfs_wr_cache_env.current_buf_offset,BXFS_WRITE_CACHE_SIZE,bxfs_wr_cache_env.buf);
        bxfs_wr_cache_env.idx = 0;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxfs_nvm_program(uint32_t offset,uint32_t length,uint8_t *buffer)
{
    while(length)
    {
        bxfs_wr_cache_env.current_buf_offset = offset & ~(BXFS_WRITE_CACHE_SIZE - 1);
        uint16_t buf_available = BXFS_WRITE_CACHE_SIZE - bxfs_wr_cache_env.idx;
        if(length<=buf_available)
        {
            memcpy(&bxfs_wr_cache_env.buf[bxfs_wr_cache_env.idx],buffer,length);
            bxfs_wr_cache_env.idx += length;
            length = 0;
        }else{
            memcpy(&bxfs_wr_cache_env.buf[bxfs_wr_cache_env.idx],buffer,buf_available);
            length -= buf_available;
            buffer += buf_available;
            offset += buf_available;
            bxfs_wr_cache_env.idx += buf_available;
        }
        if(bxfs_wr_cache_env.idx == BXFS_WRITE_CACHE_SIZE)
        {
            bxfs_nvm_write_through();
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bxfs_nvm_read_with_cache(uint32_t offset, uint32_t length, uint8_t *buffer)
{
    uint32_t nvm_read_length; 
    uint8_t *cache_src = bxfs_wr_cache_env.buf;
    if(offset+length>bxfs_wr_cache_env.current_buf_offset&&offset+length<=bxfs_wr_cache_env.current_buf_offset + bxfs_wr_cache_env.idx)
    {
        if(offset<bxfs_wr_cache_env.current_buf_offset)
        {
            nvm_read_length = length - (offset+length&BXFS_WRITE_CACHE_SIZE-1);
        }else
        {
            cache_src += offset & BXFS_WRITE_CACHE_SIZE-1;
            nvm_read_length = 0;
        }       
    }else
    {
        nvm_read_length = length;
    }
    if(nvm_read_length)
    {
        flash_multi_read(offset,nvm_read_length,buffer);
        buffer += nvm_read_length;
        length -= nvm_read_length;
    }
    if(length)
    {
        memcpy(buffer,cache_src,length);
    }
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


