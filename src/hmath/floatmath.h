#pragma once
#define PI 3.14159265358979323846
#define TAU 6.28318530717958647692
#define E 2.71828182845904523536

class MathF
{
    static float abs(float x);
static float fadd(float a, float b);
static float fsub(float a, float b);
static float fmul(float a, float b);
static float fdiv(float a, float b);
static float min(float a, float b);
static float max(float a, float b);
static float clamp(float x, float min, float max);
static int f2i_trunc(float x);
static float sign(float x);
static float fpow(float x, float y);
static float sqrt(float x);
static float cbrt(float x);
static float exp(float x);
static float log(float x);
static float log10(float x);
static float log2(float x);
static float sin(float x);
static float cos(float x);
static float tan(float x);
static float asin(float x);
static float acos(float x);
static float atan(float x);
static float atan2(float y, float x);
static float sinh(float x);
static float cosh(float x);
static float tanh(float x);
static float asinh(float x);
static float acosh(float x);
static float atanh(float x);
static float floor(float x);
static float ceil(float x);
static float round(float x);
static float trunc(float x);
static float fmod(float x, float y);
static float remainder(float x, float y);
static float copysign(float x, float y);
static float nan(const char* tagp);
static float nextafter(float x, float y);
static float fdim(float x, float y);
static float fmax(float x, float y);
static float fmin(float x, float y);
static float fma(float x, float y, float z);
static float fmaxmag(float x, float y);
static float fminmag(float x, float y);
static float hypot(float x, float y);
static float exp2(float x);
static float expm1(float x);
static float log1p(float x);
static float lerpf(float a, float b, float t);
};