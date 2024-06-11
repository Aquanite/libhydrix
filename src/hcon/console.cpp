#include "console.h"
#include "../hio/io.h"
#include "../hmem/smem/smem.h"

inline void Console::advance_column(int text_length) {
    currentcolumn += text_length;
    if (currentcolumn >= graphics.width / 8) {
        currentcolumn = 0;
        currentline++;
    }
}

inline void Console::check_line_overflow() {
    if (currentline >= graphics.height / pxlinedown) {
        ShiftUp((uint64_t*)graphics.framebuffer, graphics.width, graphics.height);
        currentline--;
    }
}

//set cursor
void Console::SetCursor(int x, int y) {
    currentcolumn = x;
    currentline = y;
}

void Console::Write(string text) {
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline * pxlinedown, rgb(255, 255, 255));
    advance_column(strlen(text));
    check_line_overflow();
}

void Console::WriteLine(string text) {
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline * pxlinedown, rgb(255, 255, 255));
    currentline++;
    check_line_overflow();
    currentcolumn = 0;
}

void Console::Write(string text, int color) {
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline * pxlinedown, color);
    advance_column(strlen(text));
    check_line_overflow();
}

void Console::WriteLine(string text, int color) {
    graphics.put_string(text, (currentcolumn * 8) + 1, currentline * pxlinedown, color);
    currentline++;
    check_line_overflow();
    currentcolumn = 0;
}

void Console::WriteS(string text) {
    Write(text);
    graphics.Swap();
}

void Console::WriteLineS(string text) {
    WriteLine(text);
    graphics.Swap();
}

void Console::WriteS(string text, int color) {
    Write(text, color);
    graphics.Swap();
}

void Console::WriteLineS(string text, int color) {
    WriteLine(text, color);
    graphics.Swap();
}

void Console::Clear() {
    graphics.clear();
    currentline = 0;
    currentcolumn = 0;
}

void Console::ClearS() {
    Clear();
    graphics.Swap();
}

void Console::ShiftUp(uint64_t* buffer, uint64_t width, uint64_t height) {
    size_t row_size = width * sizeof(uint64_t);
    memmove(buffer, buffer + (pxlinedown * width / 2), (height - pxlinedown / 2) * row_size);
    memset(buffer + (height - pxlinedown / 2) * width, 0, (pxlinedown / 2) * row_size);
}
