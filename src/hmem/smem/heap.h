#pragma once
#include <stddef.h>
#include <stdint.h>
void heap_init(unsigned long long memsize);
void* kalloc( uint64_t bytes );