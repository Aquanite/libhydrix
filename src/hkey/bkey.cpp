#include "bkey.h"
//make a function pointer that requires a uint8_t as an argument
key_handler_t handler;
void Keyboard_Handler()
{
    // Read from the keyboard's data buffer
    uint8_t scancode = inb(KEYBOARD_IO_PORT);
    // Call the function pointer with the scancode as an argument
    handler(scancode);
}
void Set_Handler_Keyboard(key_handler_t h)
{
    handler = h;
}
void Send_Command_Keyboard(uint8_t cmd)
{
    // Wait for the input buffer to be empty
    while (inb(KEYBOARD_STATUS_PORT) & 0x02)
        ;
    // Send the command
    outb(KEYBOARD_IO_PORT, cmd);
}
//tell keyboard that it can send data
void Keyboard_Enable()
{
    Send_Command_Keyboard(0xF4);
}

void Wait_For_Key()
{
    uint8_t currentscancode = inb(KEYBOARD_IO_PORT);
    while (inb(KEYBOARD_IO_PORT) == currentscancode)
    {
        //do nothing
    }
    return;
}
