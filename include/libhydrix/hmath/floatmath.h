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
    static float Absolute(float x);
    /// @brief Add two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The sum
    static float FloatAdd(float a, float b);
    /// @brief Subtract two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The difference
    static float FloatSubtract(float a, float b);
    /// @brief Multiply two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The product
    static float FloatMultiply(float a, float b);
    /// @brief Divide two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The quotient
    static float FloatDivide(float a, float b);
    /// @brief Minimumimum of two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The Minimumimum
    static float Minimum(float a, float b);
    /// @brief Maximumimum of two floating point numbers
    /// @param a The first number
    /// @param b The second number
    /// @return The Maximumimum
    static float Maximum(float a, float b);
    /// @brief Clamp a value between a Minimumimum and Maximumimum
    /// @param x The value
    /// @param Minimum The Minimumimum
    /// @param Maximum The Maximumimum
    /// @return The Clamped value
    static float Clamp(float x, float Minimum, float Maximum);
    /// @brief Float to integer truncation
    /// @param x The value
    /// @return The truncated value (integer)
    static int FloatToTruncatedInteger(float x);
    /// @brief Sign of a floating point number
    /// @param x The value
    /// @return The Sign (-1, 0, 1)
    static float Sign(float x);
    /// @brief Power function
    /// @param x The base
    /// @param y The exponent
    /// @return The result
    static float FloatPower(float x, float y);
    /// @brief Square root
    /// @param x The value
    /// @return The square root
    static float SquareRoot(float x);
    /// @brief Cube root
    /// @param x The value
    /// @return The cube root
    static float CubeRoot(float x);
    /// @brief Exponential function
    /// @param x The value
    /// @return The exponential
    static float Exponential(float x);
    /// @brief Natural logarithm
    /// @param x The value
    /// @return The natural logarithm
    static float Log(float x);
    /// @brief Base 10 logarithm
    /// @param x The value
    /// @return The base 10 logarithm
    static float Log10(float x);
    /// @brief Base 2 logarithm
    /// @param x The value
    /// @return The base 2 logarithm
    static float Log2(float x);
    /// @brief Sine function
    /// @param x The angle
    /// @return The sine
    static float Sine(float x);
    /// @brief Cosine function
    /// @param x The angle
    /// @return The cosine
    static float Cosine(float x);
    /// @brief Tangent function
    /// @param x The angle
    /// @return The tangent
    static float Tangent(float x);
    /// @brief Arcsine function
    /// @param x The value
    /// @return The arcsine
    static float ArcSine(float x);
    /// @brief Arccosine function
    /// @param x The value
    /// @return The arccosine
    static float ArcCosine(float x);
    /// @brief Arctangent function
    /// @param x The value
    /// @return The arctangent
    static float ArcTangent(float x);
    /// @brief Arctangent 2 function
    /// @param y The y value
    /// @param x The x value
    /// @return The arctangent
    static float ArcTangent2(float y, float x);
    /// @brief Hyperbolic sine function
    /// @param x The value
    /// @return The hyperbolic sine
    static float HyperbolicSine(float x);
    /// @brief Hyperbolic cosine function
    /// @param x The value
    /// @return The hyperbolic cosine
    static float HyperbolicCosine(float x);
    /// @brief Hyperbolic tangent function
    /// @param x The value
    /// @return The hyperbolic tangent
    static float HyperbolicTangent(float x);
    /// @brief Inverse hyperbolic sine function
    /// @param x The value
    /// @return The inverse hyperbolic sine
    static float HyperbolicArcSine(float x);
    /// @brief Inverse hyperbolic cosine function
    /// @param x The value
    /// @return The inverse hyperbolic cosine
    static float HyperbolicArcCosine(float x);
    /// @brief Inverse hyperbolic tangent function
    /// @param x The value
    /// @return The inverse hyperbolic tangent
    static float HyperbolicArcTangent(float x);
    /// @brief Floor function
    /// @param x The value
    /// @return The floor
    static float Floor(float x);
    /// @brief Ceiling function
    /// @param x The value
    /// @return The ceiling
    static float Ceiling(float x);
    /// @brief Round function
    /// @param x The value
    /// @return The rounded value
    static float Round(float x);
    /// @brief Truncate function
    /// @param x The value
    /// @return The truncated value
    static float Truncate(float x);
    /// @brief Modulus function
    /// @param x The value
    /// @param y The modulus
    /// @return The modulus
    static float FloatModulus(float x, float y);
    /// @brief Remainder function
    /// @param x The value
    /// @param y The remainder
    /// @return The remainder
    static float Remainder(float x, float y);
    /// @brief CopySign function
    /// @param x The value
    /// @param y The Sign
    /// @return The value with the Sign of y
    static float CopySign(float x, float y);
    /// @brief Not a number
    /// @param tagp The tag
    /// @return The NaN
    static float NaN(const char* tagp);
    /// @brief Nextafter function
    /// @param x Where to start
    /// @param y Where to go
    /// @return The next value
    static float NextAfter(float x, float y);
    /// @brief F Dimension function
    /// @param x The first value
    /// @param y The second value
    /// @return The dimension
    static float FloatDimension(float x, float y);
    /// @brief FMA function
    /// @param x The first value
    /// @param y The second value
    /// @param z The third value
    /// @return The FMA (fused multiply-add)
    static float FusedMultiplyAndAdd(float x, float y, float z);
    /// @brief Maximumimum magnitude function
    /// @param x The first value
    /// @param y The second value
    /// @return The Maximumimum magnitude
    static float FloatMaximumMagnitude(float x, float y);
    /// @brief Minimumimum magnitude function
    /// @param x The first value
    /// @param y The second value
    /// @return The Minimumimum magnitude
    static float FloatMinimumMagnitude(float x, float y);
    /// @brief Square root of the sum of squares
    /// @param x The first value
    /// @param y The second value
    /// @return The hypotenuse
    static float Hypotenuse(float x, float y);
    /// @brief Exponential base 2
    /// @param x The value
    /// @return The exponential base 2
    static float ExponentialBase2(float x);
    /// @brief Exponential Minimumus 1
    /// @param x The value
    /// @return The exponential Minimumus 1
    static float ExponentialMinimumus1(float x);
    /// @brief Natural logarithm of 1 + x
    /// @param x The value
    /// @return The natural logarithm of 1 + x
    static float NaturalLogarithm1p(float x);
    /// @brief Linear interpolation
    /// @param a The first value
    /// @param b The second value
    /// @param t The interpolation factor
    /// @return The interpolated value
    static float LinearInterpolation(float a, float b, float t);
    /// @brief Swap two floating point numbers
    /// @param a The first value
    /// @param b The second value
    static void Swap(float &a, float &b);
};