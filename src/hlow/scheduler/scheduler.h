#pragma once
#include "process.h"
#include <stdint.h>
void init_scheduler();
void schedule(registers_t* regs);
void add_process_to_schedule(process_t* process);
void remove_process_from_schedule(uint64_t pid);