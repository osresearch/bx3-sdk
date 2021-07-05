/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include "fal_def.h"

#define FAL_PART_HAS_TABLE_CFG

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev rf01_flash;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &rf01_flash,                                                     \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                \
{                                                                                     \
    {FAL_PART_MAGIC_WORD,   "bl",   "rf01_onchip",  0,            12*1024,  0},  \
    {FAL_PART_MAGIC_WORD,   "app",  "rf01_onchip",  12*1024,      180*1024, 0},  \
    {FAL_PART_MAGIC_WORD,   "kvdb", "rf01_onchip",  192*1024,     64*1024,  0},  \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
