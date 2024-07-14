#pragma once
#include <libhydrix/hstring/string.h>
#include <limine.h>
#include <libhydrix/hgl/graphics.h>

class Console
{       
    public:
        bool allow_typing = false;
        /// @brief Graphics object
        Graphics* graphics;
        /// @brief The Current Line
        int currentline;
        /// @brief The Current Column
        int currentcolumn;
        /// @brief How many pixels to move down
        int pxlinedown;
        void AdvanceColumn(int text_length);
        void CheckLineOverflow();
        void SetCursor(int x, int y);
        void PutChar(char c);
        void PutCharS(char c);
        void Write(string text);
        void WriteLine(string text);
        void Write(string text, int color);
        void WriteLine(string text, int color);
        void WriteS(string text);
        void WriteLineS(string text);
        void WriteS(string text, int color);
        void WriteLineS(string text, int color); //S means Swap
        void WriteLineA(string text, int color, ...); //Write Line Append
        void WriteLineA(string text, ...);
        void WriteLineAS(string text, int color, ...);
        void WriteLineAS(string text, ...);
        void Clear();
        void ClearS();
        void ShiftUp(uint64_t* buffer, uint64_t width, uint64_t height);
        void Init(Graphics* graphics, int pxlinedown, bool allow_typing);
};