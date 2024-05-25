#include "idt.h"
#include "../../hmem/smem/smem.h"
// Define the IDT
InterruptDescriptor64 idt[256];
//idt pointer
IDTPointer idt_ptr;

void idt_init()
{
    // Set the pointer
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint64_t)&idt;

    // Clear the IDT
    memset(&idt, 0, sizeof(idt));

    // Remap the PIC
    PIC_remap(0x20, 0x28); // 0x20 is the master offset, 0x28 is the slave offset

    // Set the IDT pointer
    idt_load();
}

void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags)
{
    // Set the base address
    idt[num].offset_1 = (uint16_t)(base & 0xFFFF);
    idt[num].offset_2 = (uint16_t)((base >> 16) & 0xFFFF);
    idt[num].offset_3 = (uint32_t)((base >> 32) & 0xFFFFFFFF);

    // Set the selector
    idt[num].selector = sel;

    // Set IST
    idt[num].ist = 0;

    // Set the type and attributes
    idt[num].type_attributes = flags;
}
extern "C" void idt_load()
{
    asm volatile("lidt %0" : : "m"(idt_ptr));
}