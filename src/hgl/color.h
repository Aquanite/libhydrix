#pragma once
/// @brief Get the RGB value
/// @param r Red
/// @param g Green
/// @param b Blue
/// @return The RGB value as a bitshifted integer
int rgb(int r, int g, int b);
/// @brief Get the RGBA value
/// @param r Red
/// @param g Green
/// @param b Blue
/// @param a Alpha
/// @return The RGBA value as a bitshifted integer
/// @warning This function has not been tested with the graphics library.
int rgba(int r, int g, int b, int a);