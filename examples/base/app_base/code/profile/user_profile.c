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

/* includes ------------------------------------------------------------------*/

#include "rwip_config.h"

#include "gap.h"
#include "gattc_task.h"
#include "attm.h"
#include "user_profile.h"
#include "user_profile_task.h"
#include "prf_utils.h"

#include "ke_mem.h"
#include "co_utils.h"

#include "gattm_task.h"
#include "attm_db.h"

/* private define ------------------------------------------------------------*/
#define PTS_SVC_UUID_128                                {0xC7, 0xA5, 0x00, 0x5B, 0x02, 0x00, 0x23, \
        0x9B, 0x11, 0xE1, 0x02, 0xD1, 0x66, 0x66, 0x00, 0x00}

#define PTS_SVC_TX_CHAR_UUID_128                        {0xC7, 0xA5, 0x00, 0x5B, 0x02, 0x00, 0x23, \
        0x9B, 0x11, 0xE1, 0x02, 0xD1, 0x66, 0x66, 0x00, 0x00}


#define PTS_SVC_RX_CHAR_UUID_128                        {0xC7, 0xA5, 0x00, 0x5B, 0x02, 0x00, 0x23, \
        0x9B, 0x11, 0xE1, 0x02, 0xD1, 0x77, 0x77, 0x00, 0x00}




#define PASSTHROUGH_SERVER_MAX_MTU                      247
#define ATT_DESC_CLIENT_CHAR_CFG_ARRAY                  {0x02, 0x29}

#define ATT_DECL_CHAR_ARRAY                             {0x03, 0x28}
#define PTS_SVC_RX_BUF_SIZE                             ( PASSTHROUGH_SERVER_MAX_MTU - 3 )
#define PTS_SVC_TX_BUF_SIZE                             ( PASSTHROUGH_SERVER_MAX_MTU - 3 )

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static const struct attm_desc_128 pts_att_db[USER_PROFILE_SVC_ATT_NUM] = {
    // Glucose Service Declaration
    [USER_PROFILE_SVC_IDX_SVC]           =   {PTS_SVC_UUID_128,    PERM( RD, ENABLE ), 0, 0},

    [USER_PROFILE_SVC_IDX_RX_CHAR] = {
        .uuid = ATT_DECL_CHAR_ARRAY,
        .perm = PERM( RD, ENABLE ),
        .max_size = 0,
        .ext_perm = PERM( UUID_LEN, UUID_16 ),
    },
    [USER_PROFILE_SVC_IDX_RX_VAL] = {
        .uuid = PTS_SVC_RX_CHAR_UUID_128,
        .perm = PERM( WRITE_REQ, ENABLE ) | PERM( WRITE_COMMAND, ENABLE ) | PERM( WP, NO_AUTH ),
        .max_size = PTS_SVC_RX_BUF_SIZE,
        .ext_perm = PERM( UUID_LEN, UUID_128 ) | PERM( RI, ENABLE ),
    },
    [USER_PROFILE_SVC_IDX_TX_CHAR] = {
        .uuid = ATT_DECL_CHAR_ARRAY,
        .perm = PERM( RD, ENABLE ),
        .max_size = 0,
        .ext_perm = PERM( UUID_LEN, UUID_16 ),
    },
    [USER_PROFILE_SVC_IDX_TX_VAL] = {

        .uuid = PTS_SVC_TX_CHAR_UUID_128,
        .perm = PERM( NTF, ENABLE ),
        .max_size = PTS_SVC_TX_BUF_SIZE,
        .ext_perm = PERM( UUID_LEN, UUID_128 ) | PERM( RI, ENABLE ),
    },
    [USER_PROFILE_SVC_IDX_TX_NTF_CFG] = {
        .uuid = ATT_DESC_CLIENT_CHAR_CFG_ARRAY,
        .perm = PERM( RD, ENABLE ) | PERM( WRITE_REQ, ENABLE ),
        .max_size = 0,
        .ext_perm = PERM( UUID_LEN, UUID_16 ),
    },

};
/* exported variables --------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t attm_svc_create_db_128( uint16_t * shdl, const uint8_t * uuid, uint8_t * cfg_flag, uint8_t max_nb_att,
                                uint8_t * att_tbl, ke_task_id_t const dest_id,
                                const struct attm_desc_128 * att_db, uint8_t svc_perm )
{
    uint8_t nb_att = 0;
    uint8_t i;
    uint8_t status = ATT_ERR_NO_ERROR;
    struct gattm_svc_desc * svc_desc;

    for ( i = 1; i < max_nb_att; i++ ) {
        if ( ( cfg_flag == NULL ) || ( ( ( cfg_flag[i / 8] >> ( i % 8 ) ) & 1 ) == 1 ) ) {
            nb_att++;
        }
    }

    svc_desc = ( struct gattm_svc_desc * ) ke_malloc(
                   sizeof( struct gattm_svc_desc ) + ( sizeof( struct gattm_att_desc ) * ( nb_att ) ), KE_MEM_NON_RETENTION );

    svc_desc->start_hdl = *shdl;
    svc_desc->nb_att = nb_att;
    svc_desc->task_id = dest_id;
    svc_desc->perm = svc_perm;

    memcpy( svc_desc->uuid, uuid,
            ( ( PERM_GET( svc_perm, SVC_UUID_LEN ) == PERM_UUID_16 ) ? ATT_UUID_16_LEN
              : ( ( PERM_GET( svc_perm, SVC_UUID_LEN ) == PERM_UUID_32 ) ? ATT_UUID_32_LEN
                  : ATT_UUID_128_LEN ) ) );


    nb_att = 0;
    for ( i = 1; i < max_nb_att; i++ ) {
        if ( ( cfg_flag == NULL ) || ( ( ( cfg_flag[i / 8] >> ( i % 8 ) ) & 1 ) == 1 ) ) {
            svc_desc->atts[nb_att].max_len  = att_db[i].max_size;
            svc_desc->atts[nb_att].ext_perm = att_db[i].ext_perm;
            svc_desc->atts[nb_att].perm     = att_db[i].perm;
            memcpy( svc_desc->atts[nb_att].uuid, &( att_db[i].uuid ),
                    ( ( PERM_GET( att_db[i].ext_perm, UUID_LEN ) == PERM_UUID_16 ) ? ATT_UUID_16_LEN
                      : ( ( PERM_GET( att_db[i].ext_perm, UUID_LEN ) == PERM_UUID_32 ) ? ATT_UUID_32_LEN
                          : ATT_UUID_128_LEN ) ) );
            nb_att++;
        }
    }

    status = attmdb_add_service( svc_desc );

    if( status == ATT_ERR_NO_ERROR ) {
        *shdl = svc_desc->start_hdl;
        nb_att = 0;
        for ( i = 0; ( i < max_nb_att ) && ( att_tbl != NULL ); i++ ) {
            if ( ( cfg_flag == NULL ) || ( ( ( cfg_flag[i / 8] >> ( i % 8 ) ) & 1 ) == 1 ) ) {
                att_tbl[i] = *shdl + nb_att;
                nb_att++;
            }
        }
    }

    ke_free( svc_desc );

    return ( status );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint8_t user_profile_init ( struct prf_task_env * env, uint16_t * start_hdl, uint16_t app_task, uint8_t sec_lvl, struct user_proflie_data * params )
{
    uint8_t status = ATT_ERR_NO_ERROR;
    uint8_t uuid[] = PTS_SVC_UUID_128;
    status = attm_svc_create_db_128( start_hdl, uuid, NULL,
                                     USER_PROFILE_SVC_ATT_NUM, NULL, env->task, &pts_att_db[0],
                                     PERM( SVC_MI, DISABLE ) | PERM( SVC_EKS, DISABLE ) | PERM( SVC_AUTH, NO_AUTH ) | PERM( SVC_UUID_LEN, UUID_128 ) );
    if ( status == ATT_ERR_NO_ERROR ) {
        struct user_profile_env_tag * glps_env =
            ( struct user_profile_env_tag * ) ke_malloc( sizeof( struct user_profile_env_tag ), KE_MEM_ATT_DB );


        env->env                      = ( prf_env_t * ) glps_env;
        glps_env->start_hdl           = *start_hdl;
        glps_env->value               = params->value;
        glps_env->prf_env.app_task    = app_task
                                        | ( PERM_GET( sec_lvl, SVC_MI ) ? PERM( PRF_MI, ENABLE ) : PERM( PRF_MI, DISABLE ) );
        glps_env->prf_env.prf_task    = env->task | PERM( PRF_MI, ENABLE );

        env->id                     = TASK_ID_USER;
        env->desc.idx_max           = USER_PROFILE_IDX_MAX;
        env->desc.state             = glps_env->state;
        env->desc.default_handler   = &user_profile_handler;

        ke_state_set( env->task, USER_PROFILE_IDLE );
    }

    return ( status );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void user_profile_destroy( struct prf_task_env * env )
{
    struct user_profile_env_tag * user_env = ( struct user_profile_env_tag * ) env->env;

    env->env = NULL;
    ke_free( user_env );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void user_profile_create( struct prf_task_env * env, uint8_t conidx )
{

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void user_profile_cleanup( struct prf_task_env * env, uint8_t conidx, uint8_t reason )
{

}
/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

/*========================= end of exported function =========================*/

const struct prf_task_cbs user_profile_itf = {
    ( prf_init_fnct ) user_profile_init,
    user_profile_destroy,
    user_profile_create,
    user_profile_cleanup,
};

const struct prf_task_cbs * user_profile_prf_itf_get( void )
{
    return &user_profile_itf;
}


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
