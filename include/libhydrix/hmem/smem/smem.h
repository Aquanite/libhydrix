#pragma once
#include <limine.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
/// @brief Copy memory
/// @param dest The destination
/// @param src The source
/// @param n The number of bytes to copy
/// @return The destination
void *memcpy(void *dest, const void *src, size_t n);
/// @brief Set memory to a value
/// @param s The memory to set
/// @param c The value to set
/// @param n The number of bytes to set
/// @return The memory
void *memset(void *s, int c, size_t n);
/// @brief Move memory
/// @param dest The destination
/// @param src The source
/// @param n The number of bytes to move
/// @return The destination
void *memmove(void *dest, const void *src, size_t n);
/// @brief Compare memory
/// @param s1 The first memory
/// @param s2 The second memory
/// @param n The number of bytes to compare
/// @return If the memory is equal
int memcmp(const void *s1, const void *s2, size_t n);
#ifdef __cplusplus
}
#endif
uint64_t RetrieveTotalMemory(limine_memmap_response *memmap);
struct MemoryBlock {
    MemoryBlock* next;
    uint64_t size;
    bool is_free;
};
