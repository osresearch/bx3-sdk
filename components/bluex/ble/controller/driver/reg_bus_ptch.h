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
#ifndef __REG_BUS_PTCH_H__
#define __REG_BUS_PTCH_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_ble_reg.h"
/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap0 : 15; /*16: 2,       entry address of patch 0*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP0_ADDR;

//trap1_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap1 : 15; /*16: 2,       entry address of patch 1*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP1_ADDR;

//trap2_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap2 : 15; /*16: 2,       entry address of patch 2*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP2_ADDR;

//trap3_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap3 : 15; /*16: 2,       entry address of patch 3*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP3_ADDR;

//trap4_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap4 : 15; /*16: 2,       entry address of patch 4*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP4_ADDR;

//trap5_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap5 : 15; /*16: 2,       entry address of patch 5*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP5_ADDR;

//trap6_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap6 : 15; /*16: 2,       entry address of patch 6*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP6_ADDR;

//trap7_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap7 : 15; /*16: 2,       entry address of patch 7*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP7_ADDR;

//trap8_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap8 : 15; /*16: 2,       entry address of patch 8*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP8_ADDR;

//trap9_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trap9 : 15; /*16: 2,       entry address of patch 9*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP9_ADDR;

//trapa_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trapa : 15; /*16: 2,       entry address of patch a*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAPA_ADDR;

//trapb_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trapb : 15; /*16: 2,       entry address of patch b*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAPB_ADDR;

//trapc_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trapc : 15; /*16: 2,       entry address of patch c*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAPC_ADDR;

//trapd_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trapd : 15; /*16: 2,       entry address of patch d*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAPD_ADDR;

//trape_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trape : 15; /*16: 2,       entry address of patch e*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAPE_ADDR;

//trapf_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  2; /* 1: 0,                No description.*/
        uint32_t                          trapf : 15; /*16: 2,       entry address of patch f*/
        uint32_t                     reserved_0 : 15; /*31:17,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAPF_ADDR;

//out0_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out0 : 32; /*31: 0,        exit address of patch 0*/
    } bit_field;
} T_BUS_PTCH_OUT0_ADDR;

//out1_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out1 : 32; /*31: 0,        exit address of patch 1*/
    } bit_field;
} T_BUS_PTCH_OUT1_ADDR;

//out2_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out2 : 32; /*31: 0,        exit address of patch 2*/
    } bit_field;
} T_BUS_PTCH_OUT2_ADDR;

//out3_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out3 : 32; /*31: 0,        exit address of patch 3*/
    } bit_field;
} T_BUS_PTCH_OUT3_ADDR;

//out4_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out4 : 32; /*31: 0,        exit address of patch 4*/
    } bit_field;
} T_BUS_PTCH_OUT4_ADDR;

//out5_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out5 : 32; /*31: 0,        exit address of patch 5*/
    } bit_field;
} T_BUS_PTCH_OUT5_ADDR;

//out6_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out6 : 32; /*31: 0,        exit address of patch 6*/
    } bit_field;
} T_BUS_PTCH_OUT6_ADDR;

//out7_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out7 : 32; /*31: 0,        exit address of patch 7*/
    } bit_field;
} T_BUS_PTCH_OUT7_ADDR;

//out8_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out8 : 32; /*31: 0,        exit address of patch 8*/
    } bit_field;
} T_BUS_PTCH_OUT8_ADDR;

//out9_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           out9 : 32; /*31: 0,        exit address of patch 9*/
    } bit_field;
} T_BUS_PTCH_OUT9_ADDR;

//outa_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           outa : 32; /*31: 0,        exit address of patch a*/
    } bit_field;
} T_BUS_PTCH_OUTA_ADDR;

//outb_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           outb : 32; /*31: 0,        exit address of patch b*/
    } bit_field;
} T_BUS_PTCH_OUTB_ADDR;

//outc_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           outc : 32; /*31: 0,        exit address of patch c*/
    } bit_field;
} T_BUS_PTCH_OUTC_ADDR;

//outd_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           outd : 32; /*31: 0,        exit address of patch d*/
    } bit_field;
} T_BUS_PTCH_OUTD_ADDR;

//oute_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           oute : 32; /*31: 0,        exit address of patch e*/
    } bit_field;
} T_BUS_PTCH_OUTE_ADDR;

//outf_addr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                           outf : 32; /*31: 0,        exit address of patch f*/
    } bit_field;
} T_BUS_PTCH_OUTF_ADDR;

//trap_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      trap_en_r : 16; /*15: 0, per bit corresponding one trap.0--disable 1--enable*/
        uint32_t                     reserved_0 : 16; /*31:16,                No description.*/
    } bit_field;
} T_BUS_PTCH_TRAP_EN;

//Registers Mapping to the same address

typedef struct
{
    volatile           T_BUS_PTCH_TRAP0_ADDR                     trap0_addr; /*  0x0,    RW, 0x00000000,       trap0's entrance address*/
    volatile           T_BUS_PTCH_TRAP1_ADDR                     trap1_addr; /*  0x4,    RW, 0x00000000,       trap1's entrance address*/
    volatile           T_BUS_PTCH_TRAP2_ADDR                     trap2_addr; /*  0x8,    RW, 0x00000000,       trap2's entrance address*/
    volatile           T_BUS_PTCH_TRAP3_ADDR                     trap3_addr; /*  0xc,    RW, 0x00000000,       trap3's entrance address*/
    volatile           T_BUS_PTCH_TRAP4_ADDR                     trap4_addr; /* 0x10,    RW, 0x00000000,       trap'4s entrance address*/
    volatile           T_BUS_PTCH_TRAP5_ADDR                     trap5_addr; /* 0x14,    RW, 0x00000000,       trap5's entrance address*/
    volatile           T_BUS_PTCH_TRAP6_ADDR                     trap6_addr; /* 0x18,    RW, 0x00000000,       trap6's entrance address*/
    volatile           T_BUS_PTCH_TRAP7_ADDR                     trap7_addr; /* 0x1c,    RW, 0x00000000,       trap7's entrance address*/
    volatile           T_BUS_PTCH_TRAP8_ADDR                     trap8_addr; /* 0x20,    RW, 0x00000000,       trap8's entrance address*/
    volatile           T_BUS_PTCH_TRAP9_ADDR                     trap9_addr; /* 0x24,    RW, 0x00000000,       trap9's entrance address*/
    volatile           T_BUS_PTCH_TRAPA_ADDR                     trapa_addr; /* 0x28,    RW, 0x00000000,       trapa's entrance address*/
    volatile           T_BUS_PTCH_TRAPB_ADDR                     trapb_addr; /* 0x2c,    RW, 0x00000000,       trapb's entrance address*/
    volatile           T_BUS_PTCH_TRAPC_ADDR                     trapc_addr; /* 0x30,    RW, 0x00000000,       trapc's entrance address*/
    volatile           T_BUS_PTCH_TRAPD_ADDR                     trapd_addr; /* 0x34,    RW, 0x00000000,       trapd's entrance address*/
    volatile           T_BUS_PTCH_TRAPE_ADDR                     trape_addr; /* 0x38,    RW, 0x00000000,       trape's entrance address*/
    volatile           T_BUS_PTCH_TRAPF_ADDR                     trapf_addr; /* 0x3c,    RW, 0x00000000,       trapf's entrance address*/
    volatile            T_BUS_PTCH_OUT0_ADDR                      out0_addr; /* 0x40,    RW, 0x00000000,           trap0's exit address*/
    volatile            T_BUS_PTCH_OUT1_ADDR                      out1_addr; /* 0x44,    RW, 0x00000000,           trap1's exit address*/
    volatile            T_BUS_PTCH_OUT2_ADDR                      out2_addr; /* 0x48,    RW, 0x00000000,           trap2's exit address*/
    volatile            T_BUS_PTCH_OUT3_ADDR                      out3_addr; /* 0x4c,    RW, 0x00000000,           trap3's exit address*/
    volatile            T_BUS_PTCH_OUT4_ADDR                      out4_addr; /* 0x50,    RW, 0x00000000,           trap'4s exit address*/
    volatile            T_BUS_PTCH_OUT5_ADDR                      out5_addr; /* 0x54,    RW, 0x00000000,           trap5's exit address*/
    volatile            T_BUS_PTCH_OUT6_ADDR                      out6_addr; /* 0x58,    RW, 0x00000000,           trap6's exit address*/
    volatile            T_BUS_PTCH_OUT7_ADDR                      out7_addr; /* 0x5c,    RW, 0x00000000,           trap7's exit address*/
    volatile            T_BUS_PTCH_OUT8_ADDR                      out8_addr; /* 0x60,    RW, 0x00000000,           trap8's exit address*/
    volatile            T_BUS_PTCH_OUT9_ADDR                      out9_addr; /* 0x64,    RW, 0x00000000,           trap9's exit address*/
    volatile            T_BUS_PTCH_OUTA_ADDR                      outa_addr; /* 0x68,    RW, 0x00000000,           trapa's exit address*/
    volatile            T_BUS_PTCH_OUTB_ADDR                      outb_addr; /* 0x6c,    RW, 0x00000000,           trapb's exit address*/
    volatile            T_BUS_PTCH_OUTC_ADDR                      outc_addr; /* 0x70,    RW, 0x00000000,           trapc's exit address*/
    volatile            T_BUS_PTCH_OUTD_ADDR                      outd_addr; /* 0x74,    RW, 0x00000000,           trapd's exit address*/
    volatile            T_BUS_PTCH_OUTE_ADDR                      oute_addr; /* 0x78,    RW, 0x00000000,           trape's exit address*/
    volatile            T_BUS_PTCH_OUTF_ADDR                      outf_addr; /* 0x7c,    RW, 0x00000000,           trapf's exit address*/
    volatile              T_BUS_PTCH_TRAP_EN                        trap_en; /* 0x80,    RW, 0x00000000,             enable of 16 traps*/
} T_HWP_BUS_PTCH_T;

/* exported variables --------------------------------------------------------*/
#define hwp_bus_ptch ((T_HWP_BUS_PTCH_T*)REG_BUS_PTCH_BASE)

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap0_addr_get(void)
{
    return hwp_bus_ptch->trap0_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap0_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap0_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap0_addr_pack(uint16_t trap0)
{
    hwp_bus_ptch->trap0_addr.val = (((uint32_t)trap0 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap0_addr_unpack(uint16_t* trap0)
{
    T_BUS_PTCH_TRAP0_ADDR localVal = hwp_bus_ptch->trap0_addr;

    *trap0 = localVal.bit_field.trap0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap0_getf(void)
{
    return hwp_bus_ptch->trap0_addr.bit_field.trap0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap0_setf(uint16_t trap0)
{
    hwp_bus_ptch->trap0_addr.bit_field.trap0 = trap0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap1_addr_get(void)
{
    return hwp_bus_ptch->trap1_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap1_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap1_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap1_addr_pack(uint16_t trap1)
{
    hwp_bus_ptch->trap1_addr.val = (((uint32_t)trap1 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap1_addr_unpack(uint16_t* trap1)
{
    T_BUS_PTCH_TRAP1_ADDR localVal = hwp_bus_ptch->trap1_addr;

    *trap1 = localVal.bit_field.trap1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap1_getf(void)
{
    return hwp_bus_ptch->trap1_addr.bit_field.trap1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap1_setf(uint16_t trap1)
{
    hwp_bus_ptch->trap1_addr.bit_field.trap1 = trap1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap2_addr_get(void)
{
    return hwp_bus_ptch->trap2_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap2_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap2_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap2_addr_pack(uint16_t trap2)
{
    hwp_bus_ptch->trap2_addr.val = (((uint32_t)trap2 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap2_addr_unpack(uint16_t* trap2)
{
    T_BUS_PTCH_TRAP2_ADDR localVal = hwp_bus_ptch->trap2_addr;

    *trap2 = localVal.bit_field.trap2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap2_getf(void)
{
    return hwp_bus_ptch->trap2_addr.bit_field.trap2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap2_setf(uint16_t trap2)
{
    hwp_bus_ptch->trap2_addr.bit_field.trap2 = trap2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap3_addr_get(void)
{
    return hwp_bus_ptch->trap3_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap3_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap3_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap3_addr_pack(uint16_t trap3)
{
    hwp_bus_ptch->trap3_addr.val = (((uint32_t)trap3 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap3_addr_unpack(uint16_t* trap3)
{
    T_BUS_PTCH_TRAP3_ADDR localVal = hwp_bus_ptch->trap3_addr;

    *trap3 = localVal.bit_field.trap3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap3_getf(void)
{
    return hwp_bus_ptch->trap3_addr.bit_field.trap3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap3_setf(uint16_t trap3)
{
    hwp_bus_ptch->trap3_addr.bit_field.trap3 = trap3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap4_addr_get(void)
{
    return hwp_bus_ptch->trap4_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap4_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap4_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap4_addr_pack(uint16_t trap4)
{
    hwp_bus_ptch->trap4_addr.val = (((uint32_t)trap4 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap4_addr_unpack(uint16_t* trap4)
{
    T_BUS_PTCH_TRAP4_ADDR localVal = hwp_bus_ptch->trap4_addr;

    *trap4 = localVal.bit_field.trap4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap4_getf(void)
{
    return hwp_bus_ptch->trap4_addr.bit_field.trap4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap4_setf(uint16_t trap4)
{
    hwp_bus_ptch->trap4_addr.bit_field.trap4 = trap4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap5_addr_get(void)
{
    return hwp_bus_ptch->trap5_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap5_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap5_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap5_addr_pack(uint16_t trap5)
{
    hwp_bus_ptch->trap5_addr.val = (((uint32_t)trap5 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap5_addr_unpack(uint16_t* trap5)
{
    T_BUS_PTCH_TRAP5_ADDR localVal = hwp_bus_ptch->trap5_addr;

    *trap5 = localVal.bit_field.trap5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap5_getf(void)
{
    return hwp_bus_ptch->trap5_addr.bit_field.trap5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap5_setf(uint16_t trap5)
{
    hwp_bus_ptch->trap5_addr.bit_field.trap5 = trap5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap6_addr_get(void)
{
    return hwp_bus_ptch->trap6_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap6_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap6_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap6_addr_pack(uint16_t trap6)
{
    hwp_bus_ptch->trap6_addr.val = (((uint32_t)trap6 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap6_addr_unpack(uint16_t* trap6)
{
    T_BUS_PTCH_TRAP6_ADDR localVal = hwp_bus_ptch->trap6_addr;

    *trap6 = localVal.bit_field.trap6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap6_getf(void)
{
    return hwp_bus_ptch->trap6_addr.bit_field.trap6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap6_setf(uint16_t trap6)
{
    hwp_bus_ptch->trap6_addr.bit_field.trap6 = trap6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap7_addr_get(void)
{
    return hwp_bus_ptch->trap7_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap7_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap7_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap7_addr_pack(uint16_t trap7)
{
    hwp_bus_ptch->trap7_addr.val = (((uint32_t)trap7 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap7_addr_unpack(uint16_t* trap7)
{
    T_BUS_PTCH_TRAP7_ADDR localVal = hwp_bus_ptch->trap7_addr;

    *trap7 = localVal.bit_field.trap7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap7_getf(void)
{
    return hwp_bus_ptch->trap7_addr.bit_field.trap7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap7_setf(uint16_t trap7)
{
    hwp_bus_ptch->trap7_addr.bit_field.trap7 = trap7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap8_addr_get(void)
{
    return hwp_bus_ptch->trap8_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap8_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap8_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap8_addr_pack(uint16_t trap8)
{
    hwp_bus_ptch->trap8_addr.val = (((uint32_t)trap8 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap8_addr_unpack(uint16_t* trap8)
{
    T_BUS_PTCH_TRAP8_ADDR localVal = hwp_bus_ptch->trap8_addr;

    *trap8 = localVal.bit_field.trap8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap8_getf(void)
{
    return hwp_bus_ptch->trap8_addr.bit_field.trap8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap8_setf(uint16_t trap8)
{
    hwp_bus_ptch->trap8_addr.bit_field.trap8 = trap8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap9_addr_get(void)
{
    return hwp_bus_ptch->trap9_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap9_addr_set(uint32_t value)
{
    hwp_bus_ptch->trap9_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap9_addr_pack(uint16_t trap9)
{
    hwp_bus_ptch->trap9_addr.val = (((uint32_t)trap9 << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap9_addr_unpack(uint16_t* trap9)
{
    T_BUS_PTCH_TRAP9_ADDR localVal = hwp_bus_ptch->trap9_addr;

    *trap9 = localVal.bit_field.trap9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap9_getf(void)
{
    return hwp_bus_ptch->trap9_addr.bit_field.trap9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap9_setf(uint16_t trap9)
{
    hwp_bus_ptch->trap9_addr.bit_field.trap9 = trap9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trapa_addr_get(void)
{
    return hwp_bus_ptch->trapa_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapa_addr_set(uint32_t value)
{
    hwp_bus_ptch->trapa_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapa_addr_pack(uint16_t trapa)
{
    hwp_bus_ptch->trapa_addr.val = (((uint32_t)trapa << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapa_addr_unpack(uint16_t* trapa)
{
    T_BUS_PTCH_TRAPA_ADDR localVal = hwp_bus_ptch->trapa_addr;

    *trapa = localVal.bit_field.trapa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trapa_getf(void)
{
    return hwp_bus_ptch->trapa_addr.bit_field.trapa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapa_setf(uint16_t trapa)
{
    hwp_bus_ptch->trapa_addr.bit_field.trapa = trapa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trapb_addr_get(void)
{
    return hwp_bus_ptch->trapb_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapb_addr_set(uint32_t value)
{
    hwp_bus_ptch->trapb_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapb_addr_pack(uint16_t trapb)
{
    hwp_bus_ptch->trapb_addr.val = (((uint32_t)trapb << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapb_addr_unpack(uint16_t* trapb)
{
    T_BUS_PTCH_TRAPB_ADDR localVal = hwp_bus_ptch->trapb_addr;

    *trapb = localVal.bit_field.trapb;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trapb_getf(void)
{
    return hwp_bus_ptch->trapb_addr.bit_field.trapb;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapb_setf(uint16_t trapb)
{
    hwp_bus_ptch->trapb_addr.bit_field.trapb = trapb;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trapc_addr_get(void)
{
    return hwp_bus_ptch->trapc_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapc_addr_set(uint32_t value)
{
    hwp_bus_ptch->trapc_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapc_addr_pack(uint16_t trapc)
{
    hwp_bus_ptch->trapc_addr.val = (((uint32_t)trapc << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapc_addr_unpack(uint16_t* trapc)
{
    T_BUS_PTCH_TRAPC_ADDR localVal = hwp_bus_ptch->trapc_addr;

    *trapc = localVal.bit_field.trapc;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trapc_getf(void)
{
    return hwp_bus_ptch->trapc_addr.bit_field.trapc;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapc_setf(uint16_t trapc)
{
    hwp_bus_ptch->trapc_addr.bit_field.trapc = trapc;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trapd_addr_get(void)
{
    return hwp_bus_ptch->trapd_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapd_addr_set(uint32_t value)
{
    hwp_bus_ptch->trapd_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapd_addr_pack(uint16_t trapd)
{
    hwp_bus_ptch->trapd_addr.val = (((uint32_t)trapd << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapd_addr_unpack(uint16_t* trapd)
{
    T_BUS_PTCH_TRAPD_ADDR localVal = hwp_bus_ptch->trapd_addr;

    *trapd = localVal.bit_field.trapd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trapd_getf(void)
{
    return hwp_bus_ptch->trapd_addr.bit_field.trapd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapd_setf(uint16_t trapd)
{
    hwp_bus_ptch->trapd_addr.bit_field.trapd = trapd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trape_addr_get(void)
{
    return hwp_bus_ptch->trape_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trape_addr_set(uint32_t value)
{
    hwp_bus_ptch->trape_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trape_addr_pack(uint16_t trape)
{
    hwp_bus_ptch->trape_addr.val = (((uint32_t)trape << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trape_addr_unpack(uint16_t* trape)
{
    T_BUS_PTCH_TRAPE_ADDR localVal = hwp_bus_ptch->trape_addr;

    *trape = localVal.bit_field.trape;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trape_getf(void)
{
    return hwp_bus_ptch->trape_addr.bit_field.trape;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trape_setf(uint16_t trape)
{
    hwp_bus_ptch->trape_addr.bit_field.trape = trape;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trapf_addr_get(void)
{
    return hwp_bus_ptch->trapf_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapf_addr_set(uint32_t value)
{
    hwp_bus_ptch->trapf_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapf_addr_pack(uint16_t trapf)
{
    hwp_bus_ptch->trapf_addr.val = (((uint32_t)trapf << 2));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapf_addr_unpack(uint16_t* trapf)
{
    T_BUS_PTCH_TRAPF_ADDR localVal = hwp_bus_ptch->trapf_addr;

    *trapf = localVal.bit_field.trapf;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trapf_getf(void)
{
    return hwp_bus_ptch->trapf_addr.bit_field.trapf;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trapf_setf(uint16_t trapf)
{
    hwp_bus_ptch->trapf_addr.bit_field.trapf = trapf;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out0_addr_get(void)
{
    return hwp_bus_ptch->out0_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out0_addr_set(uint32_t value)
{
    hwp_bus_ptch->out0_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out0_addr_pack(uint32_t out0)
{
    hwp_bus_ptch->out0_addr.val = (((uint32_t)out0 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out0_addr_unpack(uint32_t* out0)
{
    T_BUS_PTCH_OUT0_ADDR localVal = hwp_bus_ptch->out0_addr;

    *out0 = localVal.bit_field.out0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out0_getf(void)
{
    return hwp_bus_ptch->out0_addr.bit_field.out0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out0_setf(uint32_t out0)
{
    hwp_bus_ptch->out0_addr.bit_field.out0 = out0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out1_addr_get(void)
{
    return hwp_bus_ptch->out1_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out1_addr_set(uint32_t value)
{
    hwp_bus_ptch->out1_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out1_addr_pack(uint32_t out1)
{
    hwp_bus_ptch->out1_addr.val = (((uint32_t)out1 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out1_addr_unpack(uint32_t* out1)
{
    T_BUS_PTCH_OUT1_ADDR localVal = hwp_bus_ptch->out1_addr;

    *out1 = localVal.bit_field.out1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out1_getf(void)
{
    return hwp_bus_ptch->out1_addr.bit_field.out1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out1_setf(uint32_t out1)
{
    hwp_bus_ptch->out1_addr.bit_field.out1 = out1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out2_addr_get(void)
{
    return hwp_bus_ptch->out2_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out2_addr_set(uint32_t value)
{
    hwp_bus_ptch->out2_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out2_addr_pack(uint32_t out2)
{
    hwp_bus_ptch->out2_addr.val = (((uint32_t)out2 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out2_addr_unpack(uint32_t* out2)
{
    T_BUS_PTCH_OUT2_ADDR localVal = hwp_bus_ptch->out2_addr;

    *out2 = localVal.bit_field.out2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out2_getf(void)
{
    return hwp_bus_ptch->out2_addr.bit_field.out2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out2_setf(uint32_t out2)
{
    hwp_bus_ptch->out2_addr.bit_field.out2 = out2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out3_addr_get(void)
{
    return hwp_bus_ptch->out3_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out3_addr_set(uint32_t value)
{
    hwp_bus_ptch->out3_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out3_addr_pack(uint32_t out3)
{
    hwp_bus_ptch->out3_addr.val = (((uint32_t)out3 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out3_addr_unpack(uint32_t* out3)
{
    T_BUS_PTCH_OUT3_ADDR localVal = hwp_bus_ptch->out3_addr;

    *out3 = localVal.bit_field.out3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out3_getf(void)
{
    return hwp_bus_ptch->out3_addr.bit_field.out3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out3_setf(uint32_t out3)
{
    hwp_bus_ptch->out3_addr.bit_field.out3 = out3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out4_addr_get(void)
{
    return hwp_bus_ptch->out4_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out4_addr_set(uint32_t value)
{
    hwp_bus_ptch->out4_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out4_addr_pack(uint32_t out4)
{
    hwp_bus_ptch->out4_addr.val = (((uint32_t)out4 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out4_addr_unpack(uint32_t* out4)
{
    T_BUS_PTCH_OUT4_ADDR localVal = hwp_bus_ptch->out4_addr;

    *out4 = localVal.bit_field.out4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out4_getf(void)
{
    return hwp_bus_ptch->out4_addr.bit_field.out4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out4_setf(uint32_t out4)
{
    hwp_bus_ptch->out4_addr.bit_field.out4 = out4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out5_addr_get(void)
{
    return hwp_bus_ptch->out5_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out5_addr_set(uint32_t value)
{
    hwp_bus_ptch->out5_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out5_addr_pack(uint32_t out5)
{
    hwp_bus_ptch->out5_addr.val = (((uint32_t)out5 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out5_addr_unpack(uint32_t* out5)
{
    T_BUS_PTCH_OUT5_ADDR localVal = hwp_bus_ptch->out5_addr;

    *out5 = localVal.bit_field.out5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out5_getf(void)
{
    return hwp_bus_ptch->out5_addr.bit_field.out5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out5_setf(uint32_t out5)
{
    hwp_bus_ptch->out5_addr.bit_field.out5 = out5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out6_addr_get(void)
{
    return hwp_bus_ptch->out6_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out6_addr_set(uint32_t value)
{
    hwp_bus_ptch->out6_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out6_addr_pack(uint32_t out6)
{
    hwp_bus_ptch->out6_addr.val = (((uint32_t)out6 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out6_addr_unpack(uint32_t* out6)
{
    T_BUS_PTCH_OUT6_ADDR localVal = hwp_bus_ptch->out6_addr;

    *out6 = localVal.bit_field.out6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out6_getf(void)
{
    return hwp_bus_ptch->out6_addr.bit_field.out6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out6_setf(uint32_t out6)
{
    hwp_bus_ptch->out6_addr.bit_field.out6 = out6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out7_addr_get(void)
{
    return hwp_bus_ptch->out7_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out7_addr_set(uint32_t value)
{
    hwp_bus_ptch->out7_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out7_addr_pack(uint32_t out7)
{
    hwp_bus_ptch->out7_addr.val = (((uint32_t)out7 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out7_addr_unpack(uint32_t* out7)
{
    T_BUS_PTCH_OUT7_ADDR localVal = hwp_bus_ptch->out7_addr;

    *out7 = localVal.bit_field.out7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out7_getf(void)
{
    return hwp_bus_ptch->out7_addr.bit_field.out7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out7_setf(uint32_t out7)
{
    hwp_bus_ptch->out7_addr.bit_field.out7 = out7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out8_addr_get(void)
{
    return hwp_bus_ptch->out8_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out8_addr_set(uint32_t value)
{
    hwp_bus_ptch->out8_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out8_addr_pack(uint32_t out8)
{
    hwp_bus_ptch->out8_addr.val = (((uint32_t)out8 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out8_addr_unpack(uint32_t* out8)
{
    T_BUS_PTCH_OUT8_ADDR localVal = hwp_bus_ptch->out8_addr;

    *out8 = localVal.bit_field.out8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out8_getf(void)
{
    return hwp_bus_ptch->out8_addr.bit_field.out8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out8_setf(uint32_t out8)
{
    hwp_bus_ptch->out8_addr.bit_field.out8 = out8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out9_addr_get(void)
{
    return hwp_bus_ptch->out9_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out9_addr_set(uint32_t value)
{
    hwp_bus_ptch->out9_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out9_addr_pack(uint32_t out9)
{
    hwp_bus_ptch->out9_addr.val = (((uint32_t)out9 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out9_addr_unpack(uint32_t* out9)
{
    T_BUS_PTCH_OUT9_ADDR localVal = hwp_bus_ptch->out9_addr;

    *out9 = localVal.bit_field.out9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_out9_getf(void)
{
    return hwp_bus_ptch->out9_addr.bit_field.out9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_out9_setf(uint32_t out9)
{
    hwp_bus_ptch->out9_addr.bit_field.out9 = out9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outa_addr_get(void)
{
    return hwp_bus_ptch->outa_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outa_addr_set(uint32_t value)
{
    hwp_bus_ptch->outa_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outa_addr_pack(uint32_t outa)
{
    hwp_bus_ptch->outa_addr.val = (((uint32_t)outa << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outa_addr_unpack(uint32_t* outa)
{
    T_BUS_PTCH_OUTA_ADDR localVal = hwp_bus_ptch->outa_addr;

    *outa = localVal.bit_field.outa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outa_getf(void)
{
    return hwp_bus_ptch->outa_addr.bit_field.outa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outa_setf(uint32_t outa)
{
    hwp_bus_ptch->outa_addr.bit_field.outa = outa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outb_addr_get(void)
{
    return hwp_bus_ptch->outb_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outb_addr_set(uint32_t value)
{
    hwp_bus_ptch->outb_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outb_addr_pack(uint32_t outb)
{
    hwp_bus_ptch->outb_addr.val = (((uint32_t)outb << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outb_addr_unpack(uint32_t* outb)
{
    T_BUS_PTCH_OUTB_ADDR localVal = hwp_bus_ptch->outb_addr;

    *outb = localVal.bit_field.outb;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outb_getf(void)
{
    return hwp_bus_ptch->outb_addr.bit_field.outb;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outb_setf(uint32_t outb)
{
    hwp_bus_ptch->outb_addr.bit_field.outb = outb;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outc_addr_get(void)
{
    return hwp_bus_ptch->outc_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outc_addr_set(uint32_t value)
{
    hwp_bus_ptch->outc_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outc_addr_pack(uint32_t outc)
{
    hwp_bus_ptch->outc_addr.val = (((uint32_t)outc << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outc_addr_unpack(uint32_t* outc)
{
    T_BUS_PTCH_OUTC_ADDR localVal = hwp_bus_ptch->outc_addr;

    *outc = localVal.bit_field.outc;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outc_getf(void)
{
    return hwp_bus_ptch->outc_addr.bit_field.outc;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outc_setf(uint32_t outc)
{
    hwp_bus_ptch->outc_addr.bit_field.outc = outc;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outd_addr_get(void)
{
    return hwp_bus_ptch->outd_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outd_addr_set(uint32_t value)
{
    hwp_bus_ptch->outd_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outd_addr_pack(uint32_t outd)
{
    hwp_bus_ptch->outd_addr.val = (((uint32_t)outd << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outd_addr_unpack(uint32_t* outd)
{
    T_BUS_PTCH_OUTD_ADDR localVal = hwp_bus_ptch->outd_addr;

    *outd = localVal.bit_field.outd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outd_getf(void)
{
    return hwp_bus_ptch->outd_addr.bit_field.outd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outd_setf(uint32_t outd)
{
    hwp_bus_ptch->outd_addr.bit_field.outd = outd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_oute_addr_get(void)
{
    return hwp_bus_ptch->oute_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_oute_addr_set(uint32_t value)
{
    hwp_bus_ptch->oute_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_oute_addr_pack(uint32_t oute)
{
    hwp_bus_ptch->oute_addr.val = (((uint32_t)oute << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_oute_addr_unpack(uint32_t* oute)
{
    T_BUS_PTCH_OUTE_ADDR localVal = hwp_bus_ptch->oute_addr;

    *oute = localVal.bit_field.oute;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_oute_getf(void)
{
    return hwp_bus_ptch->oute_addr.bit_field.oute;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_oute_setf(uint32_t oute)
{
    hwp_bus_ptch->oute_addr.bit_field.oute = oute;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outf_addr_get(void)
{
    return hwp_bus_ptch->outf_addr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outf_addr_set(uint32_t value)
{
    hwp_bus_ptch->outf_addr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outf_addr_pack(uint32_t outf)
{
    hwp_bus_ptch->outf_addr.val = (((uint32_t)outf << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outf_addr_unpack(uint32_t* outf)
{
    T_BUS_PTCH_OUTF_ADDR localVal = hwp_bus_ptch->outf_addr;

    *outf = localVal.bit_field.outf;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_outf_getf(void)
{
    return hwp_bus_ptch->outf_addr.bit_field.outf;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_outf_setf(uint32_t outf)
{
    hwp_bus_ptch->outf_addr.bit_field.outf = outf;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t bus_ptch_trap_en_get(void)
{
    return hwp_bus_ptch->trap_en.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap_en_set(uint32_t value)
{
    hwp_bus_ptch->trap_en.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap_en_pack(uint16_t trap_en_r)
{
    hwp_bus_ptch->trap_en.val = (((uint32_t)trap_en_r << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap_en_unpack(uint16_t* trap_en_r)
{
    T_BUS_PTCH_TRAP_EN localVal = hwp_bus_ptch->trap_en;

    *trap_en_r = localVal.bit_field.trap_en_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t bus_ptch_trap_en_r_getf(void)
{
    return hwp_bus_ptch->trap_en.bit_field.trap_en_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void bus_ptch_trap_en_r_setf(uint16_t trap_en_r)
{
    hwp_bus_ptch->trap_en.bit_field.trap_en_r = trap_en_r;
}


#ifdef __cplusplus
}
#endif

#endif /* __REG_BUS_PTCH_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
