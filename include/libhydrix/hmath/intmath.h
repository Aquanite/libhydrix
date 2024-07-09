#pragma once
//intmath

/// @brief Basic Integer Arithmetic
class MathI
{
public:
    /// @brief Absolute value
    /// @param x The number
    /// @return The absolute value of x
    static int abs(int x);
    /// @brief Minimum of two numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The minimum of a and b
    static int min(int a, int b);
    /// @brief Maximum of two numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The maximum of a and b
    static int max(int a, int b);
    /// @brief Clamp a number between a minimum and a maximum
    /// @param x The number
    /// @param min The minimum
    /// @param max The maximum
    /// @return The clamped number
    static int clamp(int x, int min, int max);
    /// @brief Sign of a number
    /// @param x The number
    /// @return -1 if x is negative, 1 if x is positive, 0 if x is zero
    static int sign(int x);
    /// @brief Power of a number
    /// @param x The base
    /// @param y The exponent
    /// @return x raised to the power of y
    static int pow(int x, int y);
    /// @brief Square root of a number
    /// @param x The number
    /// @return The square root of x (truncated to an integer)
    static int sqrt(int x);
    /// @brief Linear interpolation
    /// @param a The first number
    /// @param b The second number
    /// @param t The interpolation factor
    /// @return The interpolated number
    static int lerp(int a, int b, int t);
};