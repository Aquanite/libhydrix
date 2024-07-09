#include <libhydrix/hlow/pci/pci.h>
#include <libhydrix/hio/io.h>
#include <libhydrix/hmem/smem/heap.h>
pci_device **pci_devices = 0;
uint32_t devs = 0;

pci_driver **pci_drivers = 0;
uint32_t drivs = 0;
Console *con_pci;

void Set_Console_PCI(Console *con)
{
    con_pci = con;
}

void add_pci_device(pci_device *pdev)
{
	pci_devices[devs] = pdev;
	devs ++;
	return;
}

uint16_t pci_read_word(uint16_t bus, uint16_t slot, uint16_t func, uint16_t offset)
{
	uint64_t address;
    uint64_t lbus = (uint64_t)bus;
    uint64_t lslot = (uint64_t)slot;
    uint64_t lfunc = (uint64_t)func;
    uint16_t tmp = 0;
    address = (uint64_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
    outl(0xCF8, address);
    tmp = (uint16_t)((inl (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
}

uint16_t getVendorID(uint16_t bus, uint16_t device, uint16_t function)
{
        uint32_t r0 = pci_read_word(bus,device,function,0);
        return r0;
}

uint16_t getDeviceID(uint16_t bus, uint16_t device, uint16_t function)
{
        uint32_t r0 = pci_read_word(bus,device,function,2);
        return r0;
}

uint16_t getClassId(uint16_t bus, uint16_t device, uint16_t function)
{
        uint32_t r0 = pci_read_word(bus,device,function,0xA);
        return (r0 & ~0x00FF) >> 8;
}

uint16_t getSubClassId(uint16_t bus, uint16_t device, uint16_t function)
{
        uint32_t r0 = pci_read_word(bus,device,function,0xA);
        return (r0 & ~0xFF00);
}

void pci_probe()
{
	for(uint32_t bus = 0; bus < 256; bus++)
    {
        for(uint32_t slot = 0; slot < 32; slot++)
        {
            for(uint32_t function = 0; function < 8; function++)
            {
                    uint16_t vendor = getVendorID(bus, slot, function);
                    if(vendor == 0xffff) continue;
                    uint16_t device = getDeviceID(bus, slot, function);
                    con_pci->WriteLineS(strcat(strcat("vendor: 0x", to_string_hex(vendor)),strcat(" device: 0x", to_string_hex(device))));
                    pci_device *pdev = (pci_device *)kalloc(sizeof(pci_device));
                    pdev->vendor = vendor;
                    pdev->device = device;
                    pdev->func = function;
                    pdev->driver = 0;
                    add_pci_device(pdev);
            }
        }
    }
}

 uint16_t pciCheckVendor(uint16_t bus, uint16_t slot)
 {
    uint16_t vendor,device;
        /* check if device is valid */
    if ((vendor = pci_read_word(bus,slot,0,0)) != 0xFFFF) {
       device = pci_read_word(bus,slot,0,2);
       /* valid device */
    } return (vendor);
 }


void pci_init()
{
	devs = drivs = 0;
	pci_devices = (pci_device **)kalloc(32 * sizeof(pci_device));
	pci_drivers = (pci_driver **)kalloc(32 * sizeof(pci_driver));
	pci_probe();
    return;
}

void pci_register_driver(pci_driver *driv)
{
	pci_drivers[drivs] = driv;
	drivs++;
	return;
}