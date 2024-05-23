#pragma once
#include "stdint.h"
#include "stddef.h"
typedef char* string;
typedef const char* cstring;

size_t strlen(const char* str);
char* strcat(cstring dest, cstring src);
void reverse(char *str, int len);
char* to_string(int value);
char* to_string(uint8_t value);
char* to_string(uint16_t value);
char* to_string(uint32_t value);
char* to_string(uint64_t value);
char* to_string(float value);