#include <libhydrix/hmath/floatmath.h>
float MathF::abs(float x) {
        return x < 0 ? -x : x;
    }
    float MathF::fadd(float a, float b) {
        return a + b;
    }
    float MathF::fsub(float a, float b) {
        return a - b;
    }
    float MathF::fmul(float a, float b) {
        return a * b;
    }
    float MathF::fdiv(float a, float b) {
        return a / b;
    }
    float MathF::min(float a, float b) {
        return a < b ? a : b;
    }
    float MathF::max(float a, float b) {
        return a > b ? a : b;
    }
    float MathF::clamp(float x, float min, float max) {
        return x < min ? min : x > max ? max : x;
    }
    int MathF::f2i_trunc(float x)
    {
        return (int)x;
    }
    float MathF::sign(float x) {
        return x < 0 ? -1 : x > 0 ? 1 : 0;
    }
    float MathF::fpow(float x, float y) {
        float result = 1;
        for (int i = 0; i < y; i++) {
            result *= x;
        }
        return result;
    }
    float MathF::sqrt(float x) {
        float result = x;
        for (int i = 0; i < 10; i++) {
            result = 0.5 * (result + x / result);
        }
        return result;
    }
    float MathF::cbrt(float x) {
        float result = x;
        for (int i = 0; i < 10; i++) {
            result = (1.0 / 3.0) * ((2 * result) + (x / (result * result)));
        }
        return result;
    }
    float MathF::exp(float x) {
        float result = 1;
        for (int i = 0; i < 10; i++) {
            result += fpow(x, i) / 1;
        }
        return result;
    }
    float MathF::log(float x) {
        float result = 0;
        for (int i = 1; i < 10; i++) {
            result += fpow(-1, i + 1) * fpow(x - 1, i) / i;
        }
        return result;
    }
    float MathF::log10(float x) {
        return log(x) / log(10);
    }
    float MathF::log2(float x) {
        return log(x) / log(2);
    }
    float MathF::sin(float x) {
        float result = 0;
        for (int i = 0; i < 10; i++) {
            result += fpow(-1, i) * fpow(x, 2 * i + 1) / 1;
        }
        return result;
    }
    float MathF::cos(float x) {
        float result = 0;
        for (int i = 0; i < 10; i++) {
            result += fpow(-1, i) * fpow(x, 2 * i) / 1;
        }
        return result;
    }
    float MathF::tan(float x) {
        return sin(x) / cos(x);
    }
    float MathF::asin(float x) {
        float result = 0;
        for (int i = 0; i < 10; i++) {
            result += fpow(-1, i) * fpow(2 * i - 1, 2 * i + 1) * fpow(x, 2 * i + 1) / (2 * i + 1);
        }
        return result;
    }
    float MathF::acos(float x) {
        return PI / 2 - asin(x);
    }
    float MathF::atan(float x) {
        float result = 0;
        for (int i = 0; i < 10; i++) {
            result += fpow(-1, i) * fpow(x, 2 * i + 1) / (2 * i + 1);
        }
        return result;
    }
    float MathF::atan2(float y, float x) {
        return atan(y / x);
    }
    float MathF::sinh(float x) {
        return (exp(x) - exp(-x)) / 2;
    }
    float MathF::cosh(float x) {
        return (exp(x) + exp(-x)) / 2;
    }
    float MathF::tanh(float x) {
        return sinh(x) / cosh(x);
    }
    float MathF::asinh(float x) {
        return log(x + sqrt(x * x + 1));
    }
    float MathF::acosh(float x) {
        return log(x + sqrt(x * x - 1));
    }
    float MathF::atanh(float x) {
        return log((1 + x) / (1 - x)) / 2;
    }
    float MathF::floor(float x) {
        return x - (int)x;
    }
    float MathF::ceil(float x) {
        return (int)x + 1 - x;
    }
    float MathF::round(float x) {
        return x - (int)x < 0.5 ? floor(x) : ceil(x);
    }
    float MathF::trunc(float x) {
        return x < 0 ? ceil(x) : floor(x);
    }
    float MathF::fmod(float x, float y) {
        return x - y * floor(x / y);
    }
    float MathF::remainder(float x, float y) {
        return x - y * round(x / y);
    }
    float MathF::copysign(float x, float y) {
        return abs(x) * sign(y);
    }
    float MathF::nan(const char* tagp) {
        return 0.0 / 0.0;
    }
    float MathF::nextafter(float x, float y) {
        return x < y ? x + 1 : x - 1;
    }
    float MathF::fdim(float x, float y) {
        return x < y ? 0 : x - y;
    }
    float MathF::fma(float x, float y, float z) {
        return x * y + z;
    }
    float MathF::fmaxmag(float x, float y) {
        return abs(x) > abs(y) ? x : y;
    }
    float MathF::fminmag(float x, float y) {
        return abs(x) < abs(y) ? x : y;
    }
    float MathF::hypot(float x, float y) {
        return sqrt(x * x + y * y);
    }
    float MathF::exp2(float x) {
        return fpow(2, x);
    }
    float MathF::expm1(float x) {
        return exp(x) - 1;
    }
    float MathF::log1p(float x) {
        return log(x + 1);
    }
    float MathF::lerpf(float a, float b, float t) {
        return a + t * (b - a);
    }