#include <libhydrix/hmath/intmath.h>
int MathI::Absolute(int x) {
    return x < 0 ? -x : x;
}
int MathI::Minimum(int a, int b) {
    return a < b ? a : b;
}
int MathI::Maximum(int a, int b) {
    return a > b ? a : b;
}
int MathI::Clamp(int x, int Minimum, int Maximum) {
    return x < Minimum ? Minimum : x > Maximum ? Maximum : x;
}
int MathI::Sign(int x) {
    return x < 0 ? -1 : x > 0 ? 1 : 0;
}
int MathI::Power(int x, int y) {
    int result = 1;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}
int MathI::SquareRoot(int x) {
    int result = 0;
    for (int i = 15; i >= 0; i--) {
        int temp = result | (1 << i);
        if (temp * temp <= x) {
            result = temp;
        }
    }
    return result;
}

int MathI::LinearInterpolation(int a, int b, int t)
{
    return a + (b - a) * t;
}