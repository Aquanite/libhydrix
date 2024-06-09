#pragma once
#include <stdint.h>
#include <stddef.h>

class FPU {
    public:
        /// @brief Enable the FPU
        /// @return void
        // @note This function will enable the FPU
        static void Enable();
        /// @brief Check if the FPU is enabled
        /// @return bool
        // @note This function will return true if the FPU is enabled
        static bool Is_Enabled();
        /// @brief Init the FPU
        /// @return void
        // @note This function will initialize the FPU
        static void Init();
};