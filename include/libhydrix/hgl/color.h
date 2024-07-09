#pragma once
#include <stdint.h>
#include <stddef.h>
/// @brief Get the RGB value
/// @param r Red
/// @param g Green
/// @param b Blue
/// @return The RGB value as a bitshifted integer
int rgb(int r, int g, int b);
/// @brief Get the inverted RGB value
/// @param r Red
/// @param g Green
/// @param b Blue
/// @return The inverted RGB value as a bitshifted integer
int inverse_rgb(int r, int g, int b);
/// @brief Get the RGBA value
/// @param r Red
/// @param g Green
/// @param b Blue
/// @param a Alpha
/// @return The RGBA value as a bitshifted integer
long rgba(int r, int g, int b, int a);
/// @brief Get the inverted RGBA value
/// @param r Red
/// @param g Green
/// @param b Blue
/// @return The inverted RGBA value as a bitshifted integer
long inverse_rgba(int r, int g, int b, int a);
/// @brief Get the RGB value from an RGBA value
/// @param color The RGBA value
/// @return The RGB value as a bitshifted integer
int a2rgb(long color);
/// @brief Convert an `int` to RBG values
/// @param value The color int
/// @return uint8_t*, [0] r, [1] g, [2] b
uint8_t* int_to_rgb(int value);
/// @brief Convert a `long` to RBGA values
/// @param value The color long
/// @return uint8_t*, [0] R, [1] G, [2] B, [3] ALPHA
uint8_t *long_to_rgba(long value);
/// @brief Get the inverted RGB value
/// @param color The RGB value
/// @return The inverted RGB value as a bitshifted integer
int inverse_rgb_hex(int color);
/// @brief Get the inverted RGBA value
/// @param color The RGBA value
/// @return The inverted RGBA value as a bitshifted integer
long inverse_rgba_hex(long color);