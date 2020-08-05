#ifndef _REG_BLE_EM_ET_H_
#define _REG_BLE_EM_ET_H_

#include <stdint.h>
#include "_reg_ble_em_et.h"
#include "compiler.h"
#include "arch.h"
#include "em_map.h"
#include "reg_access.h"

#define REG_BLE_EM_ET_COUNT 2

#define REG_BLE_EM_ET_DECODING_MASK 0x00000003

#define REG_BLE_EM_ET_ADDR_GET(idx) (EM_BLE_ET_OFFSET + (idx) * REG_BLE_EM_ET_SIZE)

/**
 * @brief EXTAB0 register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     10                 RSVD   0
 *  09:08              ISOCHAN   0x0
 *     07                  ISO   0
 *     06            ISOBUFSEL   0
 *  05:04               STATUS   0x0
 *  03:00                 MODE   0x0
 * </pre>
 */
#define BLE_EXTAB0_ADDR   (0x00128000 + EM_BLE_ET_OFFSET)
#define BLE_EXTAB0_INDEX  0x00000000
#define BLE_EXTAB0_RESET  0x00000000

__INLINE uint16_t ble_extab0_get(int elt_idx)
{
    return EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
}

__INLINE void ble_extab0_set(int elt_idx, uint16_t value)
{
    EM_BLE_WR(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, value);
}

// field definitions
#define BLE_RSVD_BIT         ((uint16_t)0x00000400)
#define BLE_RSVD_POS         10
#define BLE_ISOCHAN_MASK     ((uint16_t)0x00000300)
#define BLE_ISOCHAN_LSB      8
#define BLE_ISOCHAN_WIDTH    ((uint16_t)0x00000002)
#define BLE_ISO_BIT          ((uint16_t)0x00000080)
#define BLE_ISO_POS          7
#define BLE_ISOBUFSEL_BIT    ((uint16_t)0x00000040)
#define BLE_ISOBUFSEL_POS    6
#define BLE_STATUS_MASK      ((uint16_t)0x00000030)
#define BLE_STATUS_LSB       4
#define BLE_STATUS_WIDTH     ((uint16_t)0x00000002)
#define BLE_MODE_MASK        ((uint16_t)0x0000000F)
#define BLE_MODE_LSB         0
#define BLE_MODE_WIDTH       ((uint16_t)0x00000004)

#define BLE_RSVD_RST         0x0
#define BLE_ISOCHAN_RST      0x0
#define BLE_ISO_RST          0x0
#define BLE_ISOBUFSEL_RST    0x0
#define BLE_STATUS_RST       0x0
#define BLE_MODE_RST         0x0

__INLINE void ble_extab0_pack(int elt_idx, uint8_t rsvd, uint8_t isochan, uint8_t iso, uint8_t isobufsel, uint8_t status, uint8_t mode)
{
    ASSERT_ERR((((uint16_t)rsvd << 10) & ~((uint16_t)0x00000400)) == 0);
    ASSERT_ERR((((uint16_t)isochan << 8) & ~((uint16_t)0x00000300)) == 0);
    ASSERT_ERR((((uint16_t)iso << 7) & ~((uint16_t)0x00000080)) == 0);
    ASSERT_ERR((((uint16_t)isobufsel << 6) & ~((uint16_t)0x00000040)) == 0);
    ASSERT_ERR((((uint16_t)status << 4) & ~((uint16_t)0x00000030)) == 0);
    ASSERT_ERR((((uint16_t)mode << 0) & ~((uint16_t)0x0000000F)) == 0);
    EM_BLE_WR(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE,  ((uint16_t)rsvd << 10) | ((uint16_t)isochan << 8) | ((uint16_t)iso << 7) | ((uint16_t)isobufsel << 6) | ((uint16_t)status << 4) | ((uint16_t)mode << 0));
}

__INLINE void ble_extab0_unpack(int elt_idx, uint8_t* rsvd, uint8_t* isochan, uint8_t* iso, uint8_t* isobufsel, uint8_t* status, uint8_t* mode)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);

    *rsvd = (localVal & ((uint16_t)0x00000400)) >> 10;
    *isochan = (localVal & ((uint16_t)0x00000300)) >> 8;
    *iso = (localVal & ((uint16_t)0x00000080)) >> 7;
    *isobufsel = (localVal & ((uint16_t)0x00000040)) >> 6;
    *status = (localVal & ((uint16_t)0x00000030)) >> 4;
    *mode = (localVal & ((uint16_t)0x0000000F)) >> 0;
}

__INLINE uint8_t ble_extab0_rsvd_getf(int elt_idx)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
    return ((localVal & ((uint16_t)0x00000400)) >> 10);
}

__INLINE void ble_extab0_rsvd_setf(int elt_idx, uint8_t rsvd)
{
    ASSERT_ERR((((uint16_t)rsvd << 10) & ~((uint16_t)0x00000400)) == 0);
    EM_BLE_WR(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, (EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE) & ~((uint16_t)0x00000400)) | ((uint16_t)rsvd << 10));
}

__INLINE uint8_t ble_extab0_isochan_getf(int elt_idx)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
    return ((localVal & ((uint16_t)0x00000300)) >> 8);
}

__INLINE void ble_extab0_isochan_setf(int elt_idx, uint8_t isochan)
{
    ASSERT_ERR((((uint16_t)isochan << 8) & ~((uint16_t)0x00000300)) == 0);
    EM_BLE_WR(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, (EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE) & ~((uint16_t)0x00000300)) | ((uint16_t)isochan << 8));
}

__INLINE uint8_t ble_extab0_iso_getf(int elt_idx)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
    return ((localVal & ((uint16_t)0x00000080)) >> 7);
}

__INLINE void ble_extab0_iso_setf(int elt_idx, uint8_t iso)
{
    ASSERT_ERR((((uint16_t)iso << 7) & ~((uint16_t)0x00000080)) == 0);
    EM_BLE_WR(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, (EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE) & ~((uint16_t)0x00000080)) | ((uint16_t)iso << 7));
}

__INLINE uint8_t ble_extab0_isobufsel_getf(int elt_idx)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
    return ((localVal & ((uint16_t)0x00000040)) >> 6);
}

__INLINE void ble_extab0_isobufsel_setf(int elt_idx, uint8_t isobufsel)
{
    ASSERT_ERR((((uint16_t)isobufsel << 6) & ~((uint16_t)0x00000040)) == 0);
    EM_BLE_WR(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, (EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE) & ~((uint16_t)0x00000040)) | ((uint16_t)isobufsel << 6));
}

__INLINE uint8_t ble_extab0_status_getf(int elt_idx)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
    return ((localVal & ((uint16_t)0x00000030)) >> 4);
}

__INLINE void ble_extab0_status_setf(int elt_idx, uint8_t status)
{
    ASSERT_ERR((((uint16_t)status << 4) & ~((uint16_t)0x00000030)) == 0);
    EM_BLE_WR(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, (EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE) & ~((uint16_t)0x00000030)) | ((uint16_t)status << 4));
}

__INLINE uint8_t ble_extab0_mode_getf(int elt_idx)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
    return ((localVal & ((uint16_t)0x0000000F)) >> 0);
}

__INLINE void ble_extab0_mode_setf(int elt_idx, uint8_t mode)
{
    ASSERT_ERR((((uint16_t)mode << 0) & ~((uint16_t)0x0000000F)) == 0);
    EM_BLE_WR(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, (EM_BLE_RD(BLE_EXTAB0_ADDR + elt_idx * REG_BLE_EM_ET_SIZE) & ~((uint16_t)0x0000000F)) | ((uint16_t)mode << 0));
}

/**
 * @brief EXTAB1 register definition
 * <pre>
 *   Bits           Field Name   Reset Value
 *  -----   ------------------   -----------
 *     15           EXCPTRNRDY   0
 *  14:00                CSPTR   0x0
 * </pre>
 */
#define BLE_EXTAB1_ADDR   (0x00128002 + EM_BLE_ET_OFFSET)
#define BLE_EXTAB1_INDEX  0x00000001
#define BLE_EXTAB1_RESET  0x00000000

__INLINE uint16_t ble_extab1_get(int elt_idx)
{
    return EM_BLE_RD(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
}

__INLINE void ble_extab1_set(int elt_idx, uint16_t value)
{
    EM_BLE_WR(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, value);
}

// field definitions
#define BLE_EXCPTRNRDY_BIT    ((uint16_t)0x00008000)
#define BLE_EXCPTRNRDY_POS    15
#define BLE_CSPTR_MASK        ((uint16_t)0x00007FFF)
#define BLE_CSPTR_LSB         0
#define BLE_CSPTR_WIDTH       ((uint16_t)0x0000000F)

#define BLE_EXCPTRNRDY_RST    0x0
#define BLE_CSPTR_RST         0x0

__INLINE void ble_extab1_pack(int elt_idx, uint8_t excptrnrdy, uint16_t csptr)
{
    ASSERT_ERR((((uint16_t)excptrnrdy << 15) & ~((uint16_t)0x00008000)) == 0);
    ASSERT_ERR((((uint16_t)csptr << 0) & ~((uint16_t)0x00007FFF)) == 0);
    EM_BLE_WR(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE,  ((uint16_t)excptrnrdy << 15) | ((uint16_t)csptr << 0));
}

__INLINE void ble_extab1_unpack(int elt_idx, uint8_t* excptrnrdy, uint16_t* csptr)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);

    *excptrnrdy = (localVal & ((uint16_t)0x00008000)) >> 15;
    *csptr = (localVal & ((uint16_t)0x00007FFF)) >> 0;
}

__INLINE uint8_t ble_extab1_excptrnrdy_getf(int elt_idx)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
    return ((localVal & ((uint16_t)0x00008000)) >> 15);
}

__INLINE void ble_extab1_excptrnrdy_setf(int elt_idx, uint8_t excptrnrdy)
{
    ASSERT_ERR((((uint16_t)excptrnrdy << 15) & ~((uint16_t)0x00008000)) == 0);
    EM_BLE_WR(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, (EM_BLE_RD(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE) & ~((uint16_t)0x00008000)) | ((uint16_t)excptrnrdy << 15));
}

__INLINE uint16_t ble_extab1_csptr_getf(int elt_idx)
{
    uint16_t localVal = EM_BLE_RD(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE);
    return ((localVal & ((uint16_t)0x00007FFF)) >> 0);
}

__INLINE void ble_extab1_csptr_setf(int elt_idx, uint16_t csptr)
{
    ASSERT_ERR((((uint16_t)csptr << 0) & ~((uint16_t)0x00007FFF)) == 0);
    EM_BLE_WR(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE, (EM_BLE_RD(BLE_EXTAB1_ADDR + elt_idx * REG_BLE_EM_ET_SIZE) & ~((uint16_t)0x00007FFF)) | ((uint16_t)csptr << 0));
}


#endif // _REG_BLE_EM_ET_H_

