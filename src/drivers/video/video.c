// SPDX-License-Identifier: GPL-3.0+

#include "video.h"
#include "psf.h"

static struct limine_framebuffer *ctx_fb;
static psf1_header_t *ctx_font;
static uint32_t cursor_x;
static uint32_t cursor_y;

void video_init(struct limine_framebuffer *fb, psf1_header_t *font) {
    ctx_fb = fb;
    ctx_font = font;

    set_cursor(0, 0);
}

void clear(uint32_t color) {
    if (!ctx_fb) return;

    uint32_t *fb_ptr = (uint32_t *)ctx_fb->address;
    size_t stride = ctx_fb->pitch / 4;

    for (size_t y = 0; y < ctx_fb->height; y++) {
        for (size_t x = 0; x < ctx_fb->width; x++) {
            fb_ptr[y * stride + x] = color;
        }
    }

    set_cursor(0, 0);
}

void set_cursor(uint32_t x, uint32_t y) {
    cursor_x = x;
    cursor_y = y;
}

void put_char(char c, uint32_t color) {
    if (!ctx_fb || !ctx_font) return;

    if (c == '\n') {
        set_cursor(cursor_x, cursor_y += ctx_font->charsize);
        return;
    }

    if (cursor_x + 8 > ctx_fb->width) {
        set_cursor(cursor_x, cursor_y += ctx_font->charsize);
    }

    uint8_t *font_ptr = (uint8_t *)_binary_bin_spleen_8x16_psfu_start;
    uint8_t *glyph = font_ptr + sizeof(psf1_header_t) + (uint8_t)c * ctx_font->charsize;

    uint32_t *fb_ptr = (uint32_t *)ctx_fb->address;
    uint32_t stride = ctx_fb->pitch / 4;

    for (uint32_t y = 0; y < ctx_font->charsize; y++) {
        for (uint32_t x = 0; x < 8; x++) {
            if (glyph[y] & (0x80 >> x)) {
                fb_ptr[(cursor_y + y) * stride + (cursor_x + x)] = color;
            }
        }
    }

    set_cursor(cursor_x += 8, cursor_y);
}