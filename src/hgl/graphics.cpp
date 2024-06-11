#include "graphics.h"
#include <stdint.h>
#include <stddef.h>
#include "../hmem/smem/smem.h"

// Graphics class constructor
Graphics::Graphics() {}

// Global variables for font properties
int StringGlyphWidth;
int StringGlyphHeight;
int StringFontCharWidth;
int FontSheetWidth;

void Graphics::initgmgr(uint32_t* fb, uint64_t width, uint64_t height, uint64_t pitch) {
    this->framebuffer = fb;
    this->width = width;
    this->height = height;
    this->pitch = pitch;
    StringFont = (long*)CourierNew;
    StringGlyphWidth = COURIERNEW_GLYPH_WIDTH;
    StringGlyphHeight = COURIERNEW_GLYPH_HEIGHT;
    StringFontCharWidth = COURIERNEW_GLYPH_SPACE;
    FontSheetWidth = COURIERNEW_WIDTH;
    SwapBuffer = (uint32_t*)(fb + width * height);
}

inline void Graphics::put_pixel(int x, int y, int color) {
    if (x < width && y < height) {
        SwapBuffer[y * (pitch / 4) + x] = color;
    }
}

void Graphics::fill_screen(int color) {
    uint32_t *fb_ptr = SwapBuffer;
    for (uint64_t y = 0; y < height; ++y) {
        for (uint64_t x = 0; x < width; ++x) {
            fb_ptr[y * (pitch / 4) + x] = color;
        }
    }
}

void Graphics::clear() {
    fill_screen(0);
}

void Graphics::put_char(char c, int x, int y, int color) {
    const int glyph_width = StringGlyphWidth;
    const int glyph_height = StringGlyphHeight;
    const int image_width = FontSheetWidth;

    int char_index = c - 32;
    int char_x = char_index % 16;
    int char_y = char_index / 16;
    int char_offset = char_y * glyph_height * image_width + char_x * glyph_width;

    for (int i = 0; i < glyph_height; ++i) {
        for (int j = 0; j < glyph_width; ++j) {
            int pixel = StringFont[char_offset + i * image_width + j];
            if (pixel != 0) {
                put_pixel(x + j, y + i, color);
            }
        }
    }
}

void Graphics::put_string(char *str, int x, int y, int color) {
    for (size_t i = 0; i < strlen(str); ++i) {
        put_char(str[i], x + i * StringFontCharWidth, y, color);
    }
}

void Graphics::put_line(int x1, int y1, int x2, int y2, int color) {
    int dx = MathI::abs(x2 - x1);
    int dy = MathI::abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (true) {
        put_pixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }
}

void Graphics::put_rect(int x, int y, int w, int h, int color) {
    put_line(x, y, x + w, y, color);
    put_line(x, y, x, y + h, color);
    put_line(x + w, y, x + w, y + h, color);
    put_line(x, y + h, x + w, y + h, color);
}

void Graphics::put_filled_rect(int x, int y, int w, int h, int color) {
    for (int i = 0; i < h; ++i) {
        put_line(x, y + i, x + w, y + i, color);
    }
}

void Graphics::put_circle(int x0, int y0, int radius, int color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        put_pixel(x0 + x, y0 + y, color);
        put_pixel(x0 + y, y0 + x, color);
        put_pixel(x0 - y, y0 + x, color);
        put_pixel(x0 - x, y0 + y, color);
        put_pixel(x0 - x, y0 - y, color);
        put_pixel(x0 - y, y0 - x, color);
        put_pixel(x0 + y, y0 - x, color);
        put_pixel(x0 + x, y0 - y, color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void Graphics::put_filled_circle(int x0, int y0, int radius, int color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        put_line(x0 - x, y0 + y, x0 + x, y0 + y, color);
        put_line(x0 - y, y0 + x, x0 + y, y0 + x, color);
        put_line(x0 - x, y0 - y, x0 + x, y0 - y, color);
        put_line(x0 - y, y0 - x, x0 + y, y0 - x, color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void Graphics::Swap() {
    memcpy(framebuffer, SwapBuffer, width * height * sizeof(uint32_t));
}

void Graphics::put_image(int x, int y, BMPI Bimage) {
    for (int i = 0; i < Bimage.height; ++i) {
        memcpy(SwapBuffer + (y + i) * (pitch / 4) + x, Bimage.data + i * Bimage.width, Bimage.width * sizeof(uint32_t));
    }
}

void Graphics::put_pixel_alpha(int x, int y, long color) {
    if ((color & 0xFF) == 0x00) return;

    uint32_t *fb_ptr = SwapBuffer;
    int pixel = fb_ptr[y * (pitch / 4) + x];
    int r = (color & 0xFF0000) >> 16;
    int g = (color & 0xFF00) >> 8;
    int b = (color & 0xFF);
    int a = (color & 0xFF000000) >> 24;
    int r2 = (pixel & 0xFF0000) >> 16;
    int g2 = (pixel & 0xFF00) >> 8;
    int b2 = (pixel & 0xFF);
    int a2 = (pixel & 0xFF000000) >> 24;
    int r3 = (r * a + r2 * (255 - a)) / 255;
    int g3 = (g * a + g2 * (255 - a)) / 255;
    int b3 = (b * a + b2 * (255 - a)) / 255;
    int a3 = (a * a + a2 * (255 - a)) / 255;
    fb_ptr[y * (pitch / 4) + x] = (a3 << 24) | (r3 << 16) | (g3 << 8) | b3;
}

void Graphics::put_image_alpha(int x, int y, BMPA Bimage) {
    for (int i = 0; i < Bimage.height; ++i) {
        for (int j = 0; j < Bimage.width; ++j) {
            put_pixel_alpha(x + j, y + i, Bimage.data[i * Bimage.width + j]);
        }
    }
}

inline int Graphics::get_pixel(int x, int y) {
    return SwapBuffer[y * (pitch / 4) + x];
}

void Graphics::load_font(long *font, int glyph_width, int glyph_height, int font_char_width, int font_sheet_width) {
    memcpy(StringFont, font, font_sheet_width * font_sheet_width * sizeof(long));
    StringGlyphWidth = glyph_width;
    StringGlyphHeight = glyph_height;
    StringFontCharWidth = font_char_width;
    FontSheetWidth = font_sheet_width;
}

inline void get_pixel_from_bitmap(long *bmpdata, int x, int y, int width, int height, int *color) {
    *color = bmpdata[y * width + x];
}
