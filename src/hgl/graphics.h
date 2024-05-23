#pragma once
#include <limine.h>
#include "../hmath/intmath.h"
#include "../hmath/floatmath.h"
#include "../hstring/string.h"
#include <stdint.h>
#include <stddef.h>
#include "color.h"
class Graphics {
    public:
        limine_framebuffer framebuffer;
        uint32_t* SwapBuffer;
        Graphics();
        void init(limine_framebuffer fb);
        void put_pixel(int x, int y, int color);
        void fill_screen(int color);
        void zero_clear();
        void put_string(char* str, int x, int y, int color);
        void clear();
        void put_char(char c, int x, int y, int color);
        void put_line(int x1, int y1, int x2, int y2, int color);
        //void put_line_gradient(int x1, int y1, int x2, int y2, int color1, int color2)
        void put_rect(int x, int y, int w, int h, int color);
        void put_filled_rect(int x, int y, int w, int h, int color);
        void put_circle(int x0, int y0, int radius, int color);
        void put_filled_circle(int x0, int y0, int radius, int color);
        void Swap();
};
