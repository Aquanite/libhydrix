#include <libhydrix/hdebug/serial.h>
#include <libhydrix/hio/io.h>
#include <libhydrix/hdebug/serial.h>

void DebugPrint(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        outb(COM1, str[i]);
    }
}

/// @brief Halt the CPU and disable interrupts
void CLIHalt()
{
    asm("cli");
    for (;;)
    {
        asm("hlt");
    }
}
/// @brief Halt the CPU but keep interrupts enabled
void STIHalt()
{
    for (;;)
    {
        asm("hlt");
    }
}
// qemu arg for writing the serial output to a file: -serial file:serial.log