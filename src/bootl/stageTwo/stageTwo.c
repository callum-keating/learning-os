#include "drivers/vga.h"
#include "drivers/sata.h"
#include "drivers/pci.h"

// kernel.c
void stageTwo() {
    vga_clear();
    vga_print("Stage Two Loaded", 0, 0);
    pci_pciDevices devices = pci_enumerate();
    while(1);
}
