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

#include "fal.h"
#include "flashdb.h"
#include "bx_kernel.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static uint32_t boot_count = 0;
/* default KV nodes */
static struct fdb_default_kv_node default_kv_table[] = {
    {"username", "bluex", 0}, /* string KV */
    {"password", "123456", 0}, /* string KV */
    {"boot_count", &boot_count, sizeof( boot_count )}, /* int type KV */
};
/* KVDB object */
static struct fdb_kvdb kvdb = { 0 };

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void lock( fdb_db_t db )
{
    /* YOUR CODE HERE */
    __disable_irq();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void unlock( fdb_db_t db )
{
    /* YOUR CODE HERE */
    __enable_irq();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void kvdb_init( void )
{
    fdb_err_t result;
    struct fdb_blob blob;
    { /* database initialization */
        struct fdb_default_kv default_kv;

        default_kv.kvs = default_kv_table;
        default_kv.num = sizeof( default_kv_table ) / sizeof( default_kv_table[0] );
        /* set the lock and unlock function if you want */
        fdb_lock_set( ( fdb_db_t )&kvdb, lock, unlock );
        /* Key-Value database initialization
         *
         *       &kvdb: database object
         *       "env": database name
         *  "fdb_kvdb1": The flash partition name base on FAL. Please make sure it's in FAL partition table.
         *              Please change to YOUR partition name.
         * &default_kv: The default KV nodes. It will auto add to KVDB when first initialize successfully.
         *        NULL: The user data if you need, now is empty.
         */
        result = fdb_kvdb_init( &kvdb, "env", "kvdb", &default_kv, NULL );

        if ( result != FDB_NO_ERR ) {
            return;
        }
    }
    
    { /* GET the KV value */
        /* get the "boot_count" KV value */
        fdb_kv_get_blob( &kvdb, "boot_count", fdb_blob_make( &blob, &boot_count, sizeof( boot_count ) ) );
        /* the blob.saved.len is more than 0 when get the value successful */
        if ( blob.saved.len > 0 ) {
            bx_logln( "get the 'boot_count' value is %d\n", boot_count );
        } else {
            bx_logln( "get the 'boot_count' failed\n" );
        }
    }

    { /* CHANGE the KV value */
        /* increase the boot count */
        boot_count ++;
        /* change the "boot_count" KV's value */
        fdb_kv_set_blob( &kvdb, "boot_count", fdb_blob_make( &blob, &boot_count, sizeof( boot_count ) ) );
        //bx_logln( "set the 'boot_count' value to %d\n", boot_count );
    }
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void  app_fdb_init( void )
{
    kvdb_init();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t app_fdb_save( char * key, u8 * value, u32 value_size )
{
    fdb_err_t result;
    struct fdb_blob blob;
    
    result = fdb_kv_set_blob( &kvdb, key, fdb_blob_make( &blob, value, value_size ) );
    if ( result != FDB_NO_ERR ) {
        return BX_ERROR;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t app_fdb_get( char * key, u8 * value, u32 value_size )
{
    struct fdb_blob blob;
    fdb_kv_get_blob( &kvdb, key, fdb_blob_make( &blob, value, value_size ) );
    if ( blob.saved.len > 0 ) {
        return BX_OK;
    }
    return BX_ERROR;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



