#pragma once
#include <stdint.h>
#include <stddef.h>
class IColor
{
    public:
    
    /// @brief Get the RGB value
    /// @param r Red
    /// @param g Green
    /// @param b Blue
    /// @return The RGB value as a bitshifted integer
    static int RGB(int r, int g, int b);
    /// @brief Get the inverted RGB value
    /// @param r Red
    /// @param g Green
    /// @param b Blue
    /// @return The inverted RGB value as a bitshifted integer
    static int InverseRGB(int r, int g, int b);
    /// @brief Get the RGBA value
    /// @param r Red
    /// @param g Green
    /// @param b Blue
    /// @param a Alpha
    /// @return The RGBA value as a bitshifted integer
    static long RGBA(int r, int g, int b, int a);
    /// @brief Get the inverted RGBA value
    /// @param r Red
    /// @param g Green
    /// @param b Blue
    /// @return The inverted RGBA value as a bitshifted integer
    static long InverseRGBA(int r, int g, int b, int a);
    /// @brief Get the RGB value from an RGBA value
    /// @param color The RGBA value
    /// @return The RGB value as a bitshifted integer
    static int RGBAToRGB(long color);
    /// @brief Convert an `int` to RBG values
    /// @param value The color int
    /// @return uint8_t*, [0] r, [1] g, [2] b
    static uint8_t* IntToRGB(int value);
    /// @brief Convert a `long` to RBGA values
    /// @param value The color long
    /// @return uint8_t*, [0] R, [1] G, [2] B, [3] ALPHA
    static uint8_t *LongToRGBA(long value);
    /// @brief Get the inverted RGB value
    /// @param color The RGB value
    /// @return The inverted RGB value as a bitshifted integer
    static int InverseRGBHex(int color);
    /// @brief Get the inverted RGBA value
    /// @param color The RGBA value
    /// @return The inverted RGBA value as a bitshifted integer
    static long InverseRGBAHex(long color);
};