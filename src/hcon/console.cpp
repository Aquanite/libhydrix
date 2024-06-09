#include "console.h"
#include "../hio/io.h"
/// @brief Write text to the console
/// @param text The text to write
/// @note This function does not swap the buffer, it will NOT be displayed until the buffer is swapped
void Console::Write(string text)
{
    //use put_string
    if (currentcolumn >= graphics.width / 8)
    {
        currentline++;
        currentcolumn = 0;
    }
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, rgb(255, 255, 255));
    currentcolumn += strlen(text);
    if (currentline >= graphics.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
        currentcolumn = 0;
    }
}
/// @brief Write a line of text to the console
/// @param text The text to write
/// @note This function does not swap the buffer, it will NOT be displayed until the buffer is swapped
void Console::WriteLine(string text)
{
    //use put_string
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, rgb(255, 255, 255));
    currentline++;
    //calculate the new line using screen height and pxlinedown
    if (currentline >= graphics.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
    }
    currentcolumn = 0;
}
/// @brief Write text to the console with a color
/// @param text The text to write
/// @param color The color of the text
/// @note This function does not swap the buffer, it will NOT be displayed until the buffer is swapped
void Console::Write(string text, int color)
{
    //use put_string
    //use currencolumn multiplied by the width of a character to write the text
    //if at the end of width/charracter width, go to the next line
    if (currentcolumn >= graphics.width / 8)
    {
        currentline++;
        currentcolumn = 0;
    }
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, color);
    currentcolumn += strlen(text);
    if (currentline >= graphics.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
        currentcolumn = 0;
    }
}
/// @brief Write a line of text to the console
/// @param text The text to write
/// @param color The color of the text
/// @note This function does not swap the buffer, it will NOT be displayed until the buffer is swapped
void Console::WriteLine(string text, int color)
{
    //use put_string
    //use currencolumn multiplied by the width of a character to write the text
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, color);
    currentline++;
    //calculate the new line using screen height and pxlinedown
    if (currentline >= graphics.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
    }
    currentcolumn = 0;
}
/// @brief Write text to the console and swap the buffer
/// @param text The text to write
void Console::WriteS(string text)
{
    //use put_string
    //use currencolumn multiplied by the width of a character to write the text
    //if at the end of width/charracter width, go to the next line
    if (currentcolumn >= graphics.width / 8)
    {
        currentline++;
        currentcolumn = 0;
    }
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, rgb(255, 255, 255));
    currentcolumn += strlen(text);
    if (currentline >= graphics.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
        currentcolumn = 0;
    }
    graphics.Swap();
}
/// @brief Write a line of text to the console and swap the buffer
/// @param text The text to write
void Console::WriteLineS(string text)
{
    //use put_string
    //use currencolumn multiplied by the width of a character to write the text
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, rgb(255, 255, 255));
    currentline++;
    //calculate the new line using screen height and pxlinedown
    if (currentline >= graphics.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
    }
    currentcolumn = 0;
    graphics.Swap();
}
/// @brief Write text to the console with a color and swap the buffer
/// @param text The text to write
/// @param color The color of the text
void Console::WriteS(string text, int color)
{
    //use put_string
    //use currencolumn multiplied by the width of a character to write the text
    //if at the end of width/charracter width, go to the next line
    if (currentcolumn >= graphics.width / 8)
    {
        currentline++;
        currentcolumn = 0;
    }
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, color);
    currentcolumn += strlen(text);
    if (currentline >= graphics.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
        currentcolumn = 0;
    }
    graphics.Swap();
}
/// @brief Write a line of text to the console and swap the buffer
/// @param text The text to write
/// @param color The color of the text
void Console::WriteLineS(string text, int color)
{
    //use put_string
    //use currencolumn multiplied by the width of a character to write the text
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline*pxlinedown, color);
    currentline++;
    //calculate the new line using screen height and pxlinedown
    if (currentline >= graphics.height / pxlinedown)
    {
        //shift up
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
    }
    currentcolumn = 0;
    graphics.Swap();
}
/// @brief Clear the console
/// @note This function does not swap the buffer, it will NOT be displayed until the buffer is swapped
void Console::Clear()
{
    //use clear_screen
    graphics.clear();
    currentline = 0;
    currentcolumn = 0;
}
/// @brief Clear the console and swap the buffer
void Console::ClearS()
{
    //use clear_screen
    graphics.clear();
    currentline = 0;
    currentcolumn = 0;
    graphics.Swap();
}
/// @brief Shift the buffer up
/// @param buffer The buffer to shift
/// @param width The width of the buffer
/// @param height The height of the buffer
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