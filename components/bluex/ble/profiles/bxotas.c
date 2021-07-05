/**
 ****************************************************************************************
 *
 * @file bxota.c
 *
 * @brief Apollo BLE OTA Implementation.
 *
 * Copyright (C) Apollo 2015-2016
 *
 *
 ****************************************************************************************
 */

 /**
 ****************************************************************************************
 * @addtogroup BXOTAS
 * @{
 ****************************************************************************************
 */

 /*
 * INCLUDE FILES
 ****************************************************************************************
 */
 #include "rwip_config.h"
 #if (BLE_BXOTA_SERVER)
 #include <stddef.h>
 #include "attm.h"
 #include "prf_utils.h"
 #include "prf.h"
 #include "plf.h"
 #include "flash.h"
 #include "bxotas.h"
 #include "ke_mem.h"
 #include "log.h"
 #include "bxotas_task.h"
 #include "co_math.h"
 #include "arch_init.h"
 #include "ota_image.h"
 
#include "bx_fifo.h"
#include "bx_dbg.h"
 /*
 * MACROS
 ****************************************************************************************
 */



 /*
 * DECLARATIONS
 ****************************************************************************************
 */
extern app_info_t app_info;

uint8_t         flash_data_buff[FLASH_PAGE_SIZE*2];
uint8_t         flash_page_buff[FLASH_PAGE_SIZE];
uint32_t        program_length;

uint32_t        program_length_backup;

struct  bx_fifo xfifo;
/*
 * BXOTA ATTRIBUTES
 ****************************************************************************************
 */
 const struct attm_desc bxotas_att_db[BXOTAS_IDX_NB] =
 {
    [BXOTAS_IDX_SVC] = {ATT_DECL_PRIMARY_SERVICE,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_CTRL_CHAR] = {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_CTRL_VAL] = {ATT_CHAR_BXOTA_CTRL,PERM(WRITE_REQ,ENABLE)|PERM(IND,ENABLE),PERM(RI,ENABLE),sizeof(bxota_ctrl_t)},
    [BXOTAS_IDX_CTRL_IND_CFG] = {ATT_DESC_CLIENT_CHAR_CFG,PERM(RD,ENABLE)|PERM(WRITE_REQ,ENABLE),0,0},
    [BXOTAS_IDX_DATA_CHAR] = {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_DATA_VAL] = {ATT_CHAR_BXOTA_DATA,PERM(WRITE_COMMAND,ENABLE)|PERM(RD,ENABLE),PERM(RI,ENABLE),BXOTA_ATT_DATA_MAX_LENGTH},
};

 /*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
static uint8_t bxotas_init (struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl,  void *params)
{
    uint8_t status = attm_svc_create_db(start_hdl, ATT_SVC_BXOTA, NULL, BXOTAS_IDX_NB, NULL, env->task, bxotas_att_db, sec_lvl);
    if(status == ATT_ERR_NO_ERROR)
    {
        struct bxotas_env_tag *bxotas_env = (struct bxotas_env_tag *)ke_malloc(sizeof(struct bxotas_env_tag),KE_MEM_ATT_DB);
        env->env = &bxotas_env->prf_env;
        bxotas_env->start_hdl = *start_hdl;
        bxotas_env->prf_env.app_task = app_task | PERM(PRF_MI, DISABLE);
        bxotas_env->prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);
        env->id = TASK_ID_BXOTAS;
        env->desc.idx_max = BXOTAS_IDX_MAX;
        env->desc.state = bxotas_env->state;
        env->desc.default_handler = &bxotas_default_handler;

        ke_state_set(env->task,BXOTAS_IDLE);
    }
    return status;
}
static void bxotas_destroy(struct prf_task_env* env)
{
    struct bxotas_env_tag *bxotas_env =(struct bxotas_env_tag *)env->env;
    env->env = NULL;
    ke_free(bxotas_env);
}

static void bxotas_create(struct prf_task_env* env, uint8_t conidx)
{
    /* Nothing to do */
}

static void bxotas_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    uint8_t status = ke_state_get(env->task);
    struct bxotas_env_tag *bxotas_env =(struct bxotas_env_tag *)env->env;
    if(status == BXOTAS_BUSY && conidx == bxotas_env->conidx)
    {
        ke_state_set(env->task,BXOTAS_IDLE);
    }
}

 /*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
const struct prf_task_cbs bxotas_itf =
{
    bxotas_init,
    bxotas_destroy,
    bxotas_create,
    bxotas_cleanup
};
 
 /*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
const struct prf_task_cbs *bxotas_prf_itf_get()
{
    return &bxotas_itf;
}

void bxotas_image_validation(struct bxotas_env_tag *bxotas_env)
{
    ota_image_header_struct_t header;
    
    header.valid_flag   = OTA_AVAILABLE_FLAG;
    header.crc32        = bxotas_env->ota_image_content_crc32;
    header.image_length = bxotas_env->ota_image_content_size;

    bx_log("app_info.ota_base  = 0x%x\r\n"      , app_info.ota_base);
    bx_log("header.image_length  = 0x%x\r\n"    , header.image_length);
    bx_log("header.crc32 = 0x%x\r\n"            , header.crc32);
    uint32_t remain;
    bx_fifo_pop_all( &xfifo, flash_page_buff ,&remain );
    if( remain > 0 ) {
        uint32_t addr = (app_info.ota_base + sizeof(ota_image_header_t));
        addr += program_length;
        bx_logln("%08X",addr);
        
        flash_program(addr,remain,flash_page_buff);
        program_length += remain;
        bx_logln("program total len :%d %x",program_length,program_length);
    }
    
    flash_program(app_info.ota_base,sizeof(header),(void*)&header);
    
    bx_logln("end ota");
}

void bxotas_erase_flash(uint32_t offset,uint32_t image_limit)
{
    uint8_t sector_num = CEILING(image_limit,BLOCK_4K_SECTOR);
    uint8_t i;
    for(i=0;i<sector_num;++i)
    {
        flash_erase(offset,Sector_Erase);//must be sector erase ,cannot erase boot_ram.
        offset += BLOCK_4K_SECTOR;
    }
}

void bxotas_flash_cleanup_for_ota(struct bxotas_env_tag *bxotas_env)
{
    //ota_image_base  = 0x40100
    //ota_image_content_size  = 0xca74
    //ota_image_full_size  = 0xcb74
    //ota_image_crc32 = 0x3aeab920

    bx_log("ota_image_base  = 0x%x\r\n"         , app_info.ota_base + sizeof(ota_image_header_t));
    bx_log("ota_image_content_size  = 0x%x\r\n" , bxotas_env->ota_image_content_size);
    bx_log("ota_image_full_size  = 0x%x\r\n"    , bxotas_env->ota_image_full_size);
    bx_log("ota_image_crc32 = 0x%x\r\n"         , bxotas_env->ota_image_content_crc32);
    
    bx_fifo_init(&xfifo,&flash_data_buff[0],sizeof( flash_data_buff ));
    program_length = 0;
    bxotas_erase_flash(app_info.ota_base , bxotas_env->ota_image_full_size + sizeof(ota_image_header_t));
}

void bxotas_program_flash(struct bxotas_env_tag *bxotas_env,uint16_t segment_id,uint8_t const *data,uint16_t length)
{
    //uint32_t addr = (app_info.ota_base + sizeof(ota_image_header_t)) + (bxotas_env->current_block *(BXOTA_ACK_MAP_SIZE * 8) + segment_id) * bxotas_env->segment_data_length;
    
    //bx_logln("%08X %08X",addr,length);
    //FLASH_PAGE_SIZE
    if( !bx_fifo_push(&xfifo,(uint8_t *)data, length) ){
       bx_logln("push fail-------------------------------------");
    }
    if( bx_fifo_pop( &xfifo, flash_page_buff, FLASH_PAGE_SIZE ) ) {
        uint32_t addr = (app_info.ota_base + sizeof(ota_image_header_t));
        addr += program_length;
        flash_program(addr,FLASH_PAGE_SIZE,&flash_page_buff[0]);
        program_length+= FLASH_PAGE_SIZE;
        //bx_logln("%08X",addr);
    }
}

#endif //BLE_BXOTA_SERVER
 /// @} BXOTAS
 
