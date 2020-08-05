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
#include "bxfs.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
#define RECORD_KEY1     1
#define RECORD1         "abcd"
#define RECORD_KEY2     2
#define RECORD2         "efgh"
#define RECORD_KEY3     3
#define RECORD3         "1234567890"


#define RECORD_KEY4     4
#define RECORD4         "abcd4"
#define RECORD_KEY5     5
#define RECORD5         "efgh5"
#define RECORD_KEY6     6
#define RECORD6         "12345678906"

/* private variables ---------------------------------------------------------*/
uint8_t tmp[20];

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

void bxfs_test()
{
#if 1
    bxfs_dir_t dir0,dir1,dir2, dir3;
    uint8_t rslt = bxfs_mkdir(&dir0,ROOT_DIR,5);
    rslt = bxfs_mkdir(&dir1,dir0,5);
    rslt = bxfs_mkdir(&dir2,dir1,5);
    rslt = bxfs_mkdir(&dir3,dir2,5);
    
    rslt = bxfs_write(dir2,RECORD_KEY1,RECORD1,sizeof(RECORD1));
    rslt = bxfs_write(dir2,RECORD_KEY2,RECORD2,sizeof(RECORD2));
    rslt = bxfs_write(dir1,RECORD_KEY3,RECORD3,sizeof(RECORD3));

    rslt = bxfs_write(dir0,RECORD_KEY4,RECORD4,sizeof(RECORD4));
    rslt = bxfs_write(dir1,RECORD_KEY6,RECORD6,sizeof(RECORD6));
    rslt = bxfs_write(dir3,RECORD_KEY5,RECORD5,sizeof(RECORD5));
    
    //
#endif
    bxfs_print_dir_tree();


    
    uint16_t length = 20;
    rslt = bxfs_read(dir2,RECORD_KEY1,tmp,&length);
    length = 20;
    rslt = bxfs_read(dir1,RECORD_KEY3,tmp,&length);
    rslt = bxfs_read(dir2,RECORD_KEY2,tmp,&length);
    uint16_t list_length;
    rslt = bxfs_record_list_get(dir2,&list_length,(uint16_t*)tmp);
    rslt = bxfs_del_record(dir1,RECORD_KEY3);
    rslt = bxfs_del_dir(dir0,false);
    rslt = bxfs_del_dir(dir0,true);
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
