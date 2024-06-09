#pragma once
#include <limine.h>
#include "../hmath/intmath.h"
#include "../hmath/floatmath.h"
#include "../hstring/string.h"
#include "../sdefs.h"
#include "../hmem/smem/heap.h"
#include "fonts.h"
#include <stdint.h>
#include <stddef.h>
#include "color.h"
class Graphics {
    public:
        long* StringFont;
        
        uint64_t pitch;
        uint64_t width;
        uint64_t height;

        /// @brief The framebuffer (Limine Framebuffer)
        uint32_t* framebuffer;
        /// @brief The buffer to swap with
        uint32_t* SwapBuffer;
        /// @brief The constructor for the Graphics class
        Graphics();
        /// @brief Initialize the Graphics class
        /// @param fb The framebuffer
        /// @warning THIS FUNCTION WILL CAUSE A TRIPLE FAULT, PLEASE MANUALLY SET THE FRAMEBUFFER
        void initgmgr(uint32_t* fb, uint64_t width, uint64_t height, uint64_t pitch);
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
        /// @brief Draws an image to the screen (bitmap)
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param image The bitmap image
        void put_image(int x, int y, BMPI Bimage);
        /// @brief Draws a pixel to the screen with transparency
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        void put_pixel_alpha(int x, int y, long color);
        /// @brief Draws an image to the screen (bitmap) with transparency
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param image The bitmap image
        void put_image_alpha(int x, int y, BMPA Bimage);
        /// @brief Get a pixel from the screen
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @return The color of the pixel
        int get_pixel(int x, int y);
        /// @brief Load a font (Bitmap Sprite Sheet)
        /// @param font The font (Bitmap Sprite Sheet)
        /// @param glyph_width The width of a glyph (How wide the characters are)
        /// @param glyph_height The height of a glyph (How tall the characters are)
        /// @param font_char_width The width of a font character (How close the characters are to each other)
        /// @param font_sheet_width The width of the font sheet (Example: 256 for a 16x16 font sheet)
        void load_font(long* font, int glyph_width, int glyph_height, int font_char_width, int font_sheet_width);

};
