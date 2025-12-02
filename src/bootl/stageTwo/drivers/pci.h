#pragma once
#include <stdint.h>

typedef struct pci_pciDevice {
    uint32_t bus;
    uint32_t device;
    uint8_t function;
    uint8_t classID;
    uint8_t subClass;
    uint8_t progIf;
} pci_pciDevice;

typedef struct pci_pciDevices {
    pci_pciDevice Devices[256];
} pci_pciDevices;

pci_pciDevices pci_enumerate();
