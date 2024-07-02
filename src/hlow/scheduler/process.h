#pragma once
#include "../cpu/cpu.h"

struct process_t {
    uint64_t pid;
    uint64_t cr3; // Page table base address
    registers_t regs;
    // Additional process metadata can be added here
};

void init_processes();
process_t* create_process(void (*entry)(), uint64_t cr3);
void destroy_process(uint64_t pid);