#include <stdint.h>
typedef struct sata_sataDevice {
    uint32_t bus;
    uint32_t device;
    uint32_t function;
    uint32_t mmio_region;
}sata_sataDevice;
typedef struct sata_pciSataDevices {
    sata_sataDevice drives[20];
    uint8_t count;
} sata_pciSataDevices;

sata_pciSataDevices sata_enumerate();