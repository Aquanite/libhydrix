#pragma once
#include "../hstring/string.h"
#include <limine.h>
#include "../hgl/graphics.h"
class Console
{
    public:
        /// @brief Graphics object
        Graphics graphics;
        /// @brief The Current Line
        int currentline;
        /// @brief The Current Column
        int currentcolumn;
        /// @brief How many pixels to move down
        int pxlinedown;
        void advance_column(int text_length);
        void check_line_overflow();
        void SetCursor(int x, int y);
        void Write(string text);
        void WriteLine(string text);
        void Write(string text, int color);
        void WriteLine(string text, int color);
        void WriteS(string text);
        void WriteLineS(string text);
        void WriteS(string text, int color);
        void WriteLineS(string text, int color); //S means Swap
        void Clear();
        void ClearS();
        void ShiftUp(uint64_t* buffer, uint64_t width, uint64_t height);
};