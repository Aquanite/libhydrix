#pragma once

#include <stdint.h>
#include <stddef.h>
#include <libhydrix/sdefs.h>
#include <libhydrix/hmem/smem/heap.h>
/// @brief Stretch an image
BMPI *stretch_image(BMPI *image, int width, int height);

BMPA *stretch_image_alpha(BMPA *image, int width, int height);