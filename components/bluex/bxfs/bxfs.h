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
#ifndef __BXFS_H__
#define __BXFS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

/* exported types ------------------------------------------------------------*/

enum bxfs_error_code {
    BXFS_NO_ERROR,
    BXFS_RECORD_DATA_CORRUPTED,
    BXFS_INSUFFICIENT_NODE_BUF,
    BXFS_INSUFFICIENT_RECORD_DATA_BUF,
    BXFS_DIR_IDX_OVERFLOW,
    BXFS_PARENT_DIR_NOT_FOUND,
    BXFS_DIR_NOT_EXISTED,
    BXFS_DIR_NOT_EMPTY,
    BXFS_DIR_KEY_ALREADY_EXISTED,
    BXFS_RECORD_KEY_ALREADY_EXISTED,
    BXFS_RECORD_KEY_NOT_FOUND,
    BXFS_TMP_BUF_OVERFLOW,
};

typedef void * bxfs_dir_t;

typedef struct {
    uint8_t * data;
    uint16_t length;
    uint16_t record_key;
    uint8_t dir_depth;
} bxfs_hierarchy_rw_t;

typedef struct {
    uint16_t * list;
    uint16_t num;
    uint8_t dir_depth;
} bxfs_hierarchy_record_list_t;

typedef struct {
    uint16_t record_key;
    uint8_t dir_depth;
} bxfs_hierarchy_del_record_t;

/* exported variables --------------------------------------------------------*/
extern void * root_dir_ptr;

/* exported constants --------------------------------------------------------*/
#define ROOT_DIR                (root_dir_ptr)
#define BXFS_NODE_MAX           (150)
#define BXFS_SECTION_NUM        (4)
#define BXFS_SECTION_SIZE       (0x1000)

#if ( BXFS_SECTION_NUM < 3 )
#error BXFS_SECTION_NUM must be greater than or equal to 3
#endif
#if (BXFS_SECTION_SIZE % (0x1000))
#error BXFS_SECTION_SIZE must be multiple of 4KBytes
#endif


/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void        bxfs_init( uint32_t base );

uint8_t     bxfs_write( bxfs_dir_t dir, uint16_t record_name, uint8_t * data, uint16_t length );
uint16_t    bxfs_write_through( void );
uint8_t     bxfs_read( bxfs_dir_t dir, uint16_t record_name, uint8_t * data, uint16_t * length_ptr );
void        bxfs_earse_data( void );

uint8_t     bxfs_mkdir( bxfs_dir_t * dir_to_make, bxfs_dir_t upper_dir, uint16_t dir_name );
uint8_t     bxfs_del_record( bxfs_dir_t dir, uint16_t record_name );
uint8_t     bxfs_del_dir( bxfs_dir_t dir, bool force );
uint8_t     bxfs_get_child_dir_by_name( bxfs_dir_t parent, uint16_t dir_name, bxfs_dir_t * ptr );
uint16_t    bxfs_get_dir_id_max( void );
void        bxfs_print_dir_tree( void );

uint8_t     bxfs_hierarchy_write( bxfs_hierarchy_rw_t * param, ... );
uint8_t     bxfs_hierarchy_read( bxfs_hierarchy_rw_t * param, ... );
uint8_t     bxfs_hierarchy_record_list_get( bxfs_hierarchy_record_list_t * param, ... );
uint8_t     bxfs_hierarchy_del_record( bxfs_hierarchy_del_record_t * param, ... );

uint8_t     bxfs_record_list_get( bxfs_dir_t dir, uint16_t * num, uint16_t * list );

#ifdef __cplusplus
}
#endif

#endif /* __BXFS_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
