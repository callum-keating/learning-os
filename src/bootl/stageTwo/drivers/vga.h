#pragma once
#include <stdint.h>
void vga_clear();
void vga_print(const char* str, int16_t x, uint8_t y);
int vga_addNewLine();
int vga_getLines();