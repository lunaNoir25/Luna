// SPDX-License-Identifier: GPL-3.0+

#include "limine/include/limine.h" 
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
        for (;;) {
            __asm__("hlt");
        }
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    uint32_t *fb_ptr = framebuffer->address;
    for (size_t i = 0; i < 500; i++) {
        fb_ptr[i] = 0x0000FF;
    }

    for (;;) {
        __asm__("hlt");
    }
}