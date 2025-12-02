#include "drivers/vga.h"

void kernel_entry() {
    vga_clear();
    vga_print("Kernel Loaded");
    while(1);
}