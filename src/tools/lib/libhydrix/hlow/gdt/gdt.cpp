#include <libhydrix/hlow/gdt/gdt.h>
extern "C" void _loadGDTandTSS_S(struct GDTPtr* gdtPtr);

static struct TaskStateSegment taskss;
static GDT gdt;
static struct GDTPtr gdtPtr;

void create_descriptors()
{
    // 0x00: Null descriptor
    gdt.null.limit_15_0 = 0;
    gdt.null.base_15_0 = 0;
    gdt.null.base_23_16 = 0;
    gdt.null.type = 0;
    gdt.null.limit_19_16_and_flags = 0;
    gdt.null.base_31_24 = 0;
    // 0x08: Kernel code segment (base selector)
    gdt.kernel_code.limit_15_0 = 0;
    gdt.kernel_code.base_15_0 = 0;
    gdt.kernel_code.base_23_16 = 0;
    gdt.kernel_code.type = 0x9A;
    gdt.kernel_code.limit_19_16_and_flags = 0xA0;
    gdt.kernel_code.base_31_24 = 0;
    // 0x10: Kernel data segment
    gdt.kernel_data.limit_15_0 = 0;
    gdt.kernel_data.base_15_0 = 0;
    gdt.kernel_data.base_23_16 = 0;
    gdt.kernel_data.type = 0x92;
    gdt.kernel_data.limit_19_16_and_flags = 0xA0;
    gdt.kernel_data.base_31_24 = 0;
    // 0x18: null user base selector
    gdt.null2.limit_15_0 = 0;
    gdt.null2.base_15_0 = 0;
    gdt.null2.base_23_16 = 0;
    gdt.null2.type = 0;
    gdt.null2.limit_19_16_and_flags = 0;
    gdt.null2.base_31_24 = 0;
    // 0x20: User data segment
    gdt.user_data.limit_15_0 = 0;
    gdt.user_data.base_15_0 = 0;
    gdt.user_data.base_23_16 = 0;
    gdt.user_data.type = 0x92;
    gdt.user_data.limit_19_16_and_flags = 0xA0;
    gdt.user_data.base_31_24 = 0;
    // 0x28: User code segment
    gdt.user_code.limit_15_0 = 0;
    gdt.user_code.base_15_0 = 0;
    gdt.user_code.base_23_16 = 0;
    gdt.user_code.type = 0x9A;
    gdt.user_code.limit_19_16_and_flags = 0xA0;
    gdt.user_code.base_31_24 = 0;
    // 0x30: OVMF data segment
    gdt.ovmf_data.limit_15_0 = 0;
    gdt.ovmf_data.base_15_0 = 0;
    gdt.ovmf_data.base_23_16 = 0;
    gdt.ovmf_data.type = 0x92;
    gdt.ovmf_data.limit_19_16_and_flags = 0xA0;
    gdt.ovmf_data.base_31_24 = 0;
    // 0x38: OVMF code segment
    gdt.ovmf_code.limit_15_0 = 0;
    gdt.ovmf_code.base_15_0 = 0;
    gdt.ovmf_code.base_23_16 = 0;
    gdt.ovmf_code.type = 0x9A;
    gdt.ovmf_code.limit_19_16_and_flags = 0xA0;
    gdt.ovmf_code.base_31_24 = 0;
    // 0x40: TSS low
    gdt.tss_low.limit_15_0 = 0;
    gdt.tss_low.base_15_0 = 0;
    gdt.tss_low.base_23_16 = 0;
    gdt.tss_low.type = 0x89;
    gdt.tss_low.limit_19_16_and_flags = 0xA0;
    gdt.tss_low.base_31_24 = 0;
    // 0x48: TSS high
    gdt.tss_high.limit_15_0 = 0;
    gdt.tss_high.base_15_0 = 0;
    gdt.tss_high.base_23_16 = 0;
    gdt.tss_high.type = 0x00;
    gdt.tss_high.limit_19_16_and_flags = 0x00;
    gdt.tss_high.base_31_24 = 0;
}

//create descriptors and load GDT + TSS
void InitializeGDT()
{
    create_descriptors();

    //memzero tts
    for (uint64_t i = 0; i < sizeof(taskss); i++)
    {
        ((uint8_t*)(void*)&taskss)[i] = 0;
    }

    uint64_t taskss_base = (uint64_t)&taskss;

    gdt.tss_low.base_15_0 = taskss_base & 0xFFFF;
    gdt.tss_low.base_23_16 = (taskss_base >> 16) & 0xFF;
    gdt.tss_low.base_31_24 = (taskss_base >> 24) & 0xFF;
    gdt.tss_low.limit_15_0 = sizeof(taskss);
    gdt.tss_high.limit_15_0 = (taskss_base >> 32) & 0xFFFF;
    gdt.tss_high.base_15_0 = (taskss_base >> 48) & 0xFFFF;

    gdtPtr.limit_16 = sizeof(gdt) - 1;
    gdtPtr.base_64 = (uint64_t)&gdt;

    _loadGDTandTSS_S(&gdtPtr);
}