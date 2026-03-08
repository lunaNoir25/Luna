// SPDX-License-Identifier: GPL-3.0+

#ifndef PSF_H
#define PSF_H

#include <stdint.h>

#define PSF1_FONT_MAGIC 0x0436

#define PSF1_MODE512 0x01
#define PSF1_HAS_UNICODE_TABLE 0x02

typedef struct {
    uint16_t magic;
    uint8_t mode;
    uint8_t charsize;
} __attribute__((packed)) psf1_header_t;

extern char _binary_bin_spleen_8x16_psfu_start[];

#endif