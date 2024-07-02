#include "keyboard.h"
#include "../hio/io.h"

Console* Keyboard_Console_IDT;
char LastScancode = 0;
//scancodemap
char scancodemap[58] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};
char upperscancode[58] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};
static inline bool GetKeyDown(char scancode)
{
    return inb(0x60) == scancode;
}
inline char getScancode()
{
    return inb(0x60);
}
bool AllowKeyboard = true;

void DisableKeyboard()
{
    AllowKeyboard = false;
}
void EnableKeyboard()
{
    AllowKeyboard = true;
}

void keyboard_handler(registers_t *r)
{
    if (!AllowKeyboard)
    {
        return;
    }
    char scancode = getScancode();
    if (scancode < 58 && GetKeyDown(scancode))
    {
        //if shift is pressed, capitalize, if backspace, send \b to console
        if (GetKeyDown(0x2A) || GetKeyDown(0x36))
        {
            if (!Keyboard_Console_IDT->allow_typing) return;
            Keyboard_Console_IDT->PutCharS(upperscancode[scancode]);
        }
        else if (scancode == 0x0E)
        {
            if (!Keyboard_Console_IDT->allow_typing) return;
            Keyboard_Console_IDT->PutCharS('\b');
        }
        else
        {
            if (!Keyboard_Console_IDT->allow_typing) return;
            Keyboard_Console_IDT->PutCharS(scancodemap[scancode]);
        }
    }
    //enter
    else if (scancode == 0x1C && GetKeyDown(scancode))
    {
        if (!Keyboard_Console_IDT->allow_typing) return;
        Keyboard_Console_IDT->PutCharS('\n');
    }
    LastScancode = scancode;
    return;
}

void Keyboard_Init(Console* console)
{
    Keyboard_Console_IDT = console;
}

uint64_t Keyboard_GetKey()
{
    return (uint64_t)LastScancode;
}
