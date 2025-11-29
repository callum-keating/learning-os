#include "sata.h"
#include <stdint.h>

uint32_t inl(uint16_t port) {
    uint32_t data;
    __asm__ volatile("inl %1, %0" : "=a"(data) : "dN"(port));
    return data;
}
void outl(uint16_t port, uint32_t data) {
    __asm__ volatile ("outl %0, %1" : : "a"(data), "Nd"(port));
}

uint32_t getData(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset) {
    uint32_t addr = 
        (1U << 31)               |
        ((uint32_t)bus << 16)    |
        ((uint32_t)device << 11) |
        ((uint32_t)function << 8)|
        (offset & 0xFC);                      // 0 is the offset 0x10 is bar0 0x24 is bar5 (mmio address;)
    outl(0xCF8, addr);
    uint32_t data = inl(0xCFC);
    return data;
}

sata_pciSataDevices sata_enumerate() {
    uint32_t deviceCount = 0;
    sata_pciSataDevices devices;
    for (int bus = 0; bus < 256; bus++) {
        for (int device = 0; device < 32; device++) {
            for (int function = 0; function < 8; function++) {
                uint32_t data = getData(bus, device, function, 0);  // 0 is the offset 0x10 is bar0 0x24 is bar5 (mmio address;)

                uint16_t vendor = data & 0xFFFF;
                if (vendor == 0xFFFF) continue;                      // There is no device

                uint32_t classData = getData(bus,device,function, 0x08);
                uint8_t classCode = (classData >> 24) & 0xFF;
                uint8_t subclass  = (classData >> 16) & 0xFF;
                uint8_t progIF    = (classData >> 8)  & 0xFF;
                if (classCode == 0x01 && subclass == 0x06 && progIF == 0x01) {
                    // SATA AHCI controller found!
                    
                    // Read BAR5 for AHCI MMIO
                    uint32_t bar5 = getData(bus, device,function, 0x24);

                    uint32_t hba_mmio_base = bar5 & 0xFFFFFFF0;

                    // Store or print the MMIO base
                    // Example: log("AHCI found at BAR5 = %x", hba_mmio_base);
                    devices.drives[deviceCount].bus = bus;
                    devices.drives[deviceCount].device = device;
                    devices.drives[deviceCount].function = function;
                    devices.drives[deviceCount].mmio_region = hba_mmio_base;
                    deviceCount +=1;
                }
            }
        }
    }
    devices.count = deviceCount;
    return devices;
}


uint32_t sata_read(uint64_t lba, uint32_t memlocation, uint32_t sectorCount, sata_sataDevice device) {

}