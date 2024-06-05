#pragma once
#include "stdint.h"
#include "stddef.h"
#include "../hmath/higherbitmath.h"
//define VA_LIST and va_start, va_arg, va_end etc
typedef char* va_list;
#define va_start(ap, v) (ap = (va_list)&v + sizeof(v))
#define va_arg(ap, t) (*(t*)(ap += sizeof(t)))
#define va_end(ap) (ap = NULL)

/// @brief String
typedef char* string;
/// @brief Constant string
typedef const char* cstring;
/// @brief String length
/// @param str The string
/// @return The length
size_t strlen(const char* str);
/// @brief Concatenate two strings
/// @param dest The destination
/// @param src The source
/// @return The new string
char* strcat(cstring dest, cstring src);
/// @brief Reverse a string
/// @param str The string
/// @param len The length to reverse
void reverse(char *str, int len);
/// @brief Convert an integer to a string
/// @param value The integer
/// @return The string
char* to_string(int value);
/// @brief Convert a unsigned char to a string
/// @param value The unsigned char
/// @return The string
char* to_string(uint8_t value);
/// @brief Convert a unsigned short to a string
/// @param value The unsigned short
/// @return The string
char* to_string(uint16_t value);
/// @brief Convert a unsigned int to a string
/// @param value The unsigned int
/// @return The string
char* to_string(uint32_t value);
/// @brief Convert a unsigned long long to a string
/// @param value The unsigned long long
/// @return The string
char* to_string(uint64_t value);
/// @brief Convert a float to a string
/// @param value The float
/// @return The string
char* to_string(float value);
/// @brief Convert a double to a string
/// @param value The double
/// @return The string
char* to_string(double value);
/// @brief Convert a char to a string
/// @param value The char
/// @return The string
char* to_string(char value);
/// @brief Convert a bool to a string
/// @param value The bool
/// @return The string
char* to_string(bool value);
/// @brief Convert an integer to a string
/// @param value The integer
/// @param buffer The buffer
/// @return The string in hex
char* to_string_hex(int value);
/// @brief Convert an integer to char
/// @param value The integer
/// @return The char
char to_char(int value);