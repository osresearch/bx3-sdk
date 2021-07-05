/**
  ******************************************************************************
  * @file   :   main.c
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
#include <fal.h>

#include "flash_wrapper.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
/* private variables ---------------------------------------------------------*/
/* exported variables --------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int init(void)
{
    flash_wakeup();
    return 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int read(long offset, uint8_t *buf, size_t size)
{
//    size_t i;
//    uint32_t addr = rf01_flash.addr + offset;
//    for (i = 0; i < size; i++, addr++, buf++)
//    {
//        *buf = *(uint8_t *) addr;
//    }
//    return size;
    
    if( flash_std_read(offset,size,buf) != PERIPH_NO_ERROR )
        return -1;
    return size;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int write(long offset, const uint8_t *buf, size_t size)
{
//    bx_log("before write 0x%08X 0x%08X %8u:",offset,buf,size);
//    for (u32 i = 0; i < size; i++)
//    {
//        bx_log("%02x ",buf[i]);
//    }
//    bx_logln("");
    
    if( flash_program(offset,size,(uint8_t *)buf) != PERIPH_NO_ERROR )
        return -1;

//    u8 read_buf[128];
//    u32 write_len = size;
//    bx_log("after  write 0x%08X 0x%08X %8u:",offset,buf,size);
//    do{
//        u32 read_len = write_len>128?128:write_len;
//        
//        if( flash_std_read(offset,read_len,read_buf) != PERIPH_NO_ERROR )
//            return -1;
//        for (u32 i = 0; i < size; i++)
//        {
//            bx_log("%02x ",read_buf[i]);
//        }
//        offset += read_len;
//        write_len -=read_len;
//    }
//    while(write_len>0);
//    bx_logln("");
    return size;
    
    
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int erase(long offset, size_t size)
{
    periph_err_t flash_status;
    size_t erased_size = 0;
    uint32_t cur_erase_sector;
    uint32_t addr = rf01_flash.addr + offset;

    /* start erase */
    /* it will stop when erased size is greater than setting size */
    while (erased_size < size)
    {
        cur_erase_sector = (addr + erased_size)&0xFFFFF000;
        flash_status = flash_erase(cur_erase_sector,Sector_Erase);
        if (flash_status != PERIPH_NO_ERROR)
        {
            return -1;
        }
        erased_size += 0x1000;
    }
    return size;
}
/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

/*========================= end of exported function =========================*/
const struct fal_flash_dev rf01_flash =
{
    .name       = "rf01_onchip",
    .addr       = 0x800000,
    .len        = 1024*1024,
    .blk_size   = 4*1024,
    .ops        = {init, read, write, erase},
    .write_gran = 8
};

