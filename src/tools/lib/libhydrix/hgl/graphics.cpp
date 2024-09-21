#include <libhydrix/hgl/graphics.h>
#include <stdint.h>
#include <stddef.h>
#include <libhydrix/hmem/smem/smem.h>
#include <libhydrix/htime/htime.h>
#include <libhydrix/hlow/pit/pit.h>



// Target frame time in milliseconds
int MaxHz = 200;
uint64_t CachedWHB8 = 0;
uint16_t CachedPB8 = 0;
uint64_t last_frame_time = 0;
uint64_t targetFrameTime;
int currentPointY = 16; // Initial vertical position
// Graphics class constructor
Graphics::Graphics() {}

void Graphics::Init(uint32_t* fb, uint64_t width, uint64_t height, uint64_t Pitch, uint64_t bpp, uint64_t red_mask_shift, uint64_t green_mask_shift, uint64_t blue_mask_shift, uint64_t red_mask_size, uint64_t green_mask_size, uint64_t blue_mask_size) {
    this->FrameBuffer = fb;
    this->Width = width;
    this->Height = height;
    this->Pitch = Pitch;
    this->Bpp = bpp;
    this->RedMaskShift = red_mask_shift;
    this->GreenMaskShift = green_mask_shift;
    this->BlueMaskShift = blue_mask_shift;
    this->RedMaskSize = red_mask_size;
    this->GreenMaskSize = green_mask_size;
    this->BlueMaskSize = blue_mask_size;
    Font = (long*)CourierNew;
    GlyphWidth = COURIERNEW_GLYPH_WIDTH;
    GlyphHeight = COURIERNEW_GLYPH_HEIGHT;
    FontLetterSpacing = COURIERNEW_GLYPH_SPACE;
    BitmapFontSheetWidth = COURIERNEW_WIDTH;
    // Allocate the swap buffer
    CachedWHB8 = Width * Height * (Bpp/8);
    CachedPB8 = Pitch / (Bpp / 8);
    targetFrameTime = 1000 / MaxHz;
    last_frame_time = TimeSinceBootMS(); // Initialize to current time
    //allocate memory to get rid of bad data
    void* eeee = KernelAllocate(width * height * Bpp);
    SwapBuffer = (uint32_t*)KernelCleanAllocate(width * height * Bpp);
    KernelFree(eeee);
}

inline void Graphics::DrawPixelInline(int x, int y, int color) {
    if (x >= Width || y >= Height || x < 0 || y < 0) {
        return;
    }
    SwapBuffer[y * CachedPB8 + x] = color;
}

void Graphics::DrawPixel(int x, int y, int color) {
    if (x >= Width || y >= Height || x < 0 || y < 0) {
        return;
    }
    SwapBuffer[y * CachedPB8 + x] = color;
}
void Graphics::Clear(int color) {
    for (int i = 0; i < Width * Height; ++i) {
        SwapBuffer[i] = color;
    }
    currentPointY = Height - 16;
}

void Graphics::Clear() {
    Clear(0);
}
void Graphics::DrawChar(char c, int x, int y, uint8_t scaling, int color)
{
    const int glyph_width = GlyphWidth;
    const int glyph_height = GlyphHeight;
    const int image_width = BitmapFontSheetWidth;

    int char_index = c - 32;
    int char_x = char_index % 16;
    int char_y = char_index / 16;
    int char_offset = char_y * glyph_height * image_width + char_x * glyph_width;

    for (int i = 0; i < glyph_height; ++i)
    {
        for (int j = 0; j < glyph_width; ++j)
        {
            int pixel = Font[char_offset + i * image_width + j];
            if (pixel != 0)
            {
                for (int k = 0; k < scaling; k++)
                {
                    for (int l = 0; l < scaling; l++)
                    {
                        DrawPixelInline(x + j * scaling + k, y + i * scaling + l, color);
                    }
                }
            }
        }
    }   
}
void Graphics::DrawString(StringObj str, int x, int y, uint8_t scaling, int color)
{
    for (size_t i = 0; i < str.Length(); ++i)
    {
        DrawChar(str[i], x + i * GlyphWidth * scaling / 2, y, scaling, color);
    }
}
void Graphics::DrawChar(char c, int x, int y, int color)
{
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

void Graphics::DrawString(char *str, int x, int y, uint8_t scaling, int color)
{
    //draw with correct offset
    for (size_t i = 0; i < StringLength(str); ++i)
    {
        DrawChar(str[i], x + i * GlyphWidth * scaling /2 , y, scaling, color);
    }
}

void Graphics::DrawString(char *str, int x, int y, int color) {
    for (size_t i = 0; i < StringLength(str); ++i) {
        DrawChar(str[i], x + i * FontLetterSpacing, y, color);
    }
}

void Graphics::DrawString(StringObj str, int x, int y, int color)
{
    for (size_t i = 0; i < str.Length(); ++i)
    {
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

uint64_t currentTime = 0;
uint64_t lastFrameTime = 0;

 // 60 FPS in milliseconds

bool drawframe = false;
void Graphics::Display() {
    // Get the current time in milliseconds
    currentTime = TimeGetMilliseconds();
    
    // Calculate the time taken to process the last frame
    uint64_t frameProcessingTime = currentTime - lastFrameTime;

    // Calculate the sleep time needed to maintain target frame rate
    if (frameProcessingTime < targetFrameTime) {
        uint64_t sleepTime = targetFrameTime - frameProcessingTime;
        PITSleepMS(sleepTime);
    }
    // Update last frame time for the next call
    lastFrameTime = TimeGetMilliseconds();

    // Flip the buffers
    memcpy(FrameBuffer, SwapBuffer, CachedWHB8);
}
void Graphics::DisplayNonSynced()
{
    memcpy(FrameBuffer, SwapBuffer, CachedWHB8);
}



void Graphics::PrintDebug(StringObj Debug)
{
    //draw on bottom left
    DrawString(Debug, 0, currentPointY, 0xFFFFFF);
    currentPointY -= 16;
}

void Graphics::DrawImage(int x, int y, BMPI Bimage) {
    for (int i = 0; i < Bimage.height; ++i) {
        for (int j = 0; j < Bimage.width; ++j) {
            DrawPixelInline(x + j, y + i, Bimage.data[i * Bimage.width + j]);
        }
    }
}

int BlendAlpha(int toColor, int fromColor, uint8_t alpha)
{
    byte toR = (toColor >> 16) & 0xFF;
    byte toG = (toColor >> 8) & 0xFF;
    byte toB = toColor & 0xFF;

    byte fromR = (fromColor >> 16) & 0xFF;
    byte fromG = (fromColor >> 8) & 0xFF;
    byte fromB = fromColor & 0xFF;

    byte R = (byte)(((fromR * alpha) + (toR * (255 - alpha))) >> 8);
    byte G = (byte)(((fromG * alpha) + (toG * (255 - alpha))) >> 8);
    byte B = (byte)(((fromB * alpha) + (toB * (255 - alpha))) >> 8);

    return (R << 16) | (G << 8) | B;
}


void Graphics::DrawAlphaPixel(int x, int y, uint32_t Color) {
    if (x >= Width && y >= Height && x < 0 && y < 0) {
        return;
    }
    if (x < Width && y < Height) {
        int alpha = (Color >> 24) & 0xFF;
        if (alpha == 0) return;
        if (alpha == 255) {
            //remove alpha
            DrawPixelInline(x, y, Color & 0x00FFFFFF);
            return;
        }
        int fb_color = GetPixelFromScreen(x, y);
        int r = ((Color >> 16) & 0xFF) * alpha / 255 + ((fb_color >> 16) & 0xFF) * (255 - alpha) / 255;
        int g = ((Color >> 8) & 0xFF) * alpha / 255 + ((fb_color >> 8) & 0xFF) * (255 - alpha) / 255;
        int b = (Color & 0xFF) * alpha / 255 + (fb_color & 0xFF) * (255 - alpha) / 255;
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
            // x, y, r, g, b, a
            DrawAlphaPixel(x + j, y + i, Bimage.data[y2 * Bimage.width + x2]);
        }
    }
}


inline int Graphics::GetPixelFromScreen(int x, int y) {
    return SwapBuffer[y * (Pitch / (Bpp / 8)) + x];
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

int* Graphics::ClipFromScreen(int x, int y, int w, int h)
{
    int* data = (int*)KernelAllocate(w * h * sizeof(int));
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            data[i * w + j] = GetPixelFromScreen(x + j, y + i);
        }
    }
    return data;
}
void Graphics::ClipFromScreen(int x, int y, BMPI *Bimage)
{
    //Assume data is already allocated
    for (int i = 0; i < Bimage->height; i++)
    {
        for (int j = 0; j < Bimage->width; j++)
        {
            Bimage->data[i * Bimage->width + j] = GetPixelFromScreen(x + j, y + i);
        }
    }
}
void Graphics::DrawBézierCurve(float x0, float y0, float x1, float y1, float x2, float y2, int color)
{
    // Calculate distances between control points
    float dist_p0_p1 = MathF::SquareRoot((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    float dist_p1_p2 = MathF::SquareRoot((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    float dist_p0_p2 = MathF::SquareRoot((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));

    // Estimate the total distance the curve will cover
    float total_distance = dist_p0_p1 + dist_p1_p2 + dist_p0_p2;

    // Define the maximum distance between consecutive points on the curve
    const float max_pixel_step = 1.0f; // This controls the smoothness of the curve

    // Determine the number of steps based on the total distance
    int steps = (int)(total_distance / max_pixel_step);

    // Ensure we have at least 1 step
    if (steps < 1) steps = 1;

    // Iterate over t, which goes from 0.0 to 1.0 in increments
    for (int i = 0; i <= steps; ++i)
    {
        // Calculate the parameter t
        float t = (float)i / (float)steps;

        // Calculate the interpolated points for the Bézier curve using float precision
        float xa = x0 + t * (x1 - x0);
        float ya = y0 + t * (y1 - y0);
        float xb = x1 + t * (x2 - x1);
        float yb = y1 + t * (y2 - y1);

        // Final point on the curve
        float x = xa + t * (xb - xa);
        float y = ya + t * (yb - ya);

        // Draw the pixel at the calculated point, rounded to the nearest integer
        DrawPixelInline((int)x, (int)y, color);
    }
}

void Graphics::DrawCubicCurve(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, int color)
{
    // Calculate distances between consecutive control points
    float dist_p0_p1 = MathF::SquareRoot((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    float dist_p1_p2 = MathF::SquareRoot((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    float dist_p2_p3 = MathF::SquareRoot((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    float dist_p0_p3 = MathF::SquareRoot((x3 - x0) * (x3 - x0) + (y3 - y0) * (y3 - y0));

    // Estimate the total distance the curve will cover
    float total_distance = dist_p0_p1 + dist_p1_p2 + dist_p2_p3 + dist_p0_p3;

    // Define the maximum distance between consecutive points on the curve
    const float max_pixel_step = 1.0f; // This controls the smoothness of the curve

    // Determine the number of steps based on the total distance
    int steps = (int)(total_distance / max_pixel_step);

    // Ensure we have at least 1 step
    if (steps < 1) steps = 1;

    // Iterate over t, which goes from 0.0 to 1.0 in increments
    for (int i = 0; i <= steps; ++i)
    {
        // Calculate the parameter t
        float t = (float)i / (float)steps;

        // Calculate the interpolated points for the cubic Bézier curve using float precision
        float xa = x0 + t * (x1 - x0);
        float ya = y0 + t * (y1 - y0);
        float xb = x1 + t * (x2 - x1);
        float yb = y1 + t * (y2 - y1);
        float xc = x2 + t * (x3 - x2);
        float yc = y2 + t * (y3 - y2);

        float xm = xa + t * (xb - xa);
        float ym = ya + t * (yb - ya);
        float xn = xb + t * (xc - xb);
        float yn = yb + t * (yc - yb);

        // Final point on the curve
        float x = xm + t * (xn - xm);
        float y = ym + t * (yn - ym);

        // Draw the pixel at the calculated point, rounded to the nearest integer
        DrawPixel((int)x, (int)y, color);
    }
}
int Graphics::GetPixel(int x, int y)
{
    return GetPixelFromScreen(x,y);
}

void Graphics::SetHz(uint64_t hz)
{
    MaxHz = hz;
    targetFrameTime = 1000 / MaxHz; // 60 FPS in milliseconds
}
