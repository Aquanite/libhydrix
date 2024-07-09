#include <libhydrix/hmouse/mouse.h>
#include <libhydrix/hio/io.h>
#include <libhydrix/hdebug/serial.h>

#define MOUSE_ACK 0xFA
#define MOUSE_NACK 0xFE
#define MOUSE_ERROR 0xFC

Console *mouse_console;
static int sensitivity = 1; // Default sensitivity

static void mouse_wait(uint8_t type)
{
    uint32_t timeout = 100000;
    if (type == 0)
    {
        while (timeout--)
        {
            if ((inb(MOUSE_COMMAND) & 1) == 1)
            {
                return;
            }
        }
    }
    else
    {
        while (timeout--)
        {
            if ((inb(MOUSE_COMMAND) & 2) == 0)
            {
                return;
            }
        }
    }
}

static void mouse_write(uint8_t data)
{
    mouse_wait(1);
    outb(MOUSE_COMMAND, 0xD4);
    mouse_wait(1);
    outb(MOUSE_PORT, data);
}

static uint8_t mouse_read()
{
    mouse_wait(0);
    return inb(MOUSE_PORT);
}

uint8_t MouseID = 0;

uint8_t get_mouse_id()
{
    mouse_wait(1);
    outb(MOUSE_COMMAND, 0xD4);
    mouse_wait(1);
    outb(MOUSE_PORT, 0xF2);
    mouse_wait(0);
    return mouse_read();
}

void set_mouse_rate(uint8_t rate)
{
    mouse_wait(1);
    outb(MOUSE_COMMAND, 0xD4);
    mouse_wait(1);
    outb(MOUSE_PORT, 0xF3);
    mouse_wait(1);
    outb(MOUSE_PORT, rate);
}

void enable_mouse_z()
{
    set_mouse_rate(200);
    set_mouse_rate(100);
    set_mouse_rate(80);
    MouseID = get_mouse_id();
    DebugPrint(strcat("Mouse ID: ", to_string(MouseID)));
}

void resetmouse()
{
    mouse_wait(1);
    outb(MOUSE_COMMAND, 0xFF);
    mouse_read(); // Acknowledge
}

static void mouse_enable()
{
    // Reset the mouse
    resetmouse();
    outb(0xD4, 0x64);

    mouse_wait(1);
    outb(MOUSE_COMMAND, 0xA8);
    mouse_wait(1);
    outb(MOUSE_COMMAND, 0x20);
    uint8_t status = (inb(MOUSE_PORT) | 2);
    mouse_wait(1);
    outb(MOUSE_COMMAND, 0x60);
    mouse_wait(1);
    outb(MOUSE_PORT, status);
    mouse_write(0xF6);
    mouse_read(); // Acknowledge
    
    mouse_write(0xF4);
    mouse_read(); // Acknowledge
}

MouseState State;
MouseScrollState Scrolling;
uint8_t MouseScrollDelta;

MouseScroll Get_Mouse_Scroll()
{
    return (MouseScroll){Scrolling, MouseScrollDelta};
}

MouseState Get_Current_Mouse_State()
{
    return State;
}

void set_mouse_console(Console *console)
{
    mouse_console = console;
    mouse_enable();
}

void set_mouse_sensitivity(int new_sensitivity)
{
    sensitivity = new_sensitivity;
}

static uint8_t mouse_cycle = 0;
static int8_t mouse_byte[4];

static int32_t PrevMouseX = 0;
static int32_t PrevMouseY = 0;
static int32_t MouseX = 0;
static int32_t MouseY = 0;

int32_t get_mouse_x()
{
    return MouseX;
}

int32_t get_mouse_y()
{
    return MouseY;
}

void mouse_handler(registers_t *r)
{
    static int8_t x = 0;
    static int8_t y = 0;
    switch (mouse_cycle)
    {
        case 0:
            mouse_byte[0] = mouse_read();
            // Check if mouse left button is pressed
            if (mouse_byte[0] & 0x01) // Bit: 1
            {
                State = MOUSE_LEFT;
            }
            // Check if mouse right button is pressed
            else if (mouse_byte[0] & 0x02) // Bit: 2
            {
                State = MOUSE_RIGHT;
            }
            // Check if mouse middle button is pressed
            else if (mouse_byte[0] & 0x04) // Bit: 3
            {
                State = MOUSE_MIDDLE;
            }
            else
            {
                State = MOUSE_NONE;
            }
            mouse_cycle++;
            return;
        case 1:
            mouse_byte[1] = mouse_read();
            mouse_cycle++;
            return;
        case 2:
            mouse_byte[2] = mouse_read();

            x = mouse_byte[1];
            y = mouse_byte[2];
            if (MouseID != 3) mouse_cycle = 0;
            if (mouse_console)
            {
                uint64_t screenwidth = mouse_console->graphics->width;
                uint64_t screenheight = mouse_console->graphics->height;

                MouseX += (int)(x * sensitivity);
                MouseY -= (int)(y * sensitivity);

                // Clamp the mouse coordinates to the screen dimensions
                if (MouseX < 0) MouseX = 0;
                if (MouseX >= screenwidth) MouseX = screenwidth - 1;
                if (MouseY < 0) MouseY = 0;
                if (MouseY >= screenheight) MouseY = screenheight - 1;

                PrevMouseX = MouseX;
                PrevMouseY = MouseY;
            }
            break;
        case 3:
            // Scroll wheel
            mouse_byte[3] = mouse_read();
            MouseScrollDelta = mouse_byte[3];
            if (mouse_byte[3] > 0)
            {
                Scrolling = MOUSE_SCROLL_UP;
            }
            else if (mouse_byte[3] < 0)
            {
                Scrolling = MOUSE_SCROLL_DOWN;
            }
            mouse_cycle = 0;
            break;
    }
}
