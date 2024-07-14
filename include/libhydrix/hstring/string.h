#pragma once
#include <stdint.h>
#include <stddef.h>
//include va list
#include <stdarg.h>

/// @brief String
typedef char* string;
/// @brief Constant string
typedef const char* cstring;
/// @brief String length
/// @param str The string
/// @return The length
size_t StringLength(const char* str);
/// @brief Concatenate two strings
/// @param dest The destination
/// @param src The source
/// @return The new string
char* StringConcatenate(cstring dest, cstring src);
/// @brief Compare two strings
/// @param str1 The first string
/// @param str2 The second string
/// @return True if the strings are equal
bool StringCompare(cstring str1, cstring str2);
/// @brief Reverse a string
/// @param str The string
/// @param len The length to reverse
void ReverseString(char *str, int len);
/// @brief Convert an integer to a string
/// @param value The integer
/// @return The string
char* ToString(int value);
/// @brief Convert a unsigned char to a string
/// @param value The unsigned char
/// @return The string
char* ToString(uint8_t value);
/// @brief Convert a unsigned short to a string
/// @param value The unsigned short
/// @return The string
char* ToString(uint16_t value);
/// @brief Convert a unsigned int to a string
/// @param value The unsigned int
/// @return The string
char* ToString(uint32_t value);
/// @brief Convert a unsigned long long to a string
/// @param value The unsigned long long
/// @return The string
char* ToString(uint64_t value);
/// @brief Convert a float to a string
/// @param value The float
/// @return The string
char* ToString(float value);
/// @brief Convert a double to a string
/// @param value The double
/// @return The string
char* ToString(double value);
/// @brief Convert a char to a string
/// @param value The char
/// @return The string
char* ToString(char value);
/// @brief Convert a bool to a string
/// @param value The bool
/// @return The string
char* ToString(bool value);
/// @brief Convert an integer to a string
/// @param value The integer
/// @param buffer The buffer
/// @return The string in hex
char* ToHexNumberString(int value);
/// @brief Convert a unsigned char to a string
/// @param value The unsigned char
/// @param buffer The buffer
/// @return The string in hex
char* ToHexNumberString(uint64_t value);
/// @brief Convert an integer to char
/// @param value The integer
/// @return The char
char ToCharacter(int value);