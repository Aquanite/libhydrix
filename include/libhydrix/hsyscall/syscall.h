#pragma once
#include <stdint.h>
#include <libhydrix/hlow/cpu/cpu.h>
#include <libhydrix/hcon/console.h>
#define SYSCALLINT 0x80

void InitializeSyscall(Console* con);
void HandleSyscall(registers_t *r);