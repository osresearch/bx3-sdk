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
#ifndef __BX_DBG_H__
#define __BX_DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config ------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "bx_sdk3_config.h"
#include "bx_type_def.h"
#include "jump_table.h"

/* exported define -----------------------------------------------------------*/
#define LOG_LVL_ASSERT                                  0
#define LOG_LVL_ERROR                                   1
#define LOG_LVL_WARN                                    2
#define LOG_LVL_INFO                                    3
#define LOG_LVL_DEBUG                                   4
#define LOG_LVL_VERBOSE                                 5

#define LVL_ASSERT                                      LOG_LVL_ASSERT
#define LVL_ERROR                                       LOG_LVL_ERROR
#define LVL_WARN                                        LOG_LVL_WARN
#define LVL_INFO                                        LOG_LVL_INFO
#define LVL_DEBUG                                       LOG_LVL_DEBUG
#define LVL_VERBOSE                                     LOG_LVL_VERBOSE


#if !defined(LOG_TAG)
#define LOG_TAG                                         ""
#endif

#if !defined(LOG_LVL)
#define LOG_LVL                                         LOG_LVL_VERBOSE
#endif

#if (LOG_LVL >= LOG_LVL_ASSERT) && (GLOBAL_LOG_LVL >= LOG_LVL_ASSERT)
#define bxlog_assert(TAG, ...) \
    LOG_OUTPUT(LOG_LVL_ASSERT,TAG,true,__VA_ARGS__)
#else
#define bxlog_assert(TAG, ...)                      ( ( void ) 0 )
#endif

#if (LOG_LVL >= LOG_LVL_ERROR) && (GLOBAL_LOG_LVL >= LOG_LVL_ERROR)
#define bxlog_error(TAG, ...) \
    LOG_OUTPUT(LOG_LVL_ERROR,TAG,true,__VA_ARGS__)
#else
#define bxlog_error(TAG, ...)                       ( ( void ) 0 )
#endif

#if (LOG_LVL >= LOG_LVL_WARN) && (GLOBAL_LOG_LVL >= LOG_LVL_WARN)
#define bxlog_worn(TAG, ...) \
    LOG_OUTPUT(LOG_LVL_WARN,TAG,true,__VA_ARGS__)
#else
#define bxlog_worn(TAG, ...)                        ( ( void ) 0 )
#endif

#if (LOG_LVL >= LOG_LVL_INFO) && (GLOBAL_LOG_LVL >= LOG_LVL_INFO)
#define bxlog_info(TAG, ...) \
    LOG_OUTPUT(LOG_LVL_INFO,TAG,true,__VA_ARGS__)
#else
#define bxlog_info(TAG, ...)                        ( ( void ) 0 )
#endif

#if (LOG_LVL >= LOG_LVL_DEBUG) && (GLOBAL_LOG_LVL >= LOG_LVL_DEBUG)
#define bxlog_debug(TAG, ...) \
    LOG_OUTPUT(LOG_LVL_DEBUG,TAG, true,__VA_ARGS__)
#else
#define bxlog_debug(TAG, ...)                       ( ( void ) 0 )
#endif

#if (LOG_LVL >= LOG_LVL_VERBOSE) && (GLOBAL_LOG_LVL >= LOG_LVL_VERBOSE)
#define bxlog_verbose(TAG, ...) \
    LOG_OUTPUT(LOG_LVL_VERBOSE,TAG, true,__VA_ARGS__)
#else
#define bxlog_verbose(TAG, ...)                     ( ( void ) 0 )
#endif

#define LOG_A( ... )                                    bxlog_assert( LOG_TAG, __VA_ARGS__ )
#define LOG_D( ... )                                    bxlog_debug( LOG_TAG, __VA_ARGS__ )
#define LOG_E( ... )                                    bxlog_error( LOG_TAG, __VA_ARGS__ )
#define LOG_W( ... )                                    bxlog_worn( LOG_TAG, __VA_ARGS__ )
#define LOG_I( ... )                                    bxlog_info( LOG_TAG, __VA_ARGS__ )
#define LOG_V( ... )                                    bxlog_verbose( LOG_TAG, __VA_ARGS__ )

#define LOG_RAW( ... )                                  LOG_OUTPUT( LOG_LVL_VERBOSE + 1,"", false,__VA_ARGS__ )
#define LOG(level,...)                                  LOG_OUTPUT(level,LOG_TAG,false,__VA_ARGS__)

#define bx_log(...)                                     LOG_OUTPUT(LOG_LVL_VERBOSE + 1,LOG_TAG,false,__VA_ARGS__)
#define bx_logln(...)                                   LOG_OUTPUT(LOG_LVL_VERBOSE + 1,LOG_TAG,true,__VA_ARGS__)


#define SHOW_VAR_BIN( var )                                     \
do{                                                             \
    int var##l = sizeof(var)*8;                                 \
    int var##i,var##j = 0;                                      \
    if(var##i == 0) {                                           \
         LOG_RAW("0B");                                         \
         break;                                                 \
    }                                                           \
    for(var##i = var##l-1; var##i >= 0; var##i --) {            \
        if(var&(1<<var##i)) break;                              \
    }                                                           \
    for(;var##i>=0; var##i -- ) {                               \
        if( var##j % 4 == 0 && var##j !=0 )                     \
            LOG_RAW(" ");                                       \
        LOG_RAW("%u", (var&(1<<var##i)) != 0);                  \
        var##j ++;                                              \
    }                                                           \
}while(0)

#define SHOW_VAR( var )                                         \
do{                                                             \
    LOG_RAW("%s(10) : %u%s",#var,(var),BX_DATA_NEWLINE_SIGN);   \
    LOG_RAW("%s(16) : %x%s",#var,(var),BX_DATA_NEWLINE_SIGN);   \
    LOG_RAW("%s(2)  : ",#var);                                  \
    SHOW_VAR_BIN(var);                                          \
    LOG_RAW("%s",BX_DATA_NEWLINE_SIGN);                         \
}while(0)

#define SHOW_ARRAY( name, len )                                 \
do{                                                             \
    LOG_RAW( "%s %u: %s", #name, len, BX_DATA_NEWLINE_SIGN );   \
    for( uint32_t name##_i = 0; name##_i<len; name##_i++ ){     \
        if( name##_i % 16 == 15 ) {                             \
            LOG_RAW( "%s", BX_DATA_NEWLINE_SIGN );              \
        }                                                       \
        LOG_RAW( "%02X " ,name[name##_i] );                     \
    }                                                           \
    LOG_RAW( "%s", BX_DATA_NEWLINE_SIGN );                      \
}while(0)

#if ( BX_ENABLE_LOG > 0 )
    #define BX_ASSERT(e)                                ((e)? (void)0 : bx_assert_failed(#e,__FILE__,__LINE__))
    typedef void ( *rwip_assert_fn )( uint32_t, uint32_t, uint32_t );
    #define RWIP_ASSERT(lvl,e,param0,param1)            if(!(e)) ((rwip_assert_fn)jump_table[RWIP_ASSERT_DBG])((lvl),(param0),(param1))

    void rwip_assert_asm( uint32_t, uint32_t, uint32_t );
    void bx_assert_failed(  char *, char *, int  );
    void log_output( int8_t, const char *, bool, const char *, ... );
    void hardfault_env_save( void *, uint32_t, uint32_t );
    void hardfault_print( void );
    void rwip_assert_c( uint32_t, uint32_t, uint32_t, uint32_t );
    void log_init( void );
    #define LOG_OUTPUT                                      log_output
#else
    #define log_init()                                      ( ( void ) 0 )
    #define LOG_OUTPUT( lvl, tag, line, fmt, ... )          ( ( void ) 0 )
    #define BX_ASSERT( e )                                  ( ( void ) 0 )
    #define RWIP_ASSERT( lvl, e, param0, param1 )           ( ( void ) 0 )
#endif /* ( BX_ENABLE_LOG > 0 ) */


#ifdef __cplusplus
}
#endif

#endif /* __BX_DBG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

