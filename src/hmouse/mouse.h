#pragma once
#include "../hcon/console.h"
#include <stdint.h>
#include "../hlow/cpu/cpu.h"
#define MOUSE_IRQ 12
#define MOUSE_PORT 0x60
#define MOUSE_COMMAND 0x64

typedef enum MouseState_E
{

    MOUSE_NONE = 0,
    MOUSE_LEFT = 1,
    MOUSE_RIGHT = 2,
    MOUSE_MIDDLE = 3,
} MouseState;

typedef enum MouseScrollState
{
    MOUSE_SCROLL_UP = 4,
    MOUSE_SCROLL_DOWN = 5,
} MouseScrollState;

typedef struct MouseScroll
{
    MouseScrollState State;
    uint8_t Delta;
} MouseScroll;


MouseScroll Get_Mouse_Scroll();
MouseState Get_Current_Mouse_State();
void set_mouse_console(Console *console);
void mouse_handler(registers_t *r);
void set_mouse_sensitivity(int new_sensitivity);
uint32_t get_mouse_x();
uint32_t get_mouse_y();
uint64_t Mouse_GetPos();