#include <libhydrix/hgl/color.h>
#include <libhydrix/hmem/smem/heap.h>
int IColor::RGB(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}
long IColor::RGBA(int r, int g, int b, int a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}
int IColor::InverseRGB(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b) ^ 0xFFFFFF;
}
long IColor::InverseRGBA(int r, int g, int b, int a)
{
    return ((r << 24) | (g << 16) | (b << 8) | a) ^ 0xFFFFFFFF;
}
int IColor::RGBAToRGB(long color)
{
    return (color & 0xFFFFFF);
}

uint8_t *IColor::IntToRGB(int value)
{
    uint8_t* values = (uint8_t*)KernelAllocate(3);
    values[0] = (value >> 16) & 0xFF;
    values[1] = (value >> 8) & 0xFF;
    values[2] = (value) & 0xFF;
    return values;
}

uint8_t *IColor::LongToRGBA(long value)
{
    uint8_t* values = (uint8_t*)KernelAllocate(4);
    values[0] = (value >> 24) & 0xFF;
    values[1] = (value >> 16) & 0xFF;
    values[2] = (value >> 8) & 0xFF;
    values[3] = value & 0xFF;
    return values;
}
int IColor::InverseRGBHex(int color)
{
    return color ^ 0xFFFFFF;
}

long IColor::InverseRGBAHex(long color)
{
    return color ^ 0xFFFFFFFF;
}