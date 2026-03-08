// SPDX-License-Identifier: GPL-3.0+

#include "limine/include/limine.h"
#include "drivers/video/video.h"
#include "drivers/video/psf.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

void _start(void) {
    if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) {
        goto halt;
    }

    struct limine_framebuffer *fb =
        framebuffer_request.response->framebuffers[0];

    psf1_header_t *font =
        (psf1_header_t *)_binary_bin_spleen_8x16_psfu_start;

    video_init(fb, font);

    clear(0x000000);

    put_char('W', 0xFFFFFF);
    put_char('e', 0xFFFFFF);
    put_char('l', 0xFFFFFF);
    put_char('c', 0xFFFFFF);
    put_char('o', 0xFFFFFF);
    put_char('m', 0xFFFFFF);
    put_char('e', 0xFFFFFF);
    put_char(' ', 0xFFFFFF);
    put_char('t', 0xFFFFFF);
    put_char('o', 0xFFFFFF);
    put_char(' ', 0xFFFFFF);
    put_char('L', 0xAA00AA);
    put_char('u', 0xAA00AA);
    put_char('n', 0xAA00AA);
    put_char('a', 0xAA00AA);
    put_char('!', 0xAA00AA);

halt:
    for (;;) {
        __asm__("hlt");
    }
}