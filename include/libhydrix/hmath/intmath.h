#pragma once
//intmath

/// @brief Basic Integer Arithmetic
class MathI
{
public:
    /// @brief Absolute value
    /// @param x The number
    /// @return The absolute value of x
    static int Absolute(int x);
    /// @brief Minimumimum of two numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The Minimumimum of a and b
    static int Minimum(int a, int b);
    /// @brief Maximumimum of two numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The Maximumimum of a and b
    static int Maximum(int a, int b);
    /// @brief Clamp a number between a Minimumimum and a Maximumimum
    /// @param x The number
    /// @param Minimum The Minimumimum
    /// @param Maximum The Maximumimum
    /// @return The Clamped number
    static int Clamp(int x, int Minimum, int Maximum);
    /// @brief Sign of a number
    /// @param x The number
    /// @return -1 if x is negative, 1 if x is positive, 0 if x is zero
    static int Sign(int x);
    /// @brief Power of a number
    /// @param x The base
    /// @param y The exponent
    /// @return x raised to the power of y
    static int Power(int x, int y);
    /// @brief Square root of a number
    /// @param x The number
    /// @return The square root of x (truncated to an integer)
    static int SquareRoot(int x);
    /// @brief Linear interpolation
    /// @param a The first number
    /// @param b The second number
    /// @param t The interpolation factor
    /// @return The interpolated number
    static int LinearInterpolation(int a, int b, int t);
};