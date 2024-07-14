#pragma once
#include <stddef.h>
#include <stdint.h>
#include "smem.h"
void InitializeHeap(unsigned long long memsize);
void* KernelAllocate(uint64_t bytes);
void KernelFree(void* ptr);
void* KernelReallocate(void* ptr, uint64_t bytes);
void* KernelCleanAllocate(uint64_t bytes);