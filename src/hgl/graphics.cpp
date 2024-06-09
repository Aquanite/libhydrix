#include "graphics.h"
#include <stdint.h>
#include <stddef.h>
#include "../hmem/smem/smem.h"
//graphics::graphics
Graphics::Graphics() {
}
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
    //set to width * height + address of framebuffer
    SwapBuffer = (uint32_t*)(fb + width * height);
    return;
}
void Graphics::put_pixel(int x, int y, int color) {
    if (x >= width || y >= height) return;
    volatile uint32_t *fb_ptr = static_cast<volatile uint32_t *>(SwapBuffer);
    fb_ptr[y * (pitch / 4) + x] = color;
}
void Graphics::fill_screen(int color) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            put_pixel(x, y, color);
        }
    }
}
int GetOffsetFromText(string str)
{
    //get pixel offset per char and add
    int len = strlen(str);
    return len * 10;
}
void Graphics::clear() {
    fill_screen(0);
}
void Graphics::put_char(char c, int x, int y, int color)
{
    // Assume each character is 16x16 pixels
    const int glyph_width = StringGlyphWidth;
    const int glyph_height = StringGlyphHeight;
    const int image_width = FontSheetWidth;

    // Pointer to the start of the font data

    int xpos = 0, ypos = 0;
    // Split all the characters into multiple 16x16 images
    int char_index = c - 32;
    // Modulo with StringGlyphWidth to get the x position of the character
    int char_x = char_index % 16;
    int char_y = char_index / 16;
    int char_offset = char_y * glyph_height * image_width + char_x * glyph_width;

    // Draw the character
    for (int i = 0; i < glyph_height; i++) {
        for (int j = 0; j < glyph_width; j++) {
            int pixel = StringFont[char_offset + i * image_width + j];
            if (pixel != 0) {
                put_pixel(x + xpos + j, y + ypos + i, color);
            }
        }
    }
}


void Graphics::put_string(char *str, int x, int y, int color)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
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
    for (int i = 0; i < h; i++) {
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
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
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
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}
void Graphics::Swap()
{
    //put all the SwapBuffer data into the framebuffer
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            volatile uint32_t *fb_ptr = static_cast<volatile uint32_t *>(framebuffer);
            fb_ptr[y * (pitch / 4) + x] = SwapBuffer[y * (pitch / 4) + x];
        }
    }
}

void Graphics::put_image(int x, int y, BMPI Bimage)
{
    int width = Bimage.width;
    int height = Bimage.height;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            put_pixel(x + j, y + i, Bimage.data[i * width + j]);
        }
    }
}

void Graphics::put_pixel_alpha(int x, int y, long color)
{
    if ((color & 0xFF) == 0x00) {
        return;
    }
    //get pixel below the alpha pixel and blend
    volatile uint32_t *fb_ptr = static_cast<volatile uint32_t *>(SwapBuffer);
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

void Graphics::put_image_alpha(int x, int y, BMPA Bimage)
{
    int width = Bimage.width;
    int height = Bimage.height;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            put_pixel_alpha(x + j, y + i, Bimage.data[i * width + j]);
        }
    }
}

int Graphics::get_pixel(int x, int y)
{
    volatile uint32_t *fb_ptr = static_cast<volatile uint32_t *>(framebuffer);
    return fb_ptr[y * (pitch / 4) + x];
}
void Graphics::load_font(long *font, int glyph_width, int glyph_height, int font_char_width, int FontSheetWidth)
{
    memcpy(StringFont, font, FontSheetWidth * FontSheetWidth);
    StringGlyphWidth = glyph_width;
    StringGlyphHeight = glyph_height;
    StringFontCharWidth = font_char_width;
    FontSheetWidth = FontSheetWidth;
}
void get_pixel_from_bitmap(long *bmpdata, int x, int y, int width, int height, int *color)
{
    *color = bmpdata[y * width + x];
}
