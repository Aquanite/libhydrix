#include <libhydrix/hcon/console.h>
#include <libhydrix/hio/io.h>
#include <libhydrix/hmem/smem/smem.h>



inline void Console::AdvanceColumn(int text_length) {
    currentcolumn += text_length;
    if (currentcolumn >= graphics->Width / 8) {
        currentcolumn = 0;
        currentline++;
    }
}

inline void Console::CheckLineOverflow() {
    if (currentline >= graphics->Height / pxlinedown) {
        ShiftUp((uint64_t*)graphics->FrameBuffer, graphics->Width, graphics->Height);
        currentline--;
    }
}

//set cursor
void Console::SetCursor(int x, int y) {
    currentcolumn = x;
    currentline = y;
}

void Console::PutChar(char c)
{
    //check if enter
    if (c == 0x1c)
    {
        //if enter, go to the next line
        currentline++;
        currentcolumn = 0;
    }

    if (c == '\n')
    {
        currentline++;
        currentcolumn = 0;
        CheckLineOverflow();
        return;
    }
    else if (c == '\b')
    {
        if (currentline == 0 && currentcolumn == 0) return;
        //draw a black rectangle to cover the character the same size as the character, use GlyphWidth, GRAPHICS_StringGlyphHeight, GRAPHICS_StringFontCharWidth, GRAPHICS_FontSheetWidth, use graphics->put_filled_rect
        //get offset of the area Minimumus the char spacing and the char width
        //get the x and y of the char
        //get the char offset
        //for each pixel in the char, if the pixel is not 0, put a pixel at the x and y of the char with the color 0
        //if the current column is 0, go to the previous line
        //else go to the previous column
        int x = (currentcolumn * 8) + 1;
        int y = currentline * pxlinedown;
        graphics->DrawFilledRectangle(x, y, graphics->GlyphWidth, pxlinedown, 0);
        if (currentcolumn == 0)
        {
            currentline--;
            currentcolumn = graphics->Width / 8 - 1;
        }
        else
        {
            currentcolumn--;
        }

    }
    else
    {
        if (c < 32 || c > 126) return;
        graphics->DrawChar(c, (currentcolumn * 8) + 1, currentline * pxlinedown, IColor::RGB(255, 255, 255));
        AdvanceColumn(1);
        CheckLineOverflow();
    }
}

void Console::PutCharS(char c)
{
    PutChar(c);
    graphics->Display();
}

void Console::Write(string text) {
    graphics->DrawString(text, (currentcolumn * 8) + 1, currentline * pxlinedown, IColor::RGB(255, 255, 255));
    AdvanceColumn(StringLength(text));
    CheckLineOverflow();
}

void Console::WriteLine(string text) {
    graphics->DrawString(text, (currentcolumn * 8) + 1, currentline * pxlinedown, IColor::RGB(255, 255, 255));
    currentline++;
    CheckLineOverflow();
    currentcolumn = 0;
}

void Console::Write(string text, int color) {
    graphics->DrawString(text, (currentcolumn * 8) + 1, currentline * pxlinedown, color);
    AdvanceColumn(StringLength(text));
    CheckLineOverflow();
}

void Console::WriteLine(string text, int color) {
    graphics->DrawString(text, (currentcolumn * 8) + 1, currentline * pxlinedown, color);
    currentline++;
    CheckLineOverflow();
    currentcolumn = 0;
}

void Console::WriteS(string text) {
    Write(text);
    graphics->Display();
}

void Console::WriteLineS(string text) {
    WriteLine(text);
    graphics->Display();
}

void Console::WriteS(string text, int color) {
    Write(text, color);
    graphics->Display();
}

void Console::WriteLineS(string text, int color) {
    WriteLine(text, color);
    graphics->Display();
}

void Console::WriteLineA(string text, int color, ...) {
    //use StringConcatenate to append the strings
    va_list args;
    va_start(args, color);
    string newtext = text;
    string arg = va_arg(args, string);
    while (!StringCompare(arg, "")) {
        newtext = StringConcatenate(newtext, arg);
        arg = va_arg(args, string);
    }
    va_end(args);
    WriteLine(newtext, color);
}

void Console::WriteLineA(string text, ...) {
    va_list args;
    va_start(args, text);
    string newtext = text;
    string arg = va_arg(args, string);
    while (!StringCompare(arg, "")) {
        newtext = StringConcatenate(newtext, arg);
        arg = va_arg(args, string);
    }
    va_end(args);
    WriteLine(newtext);
}

void Console::WriteLineAS(string text, int color, ...) {
    va_list args;
    va_start(args, color);
    string newtext = text;
    string arg = va_arg(args, string);
    while (!StringCompare(arg, "")) {
        newtext = StringConcatenate(newtext, arg);
        arg = va_arg(args, string);
    }
    va_end(args);
    WriteLineS(newtext, color);
}

void Console::WriteLineAS(string text, ...) {
    va_list args;
    va_start(args, text);
    string newtext = text;
    string arg = va_arg(args, string);
    while (!StringCompare(arg, "")) {
        newtext = StringConcatenate(newtext, arg);
        arg = va_arg(args, string);
    }
    va_end(args);
    WriteLineS(newtext);
}

void Console::Clear() {
    graphics->Clear();
    currentline = 0;
    currentcolumn = 0;
}

void Console::ClearS() {
    Clear();
    graphics->Display();
}

void Console::ShiftUp(uint64_t* buffer, uint64_t width, uint64_t height) {
    size_t row_size = width * sizeof(uint64_t);
    memmove(buffer, buffer + (pxlinedown * width / 2), (height - pxlinedown / 2) * row_size);
    memset(buffer + (height - pxlinedown / 2) * width, 0, (pxlinedown / 2) * row_size);
}

void Console::Init(Graphics *graphics, int pxlinedown, bool allow_typing)
{
    this->graphics = graphics;
    this->pxlinedown = pxlinedown;
    this->allow_typing = allow_typing;
    currentline = 0;
    currentcolumn = 0;
    Clear();
}
