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
        /// @brief The framebuffer (Limine Framebuffer)
        limine_framebuffer framebuffer;
        /// @brief The buffer to swap with
        uint32_t* SwapBuffer;
        /// @brief The constructor for the Graphics class
        Graphics();
        /// @brief Initialize the Graphics class
        /// @param fb The framebuffer
        /// @warning THIS FUNCTION WILL CAUSE A TRIPLE FAULT, PLEASE MANUALLY SET THE FRAMEBUFFER
        void init(limine_framebuffer fb);
        /// @brief Put a pixel on the screen
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        void put_pixel(int x, int y, int color);
        /// @brief Fill the screen with a color
        /// @param color The color
        void fill_screen(int color);
        /// @brief Put a string on the screen
        /// @param str The string
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        void put_string(char* str, int x, int y, int color);
        /// @brief Clear the screen
        /// @note Fills the screen with black
        void clear();
        /// @brief Put a char on the screen
        /// @param c The char
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        void put_char(char c, int x, int y, int color);
        /// @brief Put a line on the screen
        /// @param x1 The horizontal position of the first point
        /// @param y1 The vertical position of the first point
        /// @param x2 The horizontal position of the second point
        /// @param y2 The vertical position of the second point
        /// @param color The color
        void put_line(int x1, int y1, int x2, int y2, int color);
        /// @brief Put a rectangle on the screen
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param w The width
        /// @param h The height
        /// @param color The color
        void put_rect(int x, int y, int w, int h, int color);
        /// @brief Put a filled rectangle on the screen
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param w The width
        /// @param h The height
        /// @param color The color
        void put_filled_rect(int x, int y, int w, int h, int color);
        /// @brief Put a circle on the screen
        /// @param x0 The horizontal position of the center
        /// @param y0 The vertical position of the center
        /// @param radius The radius
        /// @param color The color
        void put_circle(int x0, int y0, int radius, int color);
        /// @brief Put a filled circle on the screen
        /// @param x0 The horizontal position of the center
        /// @param y0 The vertical position of the center
        /// @param radius The radius
        /// @param color The color
        void put_filled_circle(int x0, int y0, int radius, int color);
        /// @brief Swap the buffer
        /// @warning MUST BE CALLED AFTER DRAWING FOR ANYTHING TO BE VISIBLE
        void Swap();
};
