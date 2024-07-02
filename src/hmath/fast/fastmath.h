#pragma once
#include <stdint.h>
#include <stddef.h>

extern "C" void fastmath_abs(int* x);
extern "C" int retable_fastmath_abs(int x);
extern "C" void fastmath_sqrt(int* x);
extern "C" int retable_fastmath_sqrt(int x);