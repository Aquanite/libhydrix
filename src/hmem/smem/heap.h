#pragma once
#include <stddef.h>
#include <stdint.h>
#include "smem.h"
void heap_init(unsigned long long memsize);
void* kalloc(uint64_t bytes);
void kfree(void* ptr);
void* krealloc(void* ptr, uint64_t bytes);
void* kcalloc(uint64_t bytes);