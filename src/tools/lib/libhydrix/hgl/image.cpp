#include <libhydrix/hgl/color.h>
#include <libhydrix/hgl/image.h>


BMPI *stretch_image(BMPI *image, int width, int height) {
    BMPI *new_image = (BMPI *)kalloc(sizeof(BMPI));
    new_image->width = width;
    new_image->height = height;
    new_image->data = (int *)kalloc(width * height * sizeof(int));
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

BMPA *stretch_image_alpha(BMPA *image, int width, int height)
{
    BMPA *new_image = (BMPA *)kalloc(sizeof(BMPA));
    new_image->width = width;
    new_image->height = height;
    new_image->data = (long *)kalloc(width * height * sizeof(long));
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