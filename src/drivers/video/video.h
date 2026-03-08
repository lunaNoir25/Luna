// SPDX-License-Identifier: GPL-3.0+

#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include <stddef.h>
#include "psf.h"
#include "../../limine/include/limine.h"

void video_init(struct limine_framebuffer *fb, psf1_header_t *font);
void put_char(char c, uint32_t color);
void clear(uint32_t color);

#endif