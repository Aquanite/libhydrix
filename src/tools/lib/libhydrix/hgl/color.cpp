#include <libhydrix/hgl/color.h>
#include <libhydrix/hmem/smem/heap.h>
int rgb(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}
long rgba(int r, int g, int b, int a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}
int inverse_rgb(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b) ^ 0xFFFFFF;
}
long inverse_rgba(int r, int g, int b, int a)
{
    return ((r << 24) | (g << 16) | (b << 8) | a) ^ 0xFFFFFFFF;
}
int a2rgb(long color)
{
    return (color & 0xFFFFFF);
}

uint8_t *int_to_rgb(int value)
{
    uint8_t* values = (uint8_t*)kalloc(3);
    values[0] = (value >> 16) & 0xFF;
    values[1] = (value >> 8) & 0xFF;
    values[2] = (value) & 0xFF;
    return values;
}

uint8_t *long_to_rgba(long value)
{
    uint8_t* values = (uint8_t*)kalloc(4);
    values[0] = (value >> 24) & 0xFF;
    values[1] = (value >> 16) & 0xFF;
    values[2] = (value >> 8) & 0xFF;
    values[3] = value & 0xFF;
    return values;
}
int inverse_rgb_hex(int color)
{
    return color ^ 0xFFFFFF;
}

long inverse_rgba_hex(long color)
{
    return color ^ 0xFFFFFFFF;
}