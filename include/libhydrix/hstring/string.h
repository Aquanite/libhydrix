#pragma once
#include <stdint.h>
#include <stddef.h>
#include <libhydrix/hmem/smem/heap.h>

//include va list
#include <stdarg.h>


typedef char* string;
typedef const char* cstring;

/// @brief String length
/// @param str The string
/// @return The length
size_t StringLength(const char* str);
/// @brief Concatenate two strings
/// @param dest The destination
/// @param src The source
/// @return The new string
char* StringConcatenate(const char* dest, const char* src);
/// @brief Compare two strings
/// @param str1 The first string
/// @param str2 The second string
/// @return True if the strings are equal
bool StringCompare(const char* str1, const char* str2);
/// @brief Copy a string
/// @param dest The destination
/// @param src The source
void StringCopy(char* dest, const char* src);
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


class StringObj {
private:
    char* str;
    size_t len;

public:
    //Allow [] operator
    char& operator[](size_t index) {
        return str[index];
    }
    int Length() const {
        return len;
    }
    // Constructors
    explicit StringObj(const char* initialStr) {
        len = StringLength(initialStr);
        str = (char*)KernelAllocate(len + 1);
        StringCopy(str, initialStr);
    }

    // Copy constructor
    StringObj(const StringObj& other) {
        len = other.len;
        str = (char*)KernelAllocate(len + 1);
        StringCopy(str, other.str);
    }

    // Move constructor
    StringObj(StringObj&& other) : str(other.str), len(other.len) {
        other.str = 0;
        other.len = 0;
    }

    // Assignment operators
    StringObj& operator=(const char* newStr) {
        if (this->str != newStr) {
            //free with the byte lengh
            KernelFree(str);
            len = StringLength(newStr);
            str = (char*)KernelAllocate(len + 1);
            StringCopy(str, newStr);
        }
        return *this;
    }

    StringObj& operator=(const StringObj& other) {
        if (this != &other) {
            KernelFree(str);
            len = other.len;
            str = (char*)KernelAllocate(len + 1);
            StringCopy(str, other.str);
        }
        return *this;
    }
    // = then string
    StringObj& operator=(StringObj&& other) {
        if (this != &other) {
            KernelFree(str);
            len = other.len;
            str = other.str;
            other.str = 0;
            other.len = 0;
        }
        return *this;
    }

    //equal string
    bool operator==(const StringObj& rhs) const {
        return StringCompare(str, rhs.str);
    }

    // Not equal string
    bool operator!=(const StringObj& rhs) const {
        return !(*this == rhs);
    }

    // Concatenation operators
    StringObj operator+(const char* rhs) const {
        char* newStr = StringConcatenate(str, rhs);
        StringObj result(newStr);
        KernelFree(newStr);
        return result;
    }

    StringObj operator+(char* rhs) const {
        return *this + (const char*)rhs;
    }

    StringObj operator+(const StringObj& rhs) const {
        return *this + (const char*)rhs.str;
    }

    // Handling integer concatenation
    template<typename T>
    StringObj operator+(T rhs) const {
        char* newStr = StringConcatenate(str, ToString(rhs));
        StringObj result(newStr);
        KernelFree(newStr);
        return result;
    }

    // Type cast operators
    explicit operator const char*() const {
        return str;
    }

    // Destructor
    ~StringObj() {
        if (str) {
            KernelFree(str);
        }
    }
};


