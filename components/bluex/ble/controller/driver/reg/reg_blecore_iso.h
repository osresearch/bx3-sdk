#ifndef _REG_BLECORE_ISO_H_
#define _REG_BLECORE_ISO_H_

#include <stdint.h>
#include "_reg_blecore_iso.h"
#include "compiler.h"
#include "arch.h"
#include "reg_access.h"

#define REG_BLECORE_ISO_COUNT 92

#define REG_BLECORE_ISO_DECODING_MASK 0x000001FF

/**
 * @brief ISOCHANCNTL register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     04            RETXACKEN   0
 *     03              SYNCGEN   0
 *     02            ISOCHANEN   0
 *  01:00              ISOTYPE   0x0
 * </pre>
 */
#define BLE_ISOCHANCNTL_ADDR   0x20100150
#define BLE_ISOCHANCNTL_OFFSET 0x00000150
#define BLE_ISOCHANCNTL_INDEX  0x00000054
#define BLE_ISOCHANCNTL_RESET  0x00000000

__INLINE uint32_t ble_isochancntl_get(int elt_idx)
{
    return REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
}

__INLINE void ble_isochancntl_set(int elt_idx, uint32_t value)
{
    REG_BLE_WR(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, value);
}

// field definitions
#define BLE_RETXACKEN_BIT    ((uint32_t)0x00000010)
#define BLE_RETXACKEN_POS    4
#define BLE_SYNCGEN_BIT      ((uint32_t)0x00000008)
#define BLE_SYNCGEN_POS      3
#define BLE_ISOCHANEN_BIT    ((uint32_t)0x00000004)
#define BLE_ISOCHANEN_POS    2
#define BLE_ISOTYPE_MASK     ((uint32_t)0x00000003)
#define BLE_ISOTYPE_LSB      0
#define BLE_ISOTYPE_WIDTH    ((uint32_t)0x00000002)

#define BLE_RETXACKEN_RST    0x0
#define BLE_SYNCGEN_RST      0x0
#define BLE_ISOCHANEN_RST    0x0
#define BLE_ISOTYPE_RST      0x0

__INLINE void ble_isochancntl_pack(int elt_idx, uint8_t retxacken, uint8_t syncgen, uint8_t isochanen, uint8_t isotype)
{
    ASSERT_ERR((((uint32_t)retxacken << 4) & ~((uint32_t)0x00000010)) == 0);
    ASSERT_ERR((((uint32_t)syncgen << 3) & ~((uint32_t)0x00000008)) == 0);
    ASSERT_ERR((((uint32_t)isochanen << 2) & ~((uint32_t)0x00000004)) == 0);
    ASSERT_ERR((((uint32_t)isotype << 0) & ~((uint32_t)0x00000003)) == 0);
    REG_BLE_WR(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE,  ((uint32_t)retxacken << 4) | ((uint32_t)syncgen << 3) | ((uint32_t)isochanen << 2) | ((uint32_t)isotype << 0));
}

__INLINE void ble_isochancntl_unpack(int elt_idx, uint8_t* retxacken, uint8_t* syncgen, uint8_t* isochanen, uint8_t* isotype)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);

    *retxacken = (localVal & ((uint32_t)0x00000010)) >> 4;
    *syncgen = (localVal & ((uint32_t)0x00000008)) >> 3;
    *isochanen = (localVal & ((uint32_t)0x00000004)) >> 2;
    *isotype = (localVal & ((uint32_t)0x00000003)) >> 0;
}

__INLINE uint8_t ble_retxacken_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

__INLINE void ble_retxacken_setf(int elt_idx, uint8_t retxacken)
{
    ASSERT_ERR((((uint32_t)retxacken << 4) & ~((uint32_t)0x00000010)) == 0);
    REG_BLE_WR(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00000010)) | ((uint32_t)retxacken << 4));
}

__INLINE uint8_t ble_syncgen_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

__INLINE void ble_syncgen_setf(int elt_idx, uint8_t syncgen)
{
    ASSERT_ERR((((uint32_t)syncgen << 3) & ~((uint32_t)0x00000008)) == 0);
    REG_BLE_WR(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00000008)) | ((uint32_t)syncgen << 3));
}

__INLINE uint8_t ble_isochanen_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

__INLINE void ble_isochanen_setf(int elt_idx, uint8_t isochanen)
{
    ASSERT_ERR((((uint32_t)isochanen << 2) & ~((uint32_t)0x00000004)) == 0);
    REG_BLE_WR(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00000004)) | ((uint32_t)isochanen << 2));
}

__INLINE uint8_t ble_isotype_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

__INLINE void ble_isotype_setf(int elt_idx, uint8_t isotype)
{
    ASSERT_ERR((((uint32_t)isotype << 0) & ~((uint32_t)0x00000003)) == 0);
    REG_BLE_WR(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOCHANCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00000003)) | ((uint32_t)isotype << 0));
}

/**
 * @brief ISOMUTECNTL register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     31                  TOG   0
 *     19            MUTE_SINK   0
 *     18          MUTE_SOURCE   0
 *     17               INVL_1   0
 *     16               INVL_0   0
 *  07:00         MUTE_PATTERN   0x0
 * </pre>
 */
#define BLE_ISOMUTECNTL_ADDR   0x20100154
#define BLE_ISOMUTECNTL_OFFSET 0x00000154
#define BLE_ISOMUTECNTL_INDEX  0x00000055
#define BLE_ISOMUTECNTL_RESET  0x00000000

__INLINE uint32_t ble_isomutecntl_get(int elt_idx)
{
    return REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
}

__INLINE void ble_isomutecntl_set(int elt_idx, uint32_t value)
{
    REG_BLE_WR(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, value);
}

// field definitions
#define BLE_TOG_BIT             ((uint32_t)0x80000000)
#define BLE_TOG_POS             31
#define BLE_MUTE_SINK_BIT       ((uint32_t)0x00080000)
#define BLE_MUTE_SINK_POS       19
#define BLE_MUTE_SOURCE_BIT     ((uint32_t)0x00040000)
#define BLE_MUTE_SOURCE_POS     18
#define BLE_INVL_1_BIT          ((uint32_t)0x00020000)
#define BLE_INVL_1_POS          17
#define BLE_INVL_0_BIT          ((uint32_t)0x00010000)
#define BLE_INVL_0_POS          16
#define BLE_MUTE_PATTERN_MASK   ((uint32_t)0x000000FF)
#define BLE_MUTE_PATTERN_LSB    0
#define BLE_MUTE_PATTERN_WIDTH  ((uint32_t)0x00000008)

#define BLE_TOG_RST             0x0
#define BLE_MUTE_SINK_RST       0x0
#define BLE_MUTE_SOURCE_RST     0x0
#define BLE_INVL_1_RST          0x0
#define BLE_INVL_0_RST          0x0
#define BLE_MUTE_PATTERN_RST    0x0

__INLINE void ble_isomutecntl_pack(int elt_idx, uint8_t mutesink, uint8_t mutesource, uint8_t invl1, uint8_t invl0, uint8_t mutepattern)
{
    ASSERT_ERR((((uint32_t)mutesink << 19) & ~((uint32_t)0x00080000)) == 0);
    ASSERT_ERR((((uint32_t)mutesource << 18) & ~((uint32_t)0x00040000)) == 0);
    ASSERT_ERR((((uint32_t)invl1 << 17) & ~((uint32_t)0x00020000)) == 0);
    ASSERT_ERR((((uint32_t)invl0 << 16) & ~((uint32_t)0x00010000)) == 0);
    ASSERT_ERR((((uint32_t)mutepattern << 0) & ~((uint32_t)0x000000FF)) == 0);
    REG_BLE_WR(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE,  ((uint32_t)mutesink << 19) | ((uint32_t)mutesource << 18) | ((uint32_t)invl1 << 17) | ((uint32_t)invl0 << 16) | ((uint32_t)mutepattern << 0));
}

__INLINE void ble_isomutecntl_unpack(int elt_idx, uint8_t* tog, uint8_t* mutesink, uint8_t* mutesource, uint8_t* invl1, uint8_t* invl0, uint8_t* mutepattern)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);

    *tog = (localVal & ((uint32_t)0x80000000)) >> 31;
    *mutesink = (localVal & ((uint32_t)0x00080000)) >> 19;
    *mutesource = (localVal & ((uint32_t)0x00040000)) >> 18;
    *invl1 = (localVal & ((uint32_t)0x00020000)) >> 17;
    *invl0 = (localVal & ((uint32_t)0x00010000)) >> 16;
    *mutepattern = (localVal & ((uint32_t)0x000000FF)) >> 0;
}

__INLINE uint8_t ble_tog_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

__INLINE uint8_t ble_mute_sink_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

__INLINE void ble_mute_sink_setf(int elt_idx, uint8_t mutesink)
{
    ASSERT_ERR((((uint32_t)mutesink << 19) & ~((uint32_t)0x00080000)) == 0);
    REG_BLE_WR(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00080000)) | ((uint32_t)mutesink << 19));
}

__INLINE uint8_t ble_mute_source_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

__INLINE void ble_mute_source_setf(int elt_idx, uint8_t mutesource)
{
    ASSERT_ERR((((uint32_t)mutesource << 18) & ~((uint32_t)0x00040000)) == 0);
    REG_BLE_WR(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00040000)) | ((uint32_t)mutesource << 18));
}

__INLINE uint8_t ble_invl_1_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

__INLINE void ble_invl_1_setf(int elt_idx, uint8_t invl1)
{
    ASSERT_ERR((((uint32_t)invl1 << 17) & ~((uint32_t)0x00020000)) == 0);
    REG_BLE_WR(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00020000)) | ((uint32_t)invl1 << 17));
}

__INLINE uint8_t ble_invl_0_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

__INLINE void ble_invl_0_setf(int elt_idx, uint8_t invl0)
{
    ASSERT_ERR((((uint32_t)invl0 << 16) & ~((uint32_t)0x00010000)) == 0);
    REG_BLE_WR(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00010000)) | ((uint32_t)invl0 << 16));
}

__INLINE uint8_t ble_mute_pattern_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x000000FF)) >> 0);
}

__INLINE void ble_mute_pattern_setf(int elt_idx, uint8_t mutepattern)
{
    ASSERT_ERR((((uint32_t)mutepattern << 0) & ~((uint32_t)0x000000FF)) == 0);
    REG_BLE_WR(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOMUTECNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x000000FF)) | ((uint32_t)mutepattern << 0));
}

/**
 * @brief ISOCURRENTTXPTR register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  31:16            ISOTXPTR1   0x0
 *  15:00            ISOTXPTR0   0x0
 * </pre>
 */
#define BLE_ISOCURRENTTXPTR_ADDR   0x20100158
#define BLE_ISOCURRENTTXPTR_OFFSET 0x00000158
#define BLE_ISOCURRENTTXPTR_INDEX  0x00000056
#define BLE_ISOCURRENTTXPTR_RESET  0x00000000

__INLINE uint32_t ble_isocurrenttxptr_get(int elt_idx)
{
    return REG_BLE_RD(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
}

__INLINE void ble_isocurrenttxptr_set(int elt_idx, uint32_t value)
{
    REG_BLE_WR(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, value);
}

// field definitions
#define BLE_ISOTXPTR1_MASK   ((uint32_t)0xFFFF0000)
#define BLE_ISOTXPTR1_LSB    16
#define BLE_ISOTXPTR1_WIDTH  ((uint32_t)0x00000010)
#define BLE_ISOTXPTR0_MASK   ((uint32_t)0x0000FFFF)
#define BLE_ISOTXPTR0_LSB    0
#define BLE_ISOTXPTR0_WIDTH  ((uint32_t)0x00000010)

#define BLE_ISOTXPTR1_RST    0x0
#define BLE_ISOTXPTR0_RST    0x0

__INLINE void ble_isocurrenttxptr_pack(int elt_idx, uint16_t isotxptr1, uint16_t isotxptr0)
{
    ASSERT_ERR((((uint32_t)isotxptr1 << 16) & ~((uint32_t)0xFFFF0000)) == 0);
    ASSERT_ERR((((uint32_t)isotxptr0 << 0) & ~((uint32_t)0x0000FFFF)) == 0);
    REG_BLE_WR(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE,  ((uint32_t)isotxptr1 << 16) | ((uint32_t)isotxptr0 << 0));
}

__INLINE void ble_isocurrenttxptr_unpack(int elt_idx, uint16_t* isotxptr1, uint16_t* isotxptr0)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);

    *isotxptr1 = (localVal & ((uint32_t)0xFFFF0000)) >> 16;
    *isotxptr0 = (localVal & ((uint32_t)0x0000FFFF)) >> 0;
}

__INLINE uint16_t ble_isotxptr1_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0xFFFF0000)) >> 16);
}

__INLINE void ble_isotxptr1_setf(int elt_idx, uint16_t isotxptr1)
{
    ASSERT_ERR((((uint32_t)isotxptr1 << 16) & ~((uint32_t)0xFFFF0000)) == 0);
    REG_BLE_WR(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0xFFFF0000)) | ((uint32_t)isotxptr1 << 16));
}

__INLINE uint16_t ble_isotxptr0_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x0000FFFF)) >> 0);
}

__INLINE void ble_isotxptr0_setf(int elt_idx, uint16_t isotxptr0)
{
    ASSERT_ERR((((uint32_t)isotxptr0 << 0) & ~((uint32_t)0x0000FFFF)) == 0);
    REG_BLE_WR(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOCURRENTTXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x0000FFFF)) | ((uint32_t)isotxptr0 << 0));
}

/**
 * @brief ISOCURRENTRXPTR register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  31:16            ISORXPTR1   0x0
 *  15:00            ISORXPTR0   0x0
 * </pre>
 */
#define BLE_ISOCURRENTRXPTR_ADDR   0x2010015C
#define BLE_ISOCURRENTRXPTR_OFFSET 0x0000015C
#define BLE_ISOCURRENTRXPTR_INDEX  0x00000057
#define BLE_ISOCURRENTRXPTR_RESET  0x00000000

__INLINE uint32_t ble_isocurrentrxptr_get(int elt_idx)
{
    return REG_BLE_RD(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
}

__INLINE void ble_isocurrentrxptr_set(int elt_idx, uint32_t value)
{
    REG_BLE_WR(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, value);
}

// field definitions
#define BLE_ISORXPTR1_MASK   ((uint32_t)0xFFFF0000)
#define BLE_ISORXPTR1_LSB    16
#define BLE_ISORXPTR1_WIDTH  ((uint32_t)0x00000010)
#define BLE_ISORXPTR0_MASK   ((uint32_t)0x0000FFFF)
#define BLE_ISORXPTR0_LSB    0
#define BLE_ISORXPTR0_WIDTH  ((uint32_t)0x00000010)

#define BLE_ISORXPTR1_RST    0x0
#define BLE_ISORXPTR0_RST    0x0

__INLINE void ble_isocurrentrxptr_pack(int elt_idx, uint16_t isorxptr1, uint16_t isorxptr0)
{
    ASSERT_ERR((((uint32_t)isorxptr1 << 16) & ~((uint32_t)0xFFFF0000)) == 0);
    ASSERT_ERR((((uint32_t)isorxptr0 << 0) & ~((uint32_t)0x0000FFFF)) == 0);
    REG_BLE_WR(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE,  ((uint32_t)isorxptr1 << 16) | ((uint32_t)isorxptr0 << 0));
}

__INLINE void ble_isocurrentrxptr_unpack(int elt_idx, uint16_t* isorxptr1, uint16_t* isorxptr0)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);

    *isorxptr1 = (localVal & ((uint32_t)0xFFFF0000)) >> 16;
    *isorxptr0 = (localVal & ((uint32_t)0x0000FFFF)) >> 0;
}

__INLINE uint16_t ble_isorxptr1_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0xFFFF0000)) >> 16);
}

__INLINE void ble_isorxptr1_setf(int elt_idx, uint16_t isorxptr1)
{
    ASSERT_ERR((((uint32_t)isorxptr1 << 16) & ~((uint32_t)0xFFFF0000)) == 0);
    REG_BLE_WR(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0xFFFF0000)) | ((uint32_t)isorxptr1 << 16));
}

__INLINE uint16_t ble_isorxptr0_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x0000FFFF)) >> 0);
}

__INLINE void ble_isorxptr0_setf(int elt_idx, uint16_t isorxptr0)
{
    ASSERT_ERR((((uint32_t)isorxptr0 << 0) & ~((uint32_t)0x0000FFFF)) == 0);
    REG_BLE_WR(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOCURRENTRXPTR_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x0000FFFF)) | ((uint32_t)isorxptr0 << 0));
}

/**
 * @brief ISOTRCNTL register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  23:16             ISORXLEN   0x0
 *  07:00             ISOTXLEN   0x0
 * </pre>
 */
#define BLE_ISOTRCNTL_ADDR   0x20100160
#define BLE_ISOTRCNTL_OFFSET 0x00000160
#define BLE_ISOTRCNTL_INDEX  0x00000058
#define BLE_ISOTRCNTL_RESET  0x00000000

__INLINE uint32_t ble_isotrcntl_get(int elt_idx)
{
    return REG_BLE_RD(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
}

__INLINE void ble_isotrcntl_set(int elt_idx, uint32_t value)
{
    REG_BLE_WR(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, value);
}

// field definitions
#define BLE_ISORXLEN_MASK   ((uint32_t)0x00FF0000)
#define BLE_ISORXLEN_LSB    16
#define BLE_ISORXLEN_WIDTH  ((uint32_t)0x00000008)
#define BLE_ISOTXLEN_MASK   ((uint32_t)0x000000FF)
#define BLE_ISOTXLEN_LSB    0
#define BLE_ISOTXLEN_WIDTH  ((uint32_t)0x00000008)

#define BLE_ISORXLEN_RST    0x0
#define BLE_ISOTXLEN_RST    0x0

__INLINE void ble_isotrcntl_pack(int elt_idx, uint8_t isorxlen, uint8_t isotxlen)
{
    ASSERT_ERR((((uint32_t)isorxlen << 16) & ~((uint32_t)0x00FF0000)) == 0);
    ASSERT_ERR((((uint32_t)isotxlen << 0) & ~((uint32_t)0x000000FF)) == 0);
    REG_BLE_WR(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE,  ((uint32_t)isorxlen << 16) | ((uint32_t)isotxlen << 0));
}

__INLINE void ble_isotrcntl_unpack(int elt_idx, uint8_t* isorxlen, uint8_t* isotxlen)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);

    *isorxlen = (localVal & ((uint32_t)0x00FF0000)) >> 16;
    *isotxlen = (localVal & ((uint32_t)0x000000FF)) >> 0;
}

__INLINE uint8_t ble_isorxlen_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x00FF0000)) >> 16);
}

__INLINE void ble_isorxlen_setf(int elt_idx, uint8_t isorxlen)
{
    ASSERT_ERR((((uint32_t)isorxlen << 16) & ~((uint32_t)0x00FF0000)) == 0);
    REG_BLE_WR(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x00FF0000)) | ((uint32_t)isorxlen << 16));
}

__INLINE uint8_t ble_isotxlen_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    return ((localVal & ((uint32_t)0x000000FF)) >> 0);
}

__INLINE void ble_isotxlen_setf(int elt_idx, uint8_t isotxlen)
{
    ASSERT_ERR((((uint32_t)isotxlen << 0) & ~((uint32_t)0x000000FF)) == 0);
    REG_BLE_WR(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (REG_BLE_RD(BLE_ISOTRCNTL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE) & ~((uint32_t)0x000000FF)) | ((uint32_t)isotxlen << 0));
}

/**
 * @brief ISOEVTCNTOFFSETL register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  31:00      EVT_CNT_OFFSETL   0x0
 * </pre>
 */
#define BLE_ISOEVTCNTOFFSETL_ADDR   0x20100164
#define BLE_ISOEVTCNTOFFSETL_OFFSET 0x00000164
#define BLE_ISOEVTCNTOFFSETL_INDEX  0x00000059
#define BLE_ISOEVTCNTOFFSETL_RESET  0x00000000

__INLINE uint32_t ble_isoevtcntoffsetl_get(int elt_idx)
{
    return REG_BLE_RD(BLE_ISOEVTCNTOFFSETL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
}

__INLINE void ble_isoevtcntoffsetl_set(int elt_idx, uint32_t value)
{
    REG_BLE_WR(BLE_ISOEVTCNTOFFSETL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, value);
}

// field definitions
#define BLE_EVT_CNT_OFFSETL_MASK   ((uint32_t)0xFFFFFFFF)
#define BLE_EVT_CNT_OFFSETL_LSB    0
#define BLE_EVT_CNT_OFFSETL_WIDTH  ((uint32_t)0x00000020)

#define BLE_EVT_CNT_OFFSETL_RST    0x0

__INLINE uint32_t ble_evt_cnt_offsetl_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOEVTCNTOFFSETL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    ASSERT_ERR((localVal & ~((uint32_t)0xFFFFFFFF)) == 0);
    return (localVal >> 0);
}

__INLINE void ble_evt_cnt_offsetl_setf(int elt_idx, uint32_t evtcntoffsetl)
{
    ASSERT_ERR((((uint32_t)evtcntoffsetl << 0) & ~((uint32_t)0xFFFFFFFF)) == 0);
    REG_BLE_WR(BLE_ISOEVTCNTOFFSETL_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (uint32_t)evtcntoffsetl << 0);
}

/**
 * @brief ISOEVTCNTOFFSETU register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *  06:00      EVT_CNT_OFFSETU   0x0
 * </pre>
 */
#define BLE_ISOEVTCNTOFFSETU_ADDR   0x20100168
#define BLE_ISOEVTCNTOFFSETU_OFFSET 0x00000168
#define BLE_ISOEVTCNTOFFSETU_INDEX  0x0000005A
#define BLE_ISOEVTCNTOFFSETU_RESET  0x00000000

__INLINE uint32_t ble_isoevtcntoffsetu_get(int elt_idx)
{
    return REG_BLE_RD(BLE_ISOEVTCNTOFFSETU_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
}

__INLINE void ble_isoevtcntoffsetu_set(int elt_idx, uint32_t value)
{
    REG_BLE_WR(BLE_ISOEVTCNTOFFSETU_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, value);
}

// field definitions
#define BLE_EVT_CNT_OFFSETU_MASK   ((uint32_t)0x0000007F)
#define BLE_EVT_CNT_OFFSETU_LSB    0
#define BLE_EVT_CNT_OFFSETU_WIDTH  ((uint32_t)0x00000007)

#define BLE_EVT_CNT_OFFSETU_RST    0x0

__INLINE uint8_t ble_evt_cnt_offsetu_getf(int elt_idx)
{
    uint32_t localVal = REG_BLE_RD(BLE_ISOEVTCNTOFFSETU_ADDR + elt_idx * REG_BLECORE_ISO_SIZE);
    ASSERT_ERR((localVal & ~((uint32_t)0x0000007F)) == 0);
    return (localVal >> 0);
}

__INLINE void ble_evt_cnt_offsetu_setf(int elt_idx, uint8_t evtcntoffsetu)
{
    ASSERT_ERR((((uint32_t)evtcntoffsetu << 0) & ~((uint32_t)0x0000007F)) == 0);
    REG_BLE_WR(BLE_ISOEVTCNTOFFSETU_ADDR + elt_idx * REG_BLECORE_ISO_SIZE, (uint32_t)evtcntoffsetu << 0);
}


#endif // _REG_BLECORE_ISO_H_

