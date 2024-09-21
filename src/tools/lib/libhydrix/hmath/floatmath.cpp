#include <libhydrix/hmath/floatmath.h>

float MathF::Absolute(float x) {
        return x < 0 ? -x : x;
    }
    float MathF::FloatAdd(float a, float b) {
        return a + b;
    }
    float MathF::FloatSubtract(float a, float b) {
        return a - b;
    }
    float MathF::FloatMultiply(float a, float b) {
        return a * b;
    }
    float MathF::FloatDivide(float a, float b) {
        return a / b;
    }
    float MathF::Minimum(float a, float b) {
        return a < b ? a : b;
    }
    float MathF::Maximum(float a, float b) {
        return a > b ? a : b;
    }
    float MathF::Clamp(float x, float Minimum, float Maximum) {
        return x < Minimum ? Minimum : x > Maximum ? Maximum : x;
    }
    int MathF::FloatToTruncatedInteger(float x)
    {
        return (int)x;
    }
    float MathF::Sign(float x) {
        return x < 0 ? -1 : x > 0 ? 1 : 0;
    }
    float MathF::FloatPower(float x, float y) {
        float result = 1;
        for (int i = 0; i < y; i++) {
            result *= x;
        }
        return result;
    }
    float MathF::SquareRoot(float x) {
        float result = x;
        for (int i = 0; i < 10; i++) {
            result = 0.5 * (result + x / result);
        }
        return result;
    }
    float MathF::CubeRoot(float x) {
        float result = x;
        for (int i = 0; i < 10; i++) {
            result = (1.0 / 3.0) * ((2 * result) + (x / (result * result)));
        }
        return result;
    }
    float MathF::Exponential(float x) {
        float result = 1;
        for (int i = 0; i < 10; i++) {
            result += FloatPower(x, i) / 1;
        }
        return result;
    }
    float MathF::Log(float x) {
        float result = 0;
        for (int i = 1; i < 10; i++) {
            result += FloatPower(-1, i + 1) * FloatPower(x - 1, i) / i;
        }
        return result;
    }
    float MathF::Log10(float x) {
        return Log(x) / Log(10);
    }
    float MathF::Log2(float x) {
        return Log(x) / Log(2);
    }
    float MathF::Sine(float x) {
        float result = 0;
        for (int i = 0; i < 10; i++) {
            result += FloatPower(-1, i) * FloatPower(x, 2 * i + 1) / 1;
        }
        return result;
    }
    float MathF::Cosine(float x) {
        float result = 0;
        for (int i = 0; i < 10; i++) {
            result += FloatPower(-1, i) * FloatPower(x, 2 * i) / 1;
        }
        return result;
    }
    float MathF::Tangent(float x) {
        return Sine(x) / Cosine(x);
    }
    float MathF::ArcSine(float x) {
        float result = 0;
        for (int i = 0; i < 10; i++) {
            result += FloatPower(-1, i) * FloatPower(2 * i - 1, 2 * i + 1) * FloatPower(x, 2 * i + 1) / (2 * i + 1);
        }
        return result;
    }
    float MathF::ArcCosine(float x) {
        return PI / 2 - ArcSine(x);
    }
    float MathF::ArcTangent(float x) {
        float result = 0;
        for (int i = 0; i < 10; i++) {
            result += FloatPower(-1, i) * FloatPower(x, 2 * i + 1) / (2 * i + 1);
        }
        return result;
    }
    float MathF::ArcTangent2(float y, float x) {
        return ArcTangent(y / x);
    }
    float MathF::HyperbolicSine(float x) {
        return (Exponential(x) - Exponential(-x)) / 2;
    }
    float MathF::HyperbolicCosine(float x) {
        return (Exponential(x) + Exponential(-x)) / 2;
    }
    float MathF::HyperbolicTangent(float x) {
        return HyperbolicSine(x) / HyperbolicCosine(x);
    }
    float MathF::HyperbolicArcSine(float x) {
        return Log(x + SquareRoot(x * x + 1));
    }
    float MathF::HyperbolicArcCosine(float x) {
        return Log(x + SquareRoot(x * x - 1));
    }
    float MathF::HyperbolicArcTangent(float x) {
        return Log((1 + x) / (1 - x)) / 2;
    }
    float MathF::Floor(float x) {
        return x - (int)x;
    }
    float MathF::Ceiling(float x) {
        return (int)x + 1 - x;
    }
    float MathF::Round(float x) {
        return x - (int)x < 0.5 ? Floor(x) : Ceiling(x);
    }
    float MathF::Truncate(float x) {
        return x < 0 ? Ceiling(x) : Floor(x);
    }
    float MathF::FloatModulus(float x, float y) {
        return x - y * Floor(x / y);
    }
    float MathF::Remainder(float x, float y) {
        return x - y * Round(x / y);
    }
    float MathF::CopySign(float x, float y) {
        return Absolute(x) * Sign(y);
    }
    float MathF::NaN(const char* tagp) {
        return 0.0 / 0.0;
    }
    float MathF::NextAfter(float x, float y) {
        return x < y ? x + 1 : x - 1;
    }
    float MathF::FloatDimension(float x, float y) {
        return x < y ? 0 : x - y;
    }
    float MathF::FusedMultiplyAndAdd(float x, float y, float z) {
        return x * y + z;
    }
    float MathF::FloatMaximumMagnitude(float x, float y) {
        return Absolute(x) > Absolute(y) ? x : y;
    }
    float MathF::FloatMinimumMagnitude(float x, float y) {
        return Absolute(x) < Absolute(y) ? x : y;
    }
    float MathF::Hypotenuse(float x, float y) {
        return SquareRoot(x * x + y * y);
    }
    float MathF::ExponentialBase2(float x) {
        return FloatPower(2, x);
    }
    float MathF::ExponentialMinimumus1(float x) {
        return Exponential(x) - 1;
    }
    float MathF::NaturalLogarithm1p(float x) {
        return Log(x + 1);
    }
    float MathF::LinearInterpolation(float a, float b, float t) {
        return a + t * (b - a);
    }
    void MathF::Swap(float &a, float &b)
    {
        float temp = a;
        a = b;
        b = temp;
    }