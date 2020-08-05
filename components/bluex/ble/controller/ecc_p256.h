/**
 ****************************************************************************************
 *
 * @file ecc_p256.h
 *
 * @brief  ECC functions for P256
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 ****************************************************************************************
 */

#ifndef ECC_P256_H_
#define ECC_P256_H_


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#include "jump_table.h"
#if (SECURE_CONNECTIONS)

#include <stdint.h>
#include <stdbool.h>
#include "ke_task.h"
#include "app_hwecc_wrapper.h"
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * STRUCTURE DEFINITIONS
 ****************************************************************************************
 */

/// Multiplication result message structure
struct ecc_result_ind
{
    uint8_t key_res_x[32];
    uint8_t key_res_y[32];
};


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * Initialize Elliptic Curve algorithm
 ****************************************************************************************
 */

void ecc_init(bool reset);

/**
 ****************************************************************************************
 * @brief Generate a Secret Key compliant with ECC P256 algorithm
 *
 * If key is forced, just check its validity
 *
 * @param[out] secret_key Private key - MSB First
 * @param[in]  forced True if provided key is forced, else generate it.
 ****************************************************************************************
 */
#ifdef __RAM_CODE__
void ecc_gen_new_secret_key(uint8_t* secret_key, bool forced);
#else
typedef void (*ecc_gen_new_secret_key_fn)(uint8_t* secret_key, bool forced);
#define ecc_gen_new_secret_key(secret_key, forced) ((ecc_gen_new_secret_key_fn)jump_table[ECC_GEN_NEW_SECRET_KEY])((secret_key),(forced))
#endif // (__RAM_CODE__)
/**
 ****************************************************************************************
 * @brief Generate a new Public key pair using ECC P256 algorithm
 *
 * @param[in] secret_key Private key - MSB First
 * @param[in] blocking   Force to run full algorithm without continue mode
 ****************************************************************************************
 */
#ifdef __RAM_CODE__
void ecc_gen_new_public_key(uint8_t* secret_key256, ke_msg_id_t msg_id, ke_task_id_t task_id);
#else
typedef void (*ecc_gen_new_public_key_fn)(uint8_t* secret_key256, ke_msg_id_t msg_id, ke_task_id_t task_id);
#define ecc_gen_new_public_key(secret_key256,msg_id,task_id) ((ecc_gen_new_public_key_fn)jump_table[ECC_GEN_NEW_PUBLIC_KEY])((secret_key256),(msg_id),(task_id))
#endif
/**
 ****************************************************************************************
 * @brief Generate a new DHKey using ECC P256 algorithm
 *
 * @param[in] secret_key Private key                  - MSB First
 * @param[in] pub_key_x  Peer public key x coordinate - LSB First
 * @param[in] pub_key_y  Peer public key y coordinate - LSB First
 * @param[in] msg_id     Message task ID for the result indication
 * @param[in] task_id    Client task ID (Task type + instance)
 ****************************************************************************************
 */
#ifdef __RAM_CODE__
void ecc_generate_key256(const uint8_t* secret_key, const uint8_t* public_key_x, const uint8_t* public_key_y, ke_msg_id_t msg_id, ke_task_id_t task_id);
#else
typedef void (*ecc_generate_key256_fn)(const uint8_t* secret_key, const uint8_t* public_key_x, const uint8_t* public_key_y, ke_msg_id_t msg_id, ke_task_id_t task_id);
#define ecc_generate_key256(secret_key,public_key_x,public_key_y,msg_id,task_id) ((ecc_generate_key256_fn)jump_table[ECC_GENERATE_KEY256])((secret_key),(public_key_x),(public_key_y),(msg_id),(task_id))
#endif // (__RAM_CODE__)
/**
 ****************************************************************************************
 * @brief Abort a current DHKey generation procedure
 *
 * @param[in] task_id    Client task ID (Task type + instance)
 ****************************************************************************************
 */
void ecc_abort_key256_generation(ke_task_id_t task_id);

/**
 ****************************************************************************************
 * @brief Retrieve debug private and public keys
 *
 * @param[out] secret_key Private key             - MSB First
 * @param[out] pub_key_x  Public key x coordinate - LSB First
 * @param[out] pub_key_y  Public key y coordinate - LSB First
 ****************************************************************************************
 */
void ecc_get_debug_Keys(uint8_t*secret_key, uint8_t* pub_key_x, uint8_t* pub_key_y);


void ecc_gen_new_public_key_usr(uint8_t *secret_key,uint8_t *public_x,uint8_t *public_y,ecc_cb_t cb);

#endif // (SECURE_CONNECTIONS)


#endif /* ECC_P256_H_ */
