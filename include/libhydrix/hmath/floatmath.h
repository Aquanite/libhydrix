#pragma once
#define PI 3.14159265358979323846
#define TAU 6.28318530717958647692
#define E 2.71828182845904523536

class MathF
{
    public:
    /// @brief Absolute value
    /// @param x The value
    /// @return The absolute value
    static float abs(float x);
    /// @brief Add two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The sum
    static float fadd(float a, float b);
    /// @brief Subtract two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The difference
    static float fsub(float a, float b);
    /// @brief Multiply two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The product
    static float fmul(float a, float b);
    /// @brief Divide two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The quotient
    static float fdiv(float a, float b);
    /// @brief Minimum of two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The minimum
    static float min(float a, float b);
    /// @brief Maximum of two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The maximum
    static float max(float a, float b);
    /// @brief Clamp a value between a minimum and maximum
    /// @param x The value
    /// @param min The minimum
    /// @param max The maximum
    /// @return The clamped value
    static float clamp(float x, float min, float max);
    /// @brief Float to integer truncation
    /// @param x The value
    /// @return The truncated value (integer)
    static int f2i_trunc(float x);
    /// @brief Sign of a floating point number
    /// @param x The value
    /// @return The sign (-1, 0, 1)
    static float sign(float x);
    /// @brief Power function
    /// @param x The base
    /// @param y The exponent
    /// @return The result
    static float fpow(float x, float y);
    /// @brief Square root
    /// @param x The value
    /// @return The square root
    static float sqrt(float x);
    /// @brief Cube root
    /// @param x The value
    /// @return The cube root
    static float cbrt(float x);
    /// @brief Exponential function
    /// @param x The value
    /// @return The exponential
    static float exp(float x);
    /// @brief Natural logarithm
    /// @param x The value
    /// @return The natural logarithm
    static float log(float x);
    /// @brief Base 10 logarithm
    /// @param x The value
    /// @return The base 10 logarithm
    static float log10(float x);
    /// @brief Base 2 logarithm
    /// @param x The value
    /// @return The base 2 logarithm
    static float log2(float x);
    /// @brief Sine function
    /// @param x The angle
    /// @return The sine
    static float sin(float x);
    /// @brief Cosine function
    /// @param x The angle
    /// @return The cosine
    static float cos(float x);
    /// @brief Tangent function
    /// @param x The angle
    /// @return The tangent
    static float tan(float x);
    /// @brief Arcsine function
    /// @param x The value
    /// @return The arcsine
    static float asin(float x);
    /// @brief Arccosine function
    /// @param x The value
    /// @return The arccosine
    static float acos(float x);
    /// @brief Arctangent function
    /// @param x The value
    /// @return The arctangent
    static float atan(float x);
    /// @brief Arctangent 2 function
    /// @param y The y value
    /// @param x The x value
    /// @return The arctangent
    static float atan2(float y, float x);
    /// @brief Hyperbolic sine function
    /// @param x The value
    /// @return The hyperbolic sine
    static float sinh(float x);
    /// @brief Hyperbolic cosine function
    /// @param x The value
    /// @return The hyperbolic cosine
    static float cosh(float x);
    /// @brief Hyperbolic tangent function
    /// @param x The value
    /// @return The hyperbolic tangent
    static float tanh(float x);
    /// @brief Inverse hyperbolic sine function
    /// @param x The value
    /// @return The inverse hyperbolic sine
    static float asinh(float x);
    /// @brief Inverse hyperbolic cosine function
    /// @param x The value
    /// @return The inverse hyperbolic cosine
    static float acosh(float x);
    /// @brief Inverse hyperbolic tangent function
    /// @param x The value
    /// @return The inverse hyperbolic tangent
    static float atanh(float x);
    /// @brief Floor function
    /// @param x The value
    /// @return The floor
    static float floor(float x);
    /// @brief Ceiling function
    /// @param x The value
    /// @return The ceiling
    static float ceil(float x);
    /// @brief Round function
    /// @param x The value
    /// @return The rounded value
    static float round(float x);
    /// @brief Truncate function
    /// @param x The value
    /// @return The truncated value
    static float trunc(float x);
    /// @brief Modulus function
    /// @param x The value
    /// @param y The modulus
    /// @return The modulus
    static float fmod(float x, float y);
    /// @brief Remainder function
    /// @param x The value
    /// @param y The remainder
    /// @return The remainder
    static float remainder(float x, float y);
    /// @brief Copysign function
    /// @param x The value
    /// @param y The sign
    /// @return The value with the sign of y
    static float copysign(float x, float y);
    /// @brief Not a number
    /// @param tagp The tag
    /// @return The NaN
    static float nan(const char* tagp);
    /// @brief Nextafter function
    /// @param x Where to start
    /// @param y Where to go
    /// @return The next value
    static float nextafter(float x, float y);
    /// @brief F Dimension function
    /// @param x The first value
    /// @param y The second value
    /// @return The dimension
    static float fdim(float x, float y);
    /// @brief FMA function
    /// @param x The first value
    /// @param y The second value
    /// @param z The third value
    /// @return The FMA (fused multiply-add)
    static float fma(float x, float y, float z);
    /// @brief Maximum magnitude function
    /// @param x The first value
    /// @param y The second value
    /// @return The maximum magnitude
    static float fmaxmag(float x, float y);
    /// @brief Minimum magnitude function
    /// @param x The first value
    /// @param y The second value
    /// @return The minimum magnitude
    static float fminmag(float x, float y);
    /// @brief Square root of the sum of squares
    /// @param x The first value
    /// @param y The second value
    /// @return The hypotenuse
    static float hypot(float x, float y);
    /// @brief Exponential base 2
    /// @param x The value
    /// @return The exponential base 2
    static float exp2(float x);
    /// @brief Exponential minus 1
    /// @param x The value
    /// @return The exponential minus 1
    static float expm1(float x);
    /// @brief Natural logarithm of 1 + x
    /// @param x The value
    /// @return The natural logarithm of 1 + x
    static float log1p(float x);
    /// @brief Linear interpolation
    /// @param a The first value
    /// @param b The second value
    /// @param t The interpolation factor
    /// @return The interpolated value
    static float lerpf(float a, float b, float t);
};