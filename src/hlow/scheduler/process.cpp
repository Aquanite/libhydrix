#include "process.h"
#include "../../hmem/smem/heap.h"
static process_t* current_process = nullptr;
static uint64_t next_pid = 1;

void init_processes() {
    current_process = nullptr;
    next_pid = 1;
}

process_t* create_process(void (*entry)(), uint64_t cr3) {
    process_t* process = (process_t*)kalloc(sizeof(process_t));
    if (!process) return nullptr;

    process->pid = next_pid++;
    process->cr3 = cr3;

    // Initialize registers
    process->regs = {};
    process->regs.rip = (uint64_t)entry;
    process->regs.cs = 0x08; // Kernel code segment
    process->regs.rflags = 0x202; // Interrupt enable flag
    process->regs.rsp = 0; // Stack pointer needs to be set
    process->regs.ss = 0x10; // Kernel data segment

    return process;
}

void destroy_process(uint64_t pid) {
    if (current_process && current_process->pid == pid) {
        kfree(current_process);
        current_process = nullptr;
    }
}