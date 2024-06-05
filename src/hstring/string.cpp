#include "string.h"
#include "../hmem/smem/heap.h"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

char* strcat(cstring dest, cstring src) 
{
    //kalloc
    char* newstr = (char*)kalloc(strlen(dest) + strlen(src) + 1);
    int i = 0;
    int j = 0;
    while (dest[i] != '\0') {
        newstr[i] = dest[i];
        i++;
    }
    while (src[j] != '\0') {
        newstr[i] = src[j];
        i++;
        j++;
    }
    newstr[i] = '\0';
    return newstr;
}
void reverse(char *str, int len) {
    int start = 0;
    int end = len - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
char* int_to_string(int value) {
    bool isnegative = false;
    //if negative, set isnegative to true
    if (value < 0) {
        isnegative = true;
        value = -value;
    }
    static char buffer[32] = {0};
    int i = 30;
    //account for negative in first
    if (isnegative) {
        buffer[i--] = '-';
    }
    for(; value && i ; --i, value /= 10)
        buffer[i] = "0123456789"[value % 10];
    return &buffer[i+1];
}
int int_to_string(int value, char *buffer) {
    int i = 0;
    if (value == 0) {
        buffer[i++] = '0';
    } else {
        while (value != 0) {
            buffer[i++] = (value % 10) + '0';
            value /= 10;
        }
    }
    buffer[i] = '\0';
    reverse(buffer, i);
    return i;
}
char* u8_to_string(uint8_t value) {
    static char buffer[32] = {0};
    int i = 30;
    for(; value && i ; --i, value /= 10)
        buffer[i] = "0123456789"[value % 10];
    return &buffer[i+1];
}

char* u16_to_string(uint16_t value) {
    static char buffer[32] = {0};
    int i = 30;
    for(; value && i ; --i, value /= 10)
        buffer[i] = "0123456789"[value % 10];
    return &buffer[i+1];
}

char* u32_to_string(uint32_t value) {
    static char buffer[32] = {0};
    int i = 30;
    for(; value && i ; --i, value /= 10)
        buffer[i] = "0123456789"[value % 10];
    return &buffer[i+1];
}

char* u64_to_string(uint64_t value) {
    //if 0, return 0
    
    static char buffer[32] = {0};
    int i = 30;
    for(; value && i ; --i, value /= 10)
        buffer[i] = "0123456789"[value % 10];
    return &buffer[i+1];
}
//size_t
char* sizet_to_string(size_t value) {
    static char buffer[32] = {0};
    int i = 30;
    for(; value && i ; --i, value /= 10)
        buffer[i] = "0123456789"[value % 10];
    return &buffer[i+1];
}
char* float_to_string(float value) {
    static char buffer[64] = {0};
    int int_part = (int)value;
    float frac_part = value - (float)int_part;
    if (frac_part < 0) frac_part = -frac_part;
    
    int i = int_to_string(int_part, buffer);
    
    buffer[i++] = '.';
    
    // Convert fractional part to string
    for (int j = 0; j < 6; j++) { // Adjust precision as needed
        frac_part *= 10;
        int frac_int = (int)frac_part;
        buffer[i++] = frac_int + '0';
        frac_part -= frac_int;
    }
    
    buffer[i] = '\0';
    return buffer;
}
char* double_to_string(double value) {
    static char buffer[64] = {0};
    int int_part = (int)value;
    double frac_part = value - (double)int_part;
    if (frac_part < 0) frac_part = -frac_part;
    
    int i = int_to_string(int_part, buffer);
    
    buffer[i++] = '.';
    
    // Convert fractional part to string
    for (int j = 0; j < 6; j++) { // Adjust precision as needed
        frac_part *= 10;
        int frac_int = (int)frac_part;
        buffer[i++] = frac_int + '0';
        frac_part -= frac_int;
    }
    
    buffer[i] = '\0';
    return buffer;
}
char* char_to_string(char value) {
    static char buffer[2] = {0};
    buffer[0] = value;
    return buffer;
}
char* bool_to_string(bool value) {
    return value ? (char*)"true" : (char*)"false";
}
char* int_to_string_hex(int value) {
    static char buffer[32] = {0};
    int i = 30;
    for(; value && i ; --i, value /= 16)
        buffer[i] = "0123456789ABCDEF"[value % 16];
    return &buffer[i+1];
}
char int_to_char(int value) {
    if (value == 0) {
        return '0';
    }
    else if (value == 1) {
        return '1';
    }
    else if (value == 2) {
        return '2';
    }
    else if (value == 3) {
        return '3';
    }
    else if (value == 4) {
        return '4';
    }
    else if (value == 5) {
        return '5';
    }
    else if (value == 6) {
        return '6';
    }
    else if (value == 7) {
        return '7';
    }
    else if (value == 8) {
        return '8';
    }
    else if (value == 9) {
        return '9';
    }
    else {
        return '0';
    }
}
char* to_string(int value) {
    if (value == 0) {
        return "0";
    }
    return int_to_string(value);
}
char* to_string(uint8_t value) {
    if (value == 0) {
        return "0";
    }
    return u8_to_string(value);
}
char* to_string(uint16_t value) {
    if (value == 0) {
        return "0";
    }
    return u16_to_string(value);
}
char* to_string(uint32_t value) {
    if (value == 0) {
        return "0";
    }
    return u32_to_string(value);
}
char* to_string(uint64_t value) {
    if (value == 0) {
        return "0";
    }
    return u64_to_string(value);
}
char* to_string(float value) {
    if (value == 0.0f) {
        return "0.0";
    }
    return float_to_string(value);
}
char* to_string(double value) {
    if (value == 0.0) {
        return "0.0";
    }
    return double_to_string(value);
}
char* to_string(char value) {
    if (value == '0') {
        return "0";
    }
    return char_to_string(value);
}
char* to_string(bool value) {
    return bool_to_string(value);
}
char* to_string_hex(int value) {
    return int_to_string_hex(value);
}
char to_char(int value) {
    return int_to_char(value);
}