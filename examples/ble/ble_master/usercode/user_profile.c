/**
 ****************************************************************************************
 *
 * @file glps.c
 *
 * @brief Glucose Profile Sensor implementation.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup GLPS
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
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

#ifdef IOS_SUPPORT

#define PTS_SVC_UUID_128         {0xA5,0x00,0x00,0xFB,0x0E,0x00,0x23,\
        0x9B,0xE1,0x11,0x02,0xD1,0x00,0x1C,0x00,0x00}


#define PTS_SVC_TX_CHAR_UUID_128 {0xA5,0x00,0x00,0xFB,0x0E,0X00,0X23,\
        0X9B,0XE1,0X11,0X02,0XD1,0X0f,0X1C,0X00,0X00}



#define PTS_SVC_RX_CHAR_UUID_128 {0xA5,0x00,0x00,0xFB,0x0E,0X00,0X23,\
        0X9B,0XE1,0X11,0X02,0XD1,0X01,0X1C,0X00,0X00}
#else

//#define PTS_SVC_UUID_128         {0xA6,0x00,0x00,0xFB,0x0E,0x00,0x23,\
//        0x9B,0xE1,0x11,0x02,0xD1,0x00,0x1C,0x00,0x00}

//#define PTS_SVC_TX_CHAR_UUID_128 {0xA6,0x00,0x00,0xFB,0x0E,0X00,0X23,\
//        0X9B,0XE1,0X11,0X02,0XD1,0X00,0X1C,0X00,0X00}


//#define PTS_SVC_RX_CHAR_UUID_128 {0xA6,0x00,0x00,0xFB,0x0E,0X00,0X23,\
//        0X9B,0XE1,0X11,0X02,0XD1,0X01,0X1C,0X00,0X00}

#define PTS_SVC_UUID_128         {0xC7,0xA5,0x00,0x5B,0x02,0x00,0x23,\
        0x9B,0x11,0xE1,0x02,0xD1,0x66,0x66,0x00,0x00}

#define PTS_SVC_TX_CHAR_UUID_128 {0xC7,0xA5,0x00,0x5B,0x02,0x00,0x23,\
        0x9B,0x11,0xE1,0x02,0xD1,0x66,0x66,0x00,0x00}


#define PTS_SVC_RX_CHAR_UUID_128 {0xC7,0xA5,0x00,0x5B,0x02,0x00,0x23,\
        0x9B,0x11,0xE1,0x02,0xD1,0x77,0x77,0x00,0x00}

	
#endif


        
#define PASSTHROUGH_SERVER_MAX_MTU  247
#define ATT_DESC_CLIENT_CHAR_CFG_ARRAY {0x02,0x29}

#define ATT_DECL_CHAR_ARRAY {0x03,0x28}
#define PTS_SVC_RX_BUF_SIZE (PASSTHROUGH_SERVER_MAX_MTU - 3)
#define PTS_SVC_TX_BUF_SIZE (PASSTHROUGH_SERVER_MAX_MTU - 3)

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Full GLPS Database Description - Used to add attributes into the database
static const struct attm_desc_128 pts_att_db[PTS_SVC_ATT_NUM] =
{
    // Glucose Service Declaration
    [PTS_SVC_IDX_SVC]           =   {PTS_SVC_UUID_128,    PERM(RD, ENABLE), 0, 0},

    [PTS_SVC_IDX_RX_CHAR] = {
        .uuid = ATT_DECL_CHAR_ARRAY,
        .perm = PERM(RD,ENABLE),
        .max_size = 0,
        .ext_perm= PERM(UUID_LEN,UUID_16),
    },
    [PTS_SVC_IDX_RX_VAL] = {
        .uuid = PTS_SVC_RX_CHAR_UUID_128,
        .perm = PERM(WRITE_REQ,ENABLE)|PERM(WRITE_COMMAND,ENABLE)|PERM(WP,NO_AUTH),
        .max_size = PTS_SVC_RX_BUF_SIZE,
        .ext_perm = PERM(UUID_LEN,UUID_128)|PERM(RI,ENABLE),
    },
    [PTS_SVC_IDX_TX_CHAR] = {
        .uuid = ATT_DECL_CHAR_ARRAY,
        .perm = PERM(RD,ENABLE),
        .max_size = 0,
        .ext_perm = PERM(UUID_LEN,UUID_16),
    },
    [PTS_SVC_IDX_TX_VAL] = {

        .uuid = PTS_SVC_TX_CHAR_UUID_128,
        .perm = PERM(NTF,ENABLE),
        .max_size = PTS_SVC_TX_BUF_SIZE,
        .ext_perm = PERM(UUID_LEN,UUID_128)|PERM(RI,ENABLE),
    },
    [PTS_SVC_IDX_TX_NTF_CFG] = {
      .uuid = ATT_DESC_CLIENT_CHAR_CFG_ARRAY,
      .perm = PERM(RD,ENABLE)|PERM(WRITE_REQ,ENABLE),
       .max_size = 0,
       .ext_perm = PERM(UUID_LEN,UUID_16),
    },

};

uint8_t attm_svc_create_db_128(uint16_t *shdl, const uint8_t* uuid, uint8_t *cfg_flag, uint8_t max_nb_att,
                               uint8_t *att_tbl, ke_task_id_t const dest_id,
                               const struct attm_desc_128 *att_db, uint8_t svc_perm)
{
    uint8_t nb_att = 0;
    uint8_t i;
    uint8_t status = ATT_ERR_NO_ERROR;
    struct gattm_svc_desc* svc_desc;

    //Compute number of attributes and maximal payload size
    for (i = 1; i<max_nb_att; i++)
    {
        // check within db_cfg flag if attribute is enabled or not
        if ((cfg_flag == NULL) || (((cfg_flag[i/8] >> (i%8)) & 1) == 1))
        {
            // increment number of attribute to add
            nb_att++;
        }
    }

    // Allocate service information
    svc_desc = (struct gattm_svc_desc*) ke_malloc(
                sizeof(struct gattm_svc_desc) + (sizeof(struct gattm_att_desc) * (nb_att)), KE_MEM_NON_RETENTION);

    // Initialize service info
    svc_desc->start_hdl = *shdl;
    svc_desc->nb_att = nb_att;
    svc_desc->task_id = dest_id;
    // ensure that service has a 16 bits UUID
    svc_desc->perm = svc_perm;

    // copy UUID
    memcpy(svc_desc->uuid, uuid,
            ((PERM_GET(svc_perm, SVC_UUID_LEN) == PERM_UUID_16) ? ATT_UUID_16_LEN
                : ((PERM_GET(svc_perm, SVC_UUID_LEN) == PERM_UUID_32) ? ATT_UUID_32_LEN
                        : ATT_UUID_128_LEN)));

    // Set Attribute parameters
    nb_att = 0;
    for (i = 1; i<max_nb_att; i++)
    {
        // check within db_cfg flag if attribute is enabled or not
        if ((cfg_flag == NULL) || (((cfg_flag[i/8] >> (i%8)) & 1) == 1))
        {
            // fill attribute configuration

            // ensure that service has a 16 bits UUID
            svc_desc->atts[nb_att].max_len  = att_db[i].max_size;
            svc_desc->atts[nb_att].ext_perm = att_db[i].ext_perm;
            svc_desc->atts[nb_att].perm     = att_db[i].perm;
            // copy UUID
            memcpy(svc_desc->atts[nb_att].uuid, &(att_db[i].uuid),
                    ((PERM_GET(att_db[i].ext_perm, UUID_LEN) == PERM_UUID_16) ? ATT_UUID_16_LEN
                        : ((PERM_GET(att_db[i].ext_perm, UUID_LEN) == PERM_UUID_32) ? ATT_UUID_32_LEN
                                : ATT_UUID_128_LEN)));

            // increment number of attributes
            nb_att++;
        }
    }

    // add service in database
    status = attmdb_add_service(svc_desc);

    // if service added
    if(status == ATT_ERR_NO_ERROR)
    {
        // return start handle
        *shdl = svc_desc->start_hdl;

        // update attribute table mapping
        nb_att = 0;
        for (i = 0; (i<max_nb_att) && (att_tbl != NULL); i++)
        {
            // check within db_cfg flag if attribute is enabled or not
            if ((cfg_flag == NULL) || (((cfg_flag[i/8] >> (i%8)) & 1) == 1))
            {
                //Save handle offset in attribute table
                att_tbl[i] = *shdl + nb_att;
                // increment number of attributes
                nb_att++;
            }
        }
    }

    // free service description
    ke_free(svc_desc);

    return (status);
}


/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Initialization of the GLPS module.
 * This function performs all the initializations of the Profile module.
 *  - Creation of database (if it's a service)
 *  - Allocation of profile required memory
 *  - Initialization of task descriptor to register application
 *      - Task State array
 *      - Number of tasks
 *      - Default task handler
 *
 * @param[out]    env        Collector or Service allocated environment data.
 * @param[in|out] start_hdl  Service start handle (0 - dynamically allocated), only applies for services.
 * @param[in]     app_task   Application task number.
 * @param[in]     sec_lvl    Security level (AUTH, EKS and MI field of @see enum attm_value_perm_mask)
 * @param[in]     param      Configuration parameters of profile collector or service (32 bits aligned)
 *
 * @return status code to know if profile initialization succeed or not.
 ****************************************************************************************
 */
static uint8_t user_init (struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl, struct user_db_cfg* params)
{
    //------------------ create the attribute database for the profile -------------------
    // DB Creation Statis
    uint8_t status = ATT_ERR_NO_ERROR;

    uint8_t uuid[] = PTS_SVC_UUID_128;
    // Create Glucose Database
    status = attm_svc_create_db_128(start_hdl, uuid, NULL,
            PTS_SVC_ATT_NUM, NULL, env->task, &pts_att_db[0],
            //(sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS)) | PERM(SVC_MI, ENABLE));
            PERM(SVC_MI,DISABLE)|PERM(SVC_EKS,DISABLE)|PERM(SVC_AUTH,NO_AUTH)|PERM(SVC_UUID_LEN,UUID_128) );
    //-------------------- allocate memory required for the profile  ---------------------
    if (status == ATT_ERR_NO_ERROR)
    {
        // Allocate GLPS required environment variable
        struct user_profile_env_tag* glps_env =
                (struct user_profile_env_tag* ) ke_malloc(sizeof(struct user_profile_env_tag), KE_MEM_ATT_DB);

		
        // Initialize GLPS environment
        env->env                      = (prf_env_t*) glps_env;
        glps_env->start_hdl           = *start_hdl;
        glps_env->features            = params->features;
        glps_env->prf_env.app_task    = app_task
                | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        glps_env->prf_env.prf_task    = env->task | PERM(PRF_MI, ENABLE);

        // initialize environment variable
        env->id                     = TASK_ID_USER;
        env->desc.idx_max           = 1;
        env->desc.state             = glps_env->state;
        env->desc.default_handler   = &userp_default_handler;

        ke_state_set(env->task, USER_PROFILE_IDLE);
    }

    return (status);
}

/**
 ****************************************************************************************
 * @brief Destruction of the GLPS module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void user_destroy(struct prf_task_env* env)
{
    struct user_profile_env_tag* user_env = (struct user_profile_env_tag*) env->env;

    // remove all values present in list
    while(!co_list_is_empty(&(user_env->values)))
    {
        struct co_list_hdr* hdr = co_list_pop_front(&(user_env->values));
        ke_free(hdr);
    }


    // free profile environment variables
    env->env = NULL;
    ke_free(user_env);
}

/**
 ****************************************************************************************
 * @brief Handles Connection creation
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 ****************************************************************************************
 */
static void user_create(struct prf_task_env* env, uint8_t conidx)
{

}

/**
 ****************************************************************************************
 * @brief Handles Disconnection
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 * @param[in]        reason     Detach reason
 ****************************************************************************************
 */
static void user_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{

}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// GLPS Task interface required by profile manager
const struct prf_task_cbs user_itf =
{
        (prf_init_fnct) user_init,
        user_destroy,
        user_create,
        user_cleanup,
};

/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

const struct prf_task_cbs* user_profile_prf_itf_get(void)
{
   return &user_itf;
}


/// @} GLPS
