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
#define FDB_LOG_TAG "[fdb_test]"
/* private typedef -----------------------------------------------------------*/
//struct env_data {
//    int temp;
//    int humi;
//};

/* private variables ---------------------------------------------------------*/
static uint32_t boot_count = 0;
//static time_t boot_time[10] = {0, 1, 2, 3};
//static u32 tsdb_sys_time = 0;
/* default KV nodes */
static struct fdb_default_kv_node default_kv_table[] = {
//    {"username", "bluex", 0}, /* string KV */
//    {"password", "123456", 0}, /* string KV */
    {"boot_count", &boot_count, sizeof( boot_count )}, /* int type KV */
//    {"boot_time", &boot_time, sizeof( boot_time )},  /* int array type KV */
//    {"tsdb_sys_time", &tsdb_sys_time, sizeof( tsdb_sys_time )},
};
/* KVDB object */
static struct fdb_kvdb kvdb = { 0 };
/* TSDB object */
//static struct fdb_tsdb tsdb = { 0 };
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
}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//void kvdb_basic_sample( void )
//{
//    int boot_count = 0;
//    struct fdb_blob blob;

//    FDB_INFO( "==================== kvdb_basic_sample ====================\n" );

//    { /* GET the KV value */
//        /* get the "boot_count" KV value */
//        fdb_kv_get_blob( &kvdb, "boot_count", fdb_blob_make( &blob, &boot_count, sizeof( boot_count ) ) );
//        /* the blob.saved.len is more than 0 when get the value successful */
//        if ( blob.saved.len > 0 ) {
//            FDB_INFO( "get the 'boot_count' value is %d\n", boot_count );
//        } else {
//            FDB_INFO( "get the 'boot_count' failed\n" );
//        }
//    }

//    { /* CHANGE the KV value */
//        /* increase the boot count */
//        boot_count ++;
//        /* change the "boot_count" KV's value */
//        fdb_kv_set_blob( &kvdb, "boot_count", fdb_blob_make( &blob, &boot_count, sizeof( boot_count ) ) );
//        FDB_INFO( "set the 'boot_count' value to %d\n", boot_count );
//    }

//    FDB_INFO( "===========================================================\n" );
//}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//void kvdb_type_blob_sample( void )
//{
//    fdb_err_t result;
//    struct fdb_blob blob;
//    FDB_INFO( "================= kvdb_type_blob_sample ===================\n" );
//    int temp_data;

//    {
//        /* get the "temp" KV value */
//        fdb_kv_get_blob( &kvdb, "temp", fdb_blob_make( &blob, &temp_data, sizeof( temp_data ) ) );
//        /* if the "temp" KV value is not exist */
//        if( blob.saved.len <= 0 ) {
//            FDB_INFO( "There is not KV value of \"temp\"\n" );

//            FDB_INFO( "create new Key-Value\n" );

//            /* CREATE new Key-Value */
//            temp_data = 36;

//            /* It will create new KV node when "temp" KV not in database.
//             * fdb_blob_make: It's a blob make function, and it will return the blob when make finish.
//             */
//            result = fdb_kv_set_blob( &kvdb, "temp", fdb_blob_make( &blob, &temp_data, sizeof( temp_data ) ) );
//            if ( result != FDB_NO_ERR ) {
//                FDB_INFO( "fdb_kv_set_blob error: %d\n", result );
//            } else {
//                FDB_INFO( "create new Key-Value successfully\n" );
//            }
//        }
//    }

//    {
//        /* get the "temp" KV value */
//        fdb_kv_get_blob( &kvdb, "temp", fdb_blob_make( &blob, &temp_data, sizeof( temp_data ) ) );
//        if ( blob.saved.len > 0 ) {
//            FDB_INFO( "get  KV value of \"temp\" successfully .\n" );
//            FDB_INFO( "temp_data: %d\n", temp_data );
//        }
//    }

//    { /* CHANGE the KV value */
//        temp_data += 2;

//        /* change the "temp" KV's value to 38.1 */
//        result = fdb_kv_set_blob( &kvdb, "temp", fdb_blob_make( &blob, &temp_data, sizeof( temp_data ) ) );
//        if ( result != FDB_NO_ERR ) {
//            FDB_INFO( "fdb_kv_set_blob error: %d\n", result );
//        } else {
//            FDB_INFO( "get  KV value of \"temp\" successfully . new temp_data: %d\n", temp_data );
//        }
//    }

//    { /* DELETE the KV by name */
//        //fdb_kv_del(&kvdb, "temp");
//    }
//    FDB_INFO( "===========================================================\n" );
//}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//void kvdb_type_string_sample( void )
//{
//    FDB_INFO( "================= kvdb_type_string_sample =================\n" );
//    {
//        /* get the "temp" KV value */
//        char * return_value = fdb_kv_get( &kvdb, "humi" );
//        /* if the "temp" KV value is not exist */
//        if( return_value == NULL ) {
//            FDB_INFO( "There is not KV value of \"humi\"\n" );

//            FDB_INFO( "create new Key-Value\n" );

//            /* CREATE new Key-Value */
//            char humi_data[10] = "36";

//            /* It will create new KV node when "temp" KV not in database. */
//            fdb_kv_set( &kvdb, "humi", humi_data );
//        }
//    }

//    {
//        /* GET the KV value */
//        char * return_value, humi_data[10] = { 0 };

//        /* Get the "temp" KV value.
//         * NOTE: The return value saved in fdb_kv_get's buffer. Please copy away as soon as possible.
//         */
//        return_value = fdb_kv_get( &kvdb, "humi" );
//        /* the return value is NULL when get the value failed */
//        if ( return_value != NULL ) {
//            FDB_INFO( "get KV value of \"humi\" successfully\n" );
//            strncpy( humi_data, return_value, sizeof( humi_data ) );
//            FDB_INFO( "humi_data: %s\n", humi_data );
//        }
//    }

//    { /* CHANGE the KV value */
//        char humi_data[10] = "38";

//        /* change the "temp" KV's value to "38.1" */
//        fdb_kv_set( &kvdb, "humi", humi_data );

//        FDB_INFO( "change humi value: %s\n", humi_data );
//    }

//    { /* DELETE the KV by name */
//        //fdb_kv_del(&kvdb, "temp");
//    }
//    FDB_INFO( "===========================================================\n" );
//}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static fdb_time_t tsdb_get_time( void )
//{
//    return ( fdb_time_t )tsdb_sys_time;
//}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static void tsdb_sys_time_increase( void * arg )
//{
//    struct fdb_blob blob;
//    tsdb_sys_time++;
//    if( tsdb_sys_time % 10 == 0 ) {
//        fdb_kv_set_blob( &kvdb, "tsdb_sys_time", fdb_blob_make( &blob, &tsdb_sys_time, sizeof( tsdb_sys_time ) ) );
//    }
//}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static void tsdb_init( void )
//{
//    fdb_err_t result;
//    struct fdb_blob blob;
//    fdb_kv_get_blob( &kvdb, "tsdb_sys_time", fdb_blob_make( &blob, &tsdb_sys_time, sizeof( tsdb_sys_time ) ) );
//    FDB_INFO( "tsdb_sys_time:%u\n", tsdb_sys_time );
//    { /* database initialization */
//        /* set the lock and unlock function if you want */
//        fdb_lock_set( ( fdb_db_t )&tsdb, lock, unlock );
//        /* Time series database initialization
//         *
//         *       &tsdb: database object
//         *       "log": database name
//         *  "fdb_tsdb1": The flash partition name base on FAL. Please make sure it's in FAL partition table.
//         *              Please change to YOUR partition name.
//         *    get_time: The get current timestamp function.
//         *         128: maximum length of each log
//         *        NULL: The user data if you need, now is empty.
//         */
//        result = fdb_tsdb_init( &tsdb, "log", "tsdb", tsdb_get_time, 128, NULL );

//        if ( result != FDB_NO_ERR ) {
//            return;
//        }
//    }

//    bx_dwork( tsdb_sys_time_increase, NULL, 1000, BX_FOREVER );
//}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static bool query_cb( fdb_tsl_t tsl, void * arg )
//{
//    struct fdb_blob blob;
//    struct env_data data;
//    fdb_tsdb_t db = arg;

//    fdb_blob_read( ( fdb_db_t ) db, fdb_tsl_to_blob( tsl, fdb_blob_make( &blob, &data, sizeof( data ) ) ) );
//    FDB_INFO( "time: %10d, temp: %3d, humi: %3d\n", tsl->time, data.temp, data.humi );

//    return false;
//}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static void tsdb_sample( void )
//{
//    FDB_INFO( "======================== tsdb_sample ======================\n" );
//    struct fdb_blob blob;
//    fdb_err_t result;
//    { /* APPEND new TSL (time series log) */
//        struct env_data data;

//        /* append new log to TSDB */
//        data.temp = 36;
//        data.humi = 85;
//        result = fdb_tsl_append( &tsdb, fdb_blob_make( &blob, &data, sizeof( data ) ) );
//        if( result == FDB_NO_ERR ) {
//            FDB_INFO("append data successfully .\n");
//        }else{
//            FDB_INFO("append data fail .\n");
//        }
//        
//        data.temp = 38;
//        data.humi = 90;
//        result = fdb_tsl_append( &tsdb, fdb_blob_make( &blob, &data, sizeof( data ) ) );
//        if( result == FDB_NO_ERR ) {
//            FDB_INFO("append data successfully .\n");
//        }else{
//            FDB_INFO("append data fail .\n");
//        }
//    }

//    { /* QUERY the TSDB */
//        /* query all TSL in TSDB by iterator */
//        FDB_INFO("show all TSL in TSDB :\n");
//        fdb_tsl_iter( &tsdb, query_cb, &tsdb );
//    }
//    FDB_INFO( "===========================================================\n" );
//}
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
//    tsdb_init();

//    kvdb_basic_sample();
//    kvdb_type_blob_sample();
//    kvdb_type_string_sample();
//    tsdb_sample();
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



