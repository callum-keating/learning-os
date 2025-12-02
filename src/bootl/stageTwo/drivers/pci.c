#include "pci.h"
#include <stdint.h>

uint32_t inl(uint16_t port) {
    uint32_t result = 0;
    __asm__ volatile("inl %1, %0" : "=a"(result) : "d"(port));
    return result;
}

void outl(uint16_t port, uint32_t value) {
    __asm__ volatile("outl %0, %1" : : "a"(value), "d"(port));
}

pci_pciDevice gatherDeviceInfo(uint32_t bus, uint32_t device) {
    pci_pciDevice deviceStruct = {0};
    deviceStruct.bus = bus;
    deviceStruct.device = device;
    deviceStruct.function = 0;

    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)device;
    uint32_t lfunc = (uint32_t)0;
    uint16_t tmp = 0;
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
                  (lfunc << 8) | (0x08 & 0xFC) | ((uint32_t)0x80000000));
    // Get class ID and subclass ID
    outl(0xCF8, address);
    uint32_t value = inl(0xCFC);                    // VALUE STRUCTURE: [bits 0-7] Prog If [bits 8-15] Subclass [bits 16-23] Class ID
    uint8_t progIf = value & 0xFF;
    uint8_t subClass = (value >> 8) & 0xFF;
    uint8_t classID = (value >> 16) & 0xFF;
    deviceStruct.progIf = progIf;
    deviceStruct.subClass = subClass;
    deviceStruct.classID = classID;
    return deviceStruct;
}

pci_pciDevices pci_enumerate() {
    pci_pciDevices devices = {0};
    uint8_t count = 0;
    for (int bus = 0; bus < 256; bus++) {
        for (int device = 0; device < 32; device++) {
            pci_pciDevice pciDevice = gatherDeviceInfo(bus, device);
            if (pciDevice.classID == 0x01 && pciDevice.subClass == 0x06 && pciDevice.progIf == 0x01) {  // Found AHCI SATA controller
                devices.Devices[count] = pciDevice;
                count++;
                if (count == 255) {
                    return devices;
                }
            }
        }
    }
    return devices;
}
