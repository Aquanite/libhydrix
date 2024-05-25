#pragma once
#include <stdint.h>
#include <stddef.h>
#include "../pic/pic.h"
/// @brief The Interrupt Descriptor Table (64-bit)
struct InterruptDescriptor64 {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint32_t zero;            // reserved
};
/// @brief The IDT Pointer
struct IDTPointer {
   uint16_t limit;
   uint64_t base;
} __attribute__((packed));

/// @brief Initialize the IDT
void idt_init();
/// @brief Set an IDT gate
/// @param num The gate number
/// @param base The base address, can be a function pointer
/// @param sel The selector, usually 0x08
/// @param flags The flags, usually 0x8E
void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags);
/// @brief Load the IDT, called after setting the gates
extern "C" void idt_load();