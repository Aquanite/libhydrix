#pragma once
#include <stdint.h>
#include "../hlow/cpu/cpu.h"
#include "../hcon/console.h"
#define SYSCALLINT 0x80

void syscall_init(Console* con);
void handle_syscall(registers_t *r);