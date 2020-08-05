#ifndef _REG_COMMON_EM_FT_H_
#define _REG_COMMON_EM_FT_H_

#include <stdint.h>
#include "_reg_common_em_ft.h"
#include "compiler.h"
#include "arch.h"
#include "em_map.h"
#include "reg_access.h"

#define REG_COMMON_EM_FT_COUNT 1

#define REG_COMMON_EM_FT_DECODING_MASK 0x00000000

#define REG_COMMON_EM_FT_ADDR_GET(idx) (EM_FT_OFFSET + (idx) * REG_COMMON_EM_FT_SIZE)

/**
 * @brief FREQTAB register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  15:08              FREQODD   0x0
 *  07:00             FREQEVEN   0x0
 * </pre>
 */
#define EM_COMMON_FREQTAB_ADDR   (0x00128000 + EM_FT_OFFSET)
#define EM_COMMON_FREQTAB_INDEX  0x00000000
#define EM_COMMON_FREQTAB_RESET  0x00000000
#define EM_COMMON_FREQTAB_COUNT  20

__INLINE uint16_t em_common_freqtab_get(int elt_idx, int reg_idx)
{
    ASSERT_ERR(reg_idx <= 19);
    return EM_RD(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2);
}

__INLINE void em_common_freqtab_set(int elt_idx, int reg_idx, uint16_t value)
{
    ASSERT_ERR(reg_idx <= 19);
    EM_WR(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2, value);
}

// field definitions
#define EM_COMMON_FREQODD_MASK    ((uint16_t)0x0000FF00)
#define EM_COMMON_FREQODD_LSB     8
#define EM_COMMON_FREQODD_WIDTH   ((uint16_t)0x00000008)
#define EM_COMMON_FREQEVEN_MASK   ((uint16_t)0x000000FF)
#define EM_COMMON_FREQEVEN_LSB    0
#define EM_COMMON_FREQEVEN_WIDTH  ((uint16_t)0x00000008)

#define EM_COMMON_FREQODD_RST     0x0
#define EM_COMMON_FREQEVEN_RST    0x0

__INLINE void em_common_freqtab_pack(int elt_idx, int reg_idx, uint8_t freqodd, uint8_t freqeven)
{
    ASSERT_ERR(reg_idx <= 19);
    ASSERT_ERR((((uint16_t)freqodd << 8) & ~((uint16_t)0x0000FF00)) == 0);
    ASSERT_ERR((((uint16_t)freqeven << 0) & ~((uint16_t)0x000000FF)) == 0);
    EM_WR(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2,  ((uint16_t)freqodd << 8) | ((uint16_t)freqeven << 0));
}

__INLINE void em_common_freqtab_unpack(int elt_idx, int reg_idx, uint8_t* freqodd, uint8_t* freqeven)
{
    ASSERT_ERR(reg_idx <= 19);
    uint16_t localVal = EM_RD(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2);

    *freqodd = (localVal & ((uint16_t)0x0000FF00)) >> 8;
    *freqeven = (localVal & ((uint16_t)0x000000FF)) >> 0;
}

__INLINE uint8_t em_common_freqtab_freqodd_getf(int elt_idx, int reg_idx)
{
    ASSERT_ERR(reg_idx <= 19);
    uint16_t localVal = EM_RD(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2);
    return ((localVal & ((uint16_t)0x0000FF00)) >> 8);
}

__INLINE void em_common_freqtab_freqodd_setf(int elt_idx, int reg_idx, uint8_t freqodd)
{
    ASSERT_ERR(reg_idx <= 19);
    ASSERT_ERR((((uint16_t)freqodd << 8) & ~((uint16_t)0x0000FF00)) == 0);
    EM_WR(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2, (EM_RD(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2) & ~((uint16_t)0x0000FF00)) | ((uint16_t)freqodd << 8));
}

__INLINE uint8_t em_common_freqtab_freqeven_getf(int elt_idx, int reg_idx)
{
    ASSERT_ERR(reg_idx <= 19);
    uint16_t localVal = EM_RD(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2);
    return ((localVal & ((uint16_t)0x000000FF)) >> 0);
}

__INLINE void em_common_freqtab_freqeven_setf(int elt_idx, int reg_idx, uint8_t freqeven)
{
    ASSERT_ERR(reg_idx <= 19);
    ASSERT_ERR((((uint16_t)freqeven << 0) & ~((uint16_t)0x000000FF)) == 0);
    EM_WR(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2, (EM_RD(EM_COMMON_FREQTAB_ADDR + elt_idx * REG_COMMON_EM_FT_SIZE + reg_idx * 2) & ~((uint16_t)0x000000FF)) | ((uint16_t)freqeven << 0));
}


#endif // _REG_COMMON_EM_FT_H_

