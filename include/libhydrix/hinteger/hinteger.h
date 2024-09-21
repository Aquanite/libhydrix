#pragma once
#include <stdint.h>
#include <stddef.h>
#include <libhydrix/hstring/string.h>
class Integer
{
    public:
        /// @brief Parse an integer from a string
        /// @param str The string
        /// @return The integer
        static int ParseInt(string str);
};