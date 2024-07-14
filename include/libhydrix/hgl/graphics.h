#pragma once
#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <libhydrix/hmath/intmath.h>
#include <libhydrix/hmath/floatmath.h>
#include <libhydrix/hstring/string.h>
#include <libhydrix/sdefs.h>
#include <libhydrix/hmem/smem/heap.h>
#include "fonts.h"
#include <stdint.h>
#include <stddef.h>
#include "color.h"
class Graphics {
    public:
        long* Font;
        volatile int GlyphWidth;
        volatile int GlyphHeight;
        volatile int FontLetterSpacing;
        volatile int BitmapFontSheetWidth;
        uint64_t Pitch;
        uint64_t Width;
        uint64_t Height;
        uint64_t Bpp;
        /// @brief The framebuffer (LIMINE Framebuffer)
        uint32_t* FrameBuffer;
        /// @brief The buffer to swap with
        uint32_t* SwapBuffer;
        /// @brief The constructor for the Graphics class
        Graphics();
        /// @brief Initialize the Graphics class
        /// @param fb The framebuffer
        void Init(uint32_t* fb, uint64_t width, uint64_t height, uint64_t pitch, uint64_t bpp);
        /// @brief Draw a pixel on the screen
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        inline void DrawPixelInline(int x, int y, int color);
        /// @brief Draw a pixel on the screen without inlining
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        void DrawPixel(int x, int y, int color);
        /// @brief Fill the screen with a color
        /// @param color The color
        void Clear(int color);
        /// @brief Clear the screen
        /// @note Fills the screen with black
        void Clear();
        /// @brief Draw a string on the screen
        /// @param str The string
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        void DrawString(char* str, int x, int y, int color);
        /// @brief Draw a char on the screen
        /// @param c The char
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        void DrawChar(char c, int x, int y, int color);
        /// @brief Draw a line on the screen
        /// @param x1 The horizontal position of the first point
        /// @param y1 The vertical position of the first point
        /// @param x2 The horizontal position of the second point
        /// @param y2 The vertical position of the second point
        /// @param color The color
        void DrawLine(int x1, int y1, int x2, int y2, int color);
        /// @brief Draw a rectangle on the screen
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param w The width
        /// @param h The height
        /// @param color The color
        void DrawRectangle(int x, int y, int w, int h, int color);
        /// @brief Draw a filled rectangle on the screen
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param w The width
        /// @param h The height
        /// @param color The color
        void DrawFilledRectangle(int x, int y, int w, int h, int color);
        /// @brief Draw a circle on the screen
        /// @param x0 The horizontal position of the center
        /// @param y0 The vertical position of the center
        /// @param radius The radius
        /// @param color The color
        void DrawCircle(int x0, int y0, int radius, int color);
        /// @brief Draw a filled circle on the screen
        /// @param x0 The horizontal position of the center
        /// @param y0 The vertical position of the center
        /// @param radius The radius
        /// @param color The color
        void DrawFilledCircle(int x0, int y0, int radius, int color);
        /// @brief Swap the buffer
        /// @warning MUST BE CALLED AFTER DRAWING FOR ANYTHING TO BE VISIBLE
        void Display();
        /// @brief Draws an image to the screen (bitmap)
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param image The bitmap image
        void DrawImage(int x, int y, BMPI Bimage);
        /// @brief Draws a pixel to the screen with transparency
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param color The color
        void DrawAlphaPixel(int x, int y, long color);
        /// @brief Draws an image to the screen (bitmap) with transparency
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param image The bitmap image
        void DrawAlphaImage(int x, int y, BMPA Bimage);
        /// @brief Draws an image to the screen (bitmap) with transparency
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param w The width
        /// @param h The height
        /// @param image The bitmap image
        void DrawStretchedImage(int x, int y, int w, int h, BMPI Bimage);
        /// @brief Draws an image to the screen (bitmap) with transparency
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @param w The width
        /// @param h The height
        /// @param image The bitmap image
        void DrawStretchedAlphaImage(int x, int y, int w, int h, BMPA Bimage);
        /// @brief Get a pixel from the screen
        /// @param x The horizontal position
        /// @param y The vertical position
        /// @return The color of the pixel
        inline int GetPixelFromScreen(int x, int y);
        /// @brief Load a font (Bitmap Sprite Sheet)
        /// @param font The font (Bitmap Sprite Sheet)
        /// @param glyph_width The width of a glyph (How wide the characters are)
        /// @param glyph_height The height of a glyph (How tall the characters are)
        /// @param font_char_width The width of a font character (How close the characters are to each other)
        /// @param font_sheet_width The width of the font sheet (Example: 256 for a 16x16 font sheet)
        void LoadFont(long* font, int glyph_width, int glyph_height, int font_char_width, int font_sheet_width);
};
