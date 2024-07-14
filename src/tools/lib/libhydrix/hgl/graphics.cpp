#include <libhydrix/hgl/graphics.h>
#include <stdint.h>
#include <stddef.h>
#include <libhydrix/hmem/smem/smem.h>
// Graphics class constructor
Graphics::Graphics() {}

// Global variables for font properties


void Graphics::Init(uint32_t* fb, uint64_t width, uint64_t height, uint64_t Pitch, uint64_t bpp) {
    this->FrameBuffer = fb;
    this->Width = width;
    this->Height = height;
    this->Pitch = Pitch;
    this->Bpp = bpp;
    Font = (long*)CourierNew;
    GlyphWidth = COURIERNEW_GLYPH_WIDTH;
    GlyphHeight = COURIERNEW_GLYPH_HEIGHT;
    FontLetterSpacing = COURIERNEW_GLYPH_SPACE;
    BitmapFontSheetWidth = COURIERNEW_WIDTH;
    // Allocate the swap buffer

    //allocate memory to get rid of bad data
    KernelAllocate(width * height * Bpp);
    SwapBuffer = (uint32_t*)KernelCleanAllocate(width * height * Bpp);
}

inline void Graphics::DrawPixelInline(int x, int y, int color) {
    if (x < Width && y < Height) {
        SwapBuffer[y * (Pitch / 4) + x] = color;
    }
}
void Graphics::DrawPixel(int x, int y, int color) {
    if (x < Width && y < Height) {
        SwapBuffer[y * (Pitch / 4) + x] = color;
    }
}
void Graphics::Clear(int color) {
    uint32_t *fb_ptr = SwapBuffer;
    for (uint64_t y = 0; y < Height; ++y) {
        for (uint64_t x = 0; x < Width; ++x) {
            fb_ptr[y * (Pitch / 4) + x] = color;
        }
    }
}

void Graphics::Clear() {
    Clear(0);
}

void Graphics::DrawChar(char c, int x, int y, int color) {
    const int glyph_width = GlyphWidth;
    const int glyph_height = GlyphHeight;
    const int image_width = BitmapFontSheetWidth;

    int char_index = c - 32;
    int char_x = char_index % 16;
    int char_y = char_index / 16;
    int char_offset = char_y * glyph_height * image_width + char_x * glyph_width;

    for (int i = 0; i < glyph_height; ++i) {
        for (int j = 0; j < glyph_width; ++j) {
            int pixel = Font[char_offset + i * image_width + j];
            if (pixel != 0) {
                DrawPixelInline(x + j, y + i, color);
            }
        }
    }
}

void Graphics::DrawString(char *str, int x, int y, int color) {
    for (size_t i = 0; i < StringLength(str); ++i) {
        DrawChar(str[i], x + i * FontLetterSpacing, y, color);
    }
}

void Graphics::DrawLine(int x1, int y1, int x2, int y2, int color) {
    int dx = MathI::Absolute(x2 - x1);
    int dy = MathI::Absolute(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (true) {
        DrawPixelInline(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }
}

void Graphics::DrawRectangle(int x, int y, int w, int h, int color) {
    DrawLine(x, y, x + w, y, color);
    DrawLine(x, y, x, y + h, color);
    DrawLine(x + w, y, x + w, y + h, color);
    DrawLine(x, y + h, x + w, y + h, color);
}

void Graphics::DrawFilledRectangle(int x, int y, int w, int h, int color) {
    for (int i = 0; i < h; ++i) {
        DrawLine(x, y + i, x + w, y + i, color);
    }
}

void Graphics::DrawCircle(int x0, int y0, int radius, int color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        DrawPixelInline(x0 + x, y0 + y, color);
        DrawPixelInline(x0 + y, y0 + x, color);
        DrawPixelInline(x0 - y, y0 + x, color);
        DrawPixelInline(x0 - x, y0 + y, color);
        DrawPixelInline(x0 - x, y0 - y, color);
        DrawPixelInline(x0 - y, y0 - x, color);
        DrawPixelInline(x0 + y, y0 - x, color);
        DrawPixelInline(x0 + x, y0 - y, color);

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

void Graphics::DrawFilledCircle(int x0, int y0, int radius, int color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        DrawLine(x0 - y, y0 + x, x0 + y, y0 + x, color);
        DrawLine(x0 - x, y0 - y, x0 + x, y0 - y, color);
        DrawLine(x0 - y, y0 - x, x0 + y, y0 - x, color);

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

void Graphics::Display() {
    memcpy(FrameBuffer, SwapBuffer, Width * Height * sizeof(uint32_t));
}

void Graphics::DrawImage(int x, int y, BMPI Bimage) {
    for (int i = 0; i < Bimage.height; ++i) {
        for (int j = 0; j < Bimage.width; ++j) {
            DrawPixelInline(x + j, y + i, Bimage.data[i * Bimage.width + j]);
        }
    }
}

void Graphics::DrawAlphaPixel(int x, int y, long color) {
    //put pixel with transparency
    if (x < Width && y < Height) {
        int alpha = (color >> 24) & 0xFF;
        if (alpha == 0) return;
        if (alpha == 255) {
            DrawPixelInline(x, y, color);
            return;
        }
        int fb_color = GetPixelFromScreen(x, y);
        int r = ((color >> 16) & 0xFF) * alpha / 255 + ((fb_color >> 16) & 0xFF) * (255 - alpha) / 255;
        int g = ((color >> 8) & 0xFF) * alpha / 255 + ((fb_color >> 8) & 0xFF) * (255 - alpha) / 255;
        int b = (color & 0xFF) * alpha / 255 + (fb_color & 0xFF) * (255 - alpha) / 255;
        DrawPixelInline(x, y, (r << 16) | (g << 8) | b);
    }

}


void Graphics::DrawAlphaImage(int x, int y, BMPA Bimage) {
    for (int i = 0; i < Bimage.height; ++i) {
        for (int j = 0; j < Bimage.width; ++j) {
            DrawAlphaPixel(x + j, y + i, Bimage.data[i * Bimage.width + j]);
        }
    }
}
void Graphics::DrawStretchedImage(int x, int y, int w, int h, BMPI Bimage)
{

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int x2 = j * Bimage.width / w;
            int y2 = i * Bimage.height / h;
            DrawPixelInline(x + j, y + i, Bimage.data[y2 * Bimage.width + x2]);
        }
    }
}

void Graphics::DrawStretchedAlphaImage(int x, int y, int w, int h, BMPA Bimage)
{
    //scale the image
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int x2 = j * Bimage.width / w;
            int y2 = i * Bimage.height / h;
            DrawAlphaPixel(x + j, y + i, Bimage.data[y2 * Bimage.width + x2]);
        }
    }
}


inline int Graphics::GetPixelFromScreen(int x, int y) {
    return SwapBuffer[y * (Pitch / 4) + x];
}

void Graphics::LoadFont(long *font, int glyph_width, int glyph_height, int font_char_width, int font_sheet_width) {
    memcpy(Font, font, font_sheet_width * font_sheet_width * sizeof(long));
    GlyphWidth = glyph_width;
    GlyphHeight = glyph_height;
    FontLetterSpacing = font_char_width;
    BitmapFontSheetWidth = font_sheet_width;
}

inline void get_pixel_from_bitmap(long *bmpdata, int x, int y, int width, int height, int *color) {
    *color = bmpdata[y * width + x];
}
