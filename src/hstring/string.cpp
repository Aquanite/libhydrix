#include "string.h"
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}
//strcat
char* strcat(cstring dest, cstring src) {
    char *ptr = {0}; // Initialize ptr to null
    while (*ptr) {
        ptr++;
    }
    while (*src) {
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';
    return (char*)dest;
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
char* to_string(int value) {
    return int_to_string(value);
}
char* to_string(uint8_t value) {
    return u8_to_string(value);
}
char* to_string(uint16_t value) {
    return u16_to_string(value);
}
char* to_string(uint32_t value) {
    return u32_to_string(value);
}
char* to_string(uint64_t value) {
    return u64_to_string(value);
}
char* to_string(float value) {
    return float_to_string(value);
}
