#pragma once
#include <stdint.h>
#include <stddef.h>
#include <limine.h>

class LIMINEUtils {
    public:
        /// @brief Get the memory map request
        /// @return limine_memmap_response*
        // @note This function will return the memory map request
        static limine_memmap_response *GetMemoryMap();
        /// @brief Get the total memory size
        /// @return uint64_t
        // @note This function will return the total memory size in bytes
        static uint64_t GetTotalMemoryBytes();
        /// @brief Set the total memory size
        /// @param limine_memmap_response* memmap_request
        /// @return uint64_t
        // @note This function will set the total memory size in bytes
        static uint64_t SetTotalMemoryBytes(limine_memmap_response *memmap_request);
};