#include "heap.h"
void* mem_heap_base;
void heap_init(unsigned long long memsize)
{
    mem_heap_base = (void*)memsize;
}
void* kalloc(uint64_t bytes)
{
    void* ret = mem_heap_base;
    mem_heap_base += bytes;
    return ret;
}
