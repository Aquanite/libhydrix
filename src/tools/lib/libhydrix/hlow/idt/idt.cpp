#include <libhydrix/hlow/idt/idt.h>
#include <stdint.h>
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

// Set the idt gate to a handler, which is the location in memory to a function.
void set_idt_gate(int n, uint64_t handler) {
  idt[n].low_offset = (uint16_t)(handler >> 0);
  idt[n].sel = KERNEL_CS;
  idt[n].always0 = 0;
  idt[n].flags = 0x8E;
  idt[n].mid_offset = (uint16_t)(handler >> 16);
  idt[n].high_offset = (uint32_t)(handler >> 32);
  idt[n].always0again = 0;
}

void enable_interrupts() {
  asm volatile("sti");
}

void disable_interrupts() {
  asm volatile("cli");
}

// Load the idt
void set_idt() {
  idt_reg.base = (uint64_t)&idt;
  idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
  asm volatile("lidtq %0" : "=m"(idt_reg));
}

