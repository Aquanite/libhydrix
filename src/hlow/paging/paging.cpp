#include "paging.h"
#include "../../hmem/smem/heap.h"

static PageTable* kernel_pml4;
static struct limine_memmap_entry** memmaps;

static inline void flushTLB(void* page) 
{
	__asm__ volatile ("invlpg (%0)" :: "r" (page) : "memory");
}

void Set_LIMINE_MEMMAP_PAGING(limine_memmap_entry **memmaps)
{
    memmaps = memmaps;
}

uint64_t GetCR3()
{
    uint64_t val;
    __asm__ volatile ( "mov %%cr3, %0" : "=r"(val) );
    return val;
}

PageTable* InitPML4()
{
    uintptr_t cr3 = (uintptr_t) GetCR3();
	kernel_pml4 = (PageTable*) ((cr3 >> 12) << 12);
	return kernel_pml4;
}

void SetPageTableEntry(PageEntry* entry, uint8_t flags, uintptr_t physical_address, uint16_t available) 
{
    entry->present = (flags >> 1) & 1;
    entry->writable = (flags >> 2) & 1;
    entry->user_accessible = (flags >> 3) & 1;
    entry->write_through_caching = (flags & 0x8) & 1;
    entry->disable_cache = (flags & 0x10) & 1;
    entry->null = (flags & 0x20) & 1;
    entry->global = (flags & 0x40) & 1;
    entry->avl1 = available & 0x3;
    entry->physical_address = physical_address; 
    entry->avl2 = available >> 3;
    entry->no_execute = flags >> 7;
}

void* GetPhysAddy(void* virtual_address)
{
    uintptr_t address = (uintptr_t) virtual_address;

    uint64_t offset = address & 0xFFF;
    uint64_t page_table_index = (address >> 12) & 0x1FF;
    uint64_t page_directory_index = (address >> 21) & 0x1FF;
    uint64_t page_directory_pointer_index = (address >> 30) & 0x1FF;
    uint64_t pml4_index = (address >> 39) & 0x1FF;

    PageTable* page_directory_pointer = (PageTable*) ((uint64_t) (kernel_pml4->entries[pml4_index].physical_address) << 12);
    PageTable* page_directory = (PageTable*) ((uint64_t) (page_directory_pointer->entries[page_directory_pointer_index].physical_address) << 12);
    PageTable* page_table = (PageTable*) ((uint64_t) (page_directory->entries[page_directory_index].physical_address) << 12);

    return (void*) ((page_table->entries[page_table_index].physical_address << 12) + offset);
}

static void allocateEntry(PageTable* table, size_t index, uint8_t flags)
{
    void* physical_address = kalloc(4096);
    SetPageTableEntry(&(table->entries[index]), flags, (uintptr_t) physical_address >> 12, 0);
}

void MapPage(void* virtual_address, void* physical_address, uint8_t flags) 
{
    // Make sure that both addresses are page-aligned.
    uintptr_t virtual_address_int = (uintptr_t) virtual_address;
    uintptr_t physical_address_int = (uintptr_t) physical_address;

    uint64_t pml4_index = (virtual_address_int >> 39) & 0x1FF;
    uint64_t page_directory_pointer_index = (virtual_address_int >> 30) & 0x1FF;
    uint64_t page_directory_index = (virtual_address_int >> 21) & 0x1FF;
    uint64_t page_table_index = (virtual_address_int >> 12) & 0x1FF;
 
    if (!kernel_pml4->entries[pml4_index].present)
        allocateEntry(kernel_pml4, pml4_index, flags);

    PageTable* page_directory_pointer = (PageTable*) (uint64_t) (kernel_pml4->entries[pml4_index].physical_address << 12);

    if (!page_directory_pointer->entries[page_directory_pointer_index].present) 
        allocateEntry(page_directory_pointer, page_directory_pointer_index, flags);

    PageTable* page_directory = (PageTable*) (uint64_t) (page_directory_pointer->entries[page_directory_pointer_index].physical_address << 12);

    if (!page_directory->entries[page_directory_index].present) 
        allocateEntry(page_directory, page_directory_index, flags);

    PageTable* page_table = (PageTable*) (uint64_t) (page_directory->entries[page_directory_index].physical_address << 12);

    SetPageTableEntry(&(page_table->entries[page_table_index]), flags, physical_address_int >> 12, 0);
	
    // Now you need to flush the entry in the TLB
    flushTLB(virtual_address);
}