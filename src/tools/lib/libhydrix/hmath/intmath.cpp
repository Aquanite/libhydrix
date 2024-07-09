#include <libhydrix/hmath/intmath.h>
int MathI::abs(int x) {
    return x < 0 ? -x : x;
}
int MathI::min(int a, int b) {
    return a < b ? a : b;
}
int MathI::max(int a, int b) {
    return a > b ? a : b;
}
int MathI::clamp(int x, int min, int max) {
    return x < min ? min : x > max ? max : x;
}
int MathI::sign(int x) {
    return x < 0 ? -1 : x > 0 ? 1 : 0;
}
int MathI::pow(int x, int y) {
    int result = 1;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}
int MathI::sqrt(int x) {
    int result = 0;
    for (int i = 15; i >= 0; i--) {
        int temp = result | (1 << i);
        if (temp * temp <= x) {
            result = temp;
        }
    }
    return result;
}

int MathI::lerp(int a, int b, int t)
{
    return a + (b - a) * t;
}