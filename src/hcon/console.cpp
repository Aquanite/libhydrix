#include "console.h"

void Console::Write(string text)
{
    //use put_string
    if (currentcolumn >= graphics.framebuffer.width / 8)
    {
        currentline++;
        currentcolumn = 0;
    }
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, rgb(255, 255, 255));
    currentcolumn += strlen(text);
    if (currentline >= graphics.framebuffer.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer.address, graphics.framebuffer.width, graphics.framebuffer.height);
        currentline--;
        currentcolumn = 0;
    }
}
void Console::WriteLine(string text)
{
    //use put_string
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, rgb(255, 255, 255));
    currentline++;
    //calculate the new line using screen height and pxlinedown
    if (currentline >= graphics.framebuffer.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer.address, graphics.framebuffer.width, graphics.framebuffer.height);
        currentline--;
    }
    currentcolumn = 0;
}
//write color
void Console::Write(string text, int color)
{
    //use put_string
    //use currencolumn multiplied by the width of a character to write the text
    //if at the end of width/charracter width, go to the next line
    if (currentcolumn >= graphics.framebuffer.width / 8)
    {
        currentline++;
        currentcolumn = 0;
    }
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, color);
    currentcolumn += strlen(text);
    if (currentline >= graphics.framebuffer.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer.address, graphics.framebuffer.width, graphics.framebuffer.height);
        currentline--;
        currentcolumn = 0;
    }
}
//write color
void Console::WriteLine(string text, int color)
{
    //use put_string
    //use currencolumn multiplied by the width of a character to write the text
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, color);
    currentline++;
    //calculate the new line using screen height and pxlinedown
    if (currentline >= graphics.framebuffer.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer.address, graphics.framebuffer.width, graphics.framebuffer.height);
        currentline--;
    }
    currentcolumn = 0;
}
void Console::Clear()
{
    //use clear_screen
    graphics.clear();
    currentline = 0;
    currentcolumn = 0;
}

void Console::ShiftUp(uint64_t* buffer, uint64_t width, uint64_t height) {
    //shift up
    for (int y = 0; y < height - pxlinedown; y++)
    {
        for (int x = 0; x < width; x++)
        {
            buffer[y * width + x] = buffer[(y + (pxlinedown/2) + 1) * width + x];
        }
    }
    //clear the last line
    for (int y = height - pxlinedown; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            buffer[y * width + x] = 0;
        }
    }
}