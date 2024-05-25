#pragma once
#include <stdint.h>
#include <stddef.h>

/// @brief The GDT Descriptor
struct GDTDescriptor
{
    uint16_t limit_15_0;
    uint16_t base_15_0;
    uint8_t	base_23_16;
    uint8_t	type;
    uint8_t	limit_19_16_and_flags;
    uint8_t	base_31_24;
} __attribute__((packed));

/// @brief The Task State Segment
struct TaskStateSegment
{
    uint32_t	reserved_0;
    uint64_t	rsp_0;
    uint64_t	rsp_1;
    uint64_t	rsp_2;
    uint64_t	reserved_1;
    uint64_t	ist_1;
    uint64_t	ist_2;
    uint64_t	ist_3;
    uint64_t	ist_4;
    uint64_t	ist_5;
    uint64_t	ist_6;
    uint64_t	ist_7;
    uint64_t	reserved_2;
    uint16_t	reserved_3;
    uint16_t	io_pb_offset;
} __attribute__((packed));

//align all to 4096
__attribute__((aligned(4096)))

/// @brief The Global Descriptor Table
struct GDT
{
    struct GDTDescriptor   null;
    struct GDTDescriptor   kernel_code;
    struct GDTDescriptor   kernel_data;
    struct GDTDescriptor   null2;
    struct GDTDescriptor   user_data;
    struct GDTDescriptor   user_code;
    struct GDTDescriptor   ovmf_data;
    struct GDTDescriptor   ovmf_code;
    struct GDTDescriptor   tss_low;
    struct GDTDescriptor   tss_high;
} __attribute__((packed)); //packed means no padding

/// @brief The GDT Pointer
struct GDTPtr
{
    uint16_t limit_16;
    uint64_t base_64;
} __attribute__((packed));
/// @brief Initialize the GDT
void gdt_init();