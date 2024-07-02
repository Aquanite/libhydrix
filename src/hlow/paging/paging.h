#pragma once
#include <stdint.h>
#include <limine.h>
typedef struct PageEntry {
    uint8_t present : 1;
    uint8_t writable : 1;
    uint8_t user_accessible : 1;
    uint8_t write_through_caching : 1;
    uint8_t disable_cache : 1;
    uint8_t accessed : 1;
    uint8_t dirty : 1;
    uint8_t null : 1;
    uint8_t global : 1;
    uint8_t avl1 : 3;
    uintptr_t physical_address : 40;
    uint16_t avl2 : 11;
    uint8_t no_execute : 1;
} PageEntry;

typedef struct PageTable {
    PageEntry entries[512];
} PageTable;

void* GetPhysAddy(void* virtual_address); 
void Set_LIMINE_MEMMAP_PAGING(limine_memmap_entry** memmaps);
PageTable* InitPML4(); 
void MapPage(void* virtual_address, void* physical_address, uint8_t flags);
uint64_t GetCR3();