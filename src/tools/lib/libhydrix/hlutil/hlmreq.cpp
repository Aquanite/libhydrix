#include <libhydrix/hlutil/hlmreq.h>
//get the memory map request
static limine_memmap_response *memmap_res;
static uint64_t Total_Memory_Size_In_Bytes;

uint64_t LimineUtils::Set_Total_Mem(limine_memmap_response *memmap_request)
{
    //loop through each entry and check type
    for (int i = 0; i < memmap_request->entry_count; i++)
    {
        //check if the entry is a usable memory type
        if (memmap_request->entries[i]->type == 0)
        {
            //add the entry size to the total memory size
            Total_Memory_Size_In_Bytes += memmap_request->entries[i]->length;
        }
    }
    return Total_Memory_Size_In_Bytes;
}
uint64_t LimineUtils::Get_Total_Mem()
{
    return Total_Memory_Size_In_Bytes;
}