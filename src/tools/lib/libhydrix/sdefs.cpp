#include <libhydrix/sdefs.h>
#include <libhydrix/hmem/smem/heap.h>
BMPI Stretch_BMPI(BMPI bmp, int width, int height)
{
    BMPI newbmp;
    newbmp.width = width;
    newbmp.height = height;
    newbmp.data = (int*)kalloc(width * height * sizeof(int));
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            newbmp.data[y * width + x] = bmp.data[(y * bmp.height / height) * bmp.width + (x * bmp.width / width)];
        }
    }
    return newbmp;
}

BMPA Stretch_BMPA(BMPA bmp, int width, int height)
{
    BMPA newbmp;
    newbmp.width = width;
    newbmp.height = height;
    newbmp.data = (long*)kalloc(width * height * sizeof(long));
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            newbmp.data[y * width + x] = bmp.data[(y * bmp.height / height) * bmp.width + (x * bmp.width / width)];
        }
    }
    return newbmp;
}
