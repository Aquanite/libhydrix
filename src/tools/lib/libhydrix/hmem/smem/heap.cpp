#include <stddef.h>
#include <stdint.h>

#include <libhydrix/hmem/smem/heap.h>

typedef struct mem_block {
    uint64_t size;
    struct mem_block* next;
} mem_block_t;

static void* mem_heap_base;
static void* mem_heap_end;
static mem_block_t* free_list = NULL;

void heap_init(unsigned long long memsize) {
    mem_heap_base = (void*)memsize;
    mem_heap_end = mem_heap_base;
}

void* kalloc(uint64_t bytes) {
    mem_block_t* prev = NULL;
    mem_block_t* curr = free_list;

    // Align the requested size to the size of mem_block_t
    bytes = (bytes + sizeof(mem_block_t) - 1) & ~(sizeof(mem_block_t) - 1);

    // Find a free block that is large enough
    while (curr) {
        if (curr->size >= bytes) {
            if (prev) {
                prev->next = curr->next;
            } else {
                free_list = curr->next;
            }
            return (void*)(curr + 1);
        }
        prev = curr;
        curr = curr->next;
    }

    // Allocate a new block from the heap
    mem_block_t* block = (mem_block_t*)mem_heap_end;
    mem_heap_end = (bytes + sizeof(mem_block_t) + (uint64_t*)mem_heap_end);

    block->size = bytes;
    return (void*)(block + 1);
}

void kfree(void* ptr) {
    if (!ptr) {
        return;
    }

    mem_block_t* block = (mem_block_t*)ptr - 1;
    block->next = free_list;
    free_list = block;
}

void* krealloc(void* ptr, uint64_t bytes) {
    if (!ptr) {
        return kalloc(bytes);
    }

    mem_block_t* old_block = (mem_block_t*)ptr - 1;
    if (old_block->size >= bytes) {
        return ptr; // The current block is already large enough
    }

    void* newptr = kalloc(bytes);
    if (newptr) {
        memcpy(newptr, ptr, old_block->size);
        kfree(ptr);
    }

    return newptr;
}

void* kcalloc(uint64_t bytes)
{
    void* ptr = kalloc(bytes);
    // Zero out the memory
    memset(ptr, 0, bytes);
    return ptr;
}
