#include "vga.h"

void vga_clear() {
    volatile unsigned short *video = (unsigned short *)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        video[i] = 0x07 << 8 | ' ';  // attribute << 8 | char
    }
}

void vga_print(const char* str, int16_t x, uint8_t y) {
    volatile unsigned short *video = (unsigned short *)0xB8000;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            y++;
            x= 0 - i - 1;
            continue;
        }
        video[y*80 + x + i] = (0x07 << 8) | str[i];  // attribute << 8 | char
    }
}
