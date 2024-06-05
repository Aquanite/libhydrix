#include "heap.h"
unsigned long long mem_heap_base;
void heap_init(unsigned long long memsize)
{
    mem_heap_base = memsize;
}
void* kalloc(int bytes)
{
    void* ret = (void*)mem_heap_base;
    mem_heap_base += bytes;
    return ret;
}