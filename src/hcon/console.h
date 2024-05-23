#pragma once
#include "../hstring/string.h"
#include <limine.h>
#include "../hgl/graphics.h"
class Console
{
    public:
        Graphics graphics;
        int currentline;
        int currentcolumn;
        int pxlinedown;
        void Write(string text);
        void WriteLine(string text);
        void Write(string text, int color);
        void WriteLine(string text, int color);
        void Clear();
        void ShiftUp(uint64_t* buffer, uint64_t width, uint64_t height);
};