#include <libhydrix/hgl/color.h>
#include <libhydrix/hgl/image.h>


BMPI *StretchImage(BMPI *image, int width, int height) {
    BMPI *new_image = (BMPI *)KernelAllocate(sizeof(BMPI));
    new_image->width = width;
    new_image->height = height;
    new_image->data = (int *)KernelAllocate(width * height * sizeof(int));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x = j * image->width / width;
            int y = i * image->height / height;
            new_image->data[i * width + j] = image->data[y * image->width + x];
        }
    }
    return new_image;
}

BMPA *StretchAlphaImage(BMPA *image, int width, int height)
{
    BMPA *new_image = (BMPA *)KernelAllocate(sizeof(BMPA));
    new_image->width = width;
    new_image->height = height;
    new_image->data = (long *)KernelAllocate(width * height * sizeof(long));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x = j * image->width / width;
            int y = i * image->height / height;
            new_image->data[i * width + j] = image->data[y * image->width + x];
        }
    }
    return new_image;
}