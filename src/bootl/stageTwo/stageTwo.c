#include "drivers/vga.h"
#include "drivers/sata.h"

// kernel.c
void stageTwo() {
    vga_clear();
    vga_print("Stage Two Loaded", 0, 0);
    sata_pciSataDevices sataDevices = sata_enumerate();
    if (sataDevices.count > 0) {
        vga_print("Found atleast 1 sata device!", 0, 1);
    }
    while(1);
}
