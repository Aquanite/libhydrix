#include "serial.h"
#include "../hio/io.h"

void DebugPrint(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        outb(COM1, str[i]);
    }
}

//qemu arg for writing the serial output to a file: -serial file:serial.log