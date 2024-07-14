#pragma once

#include <stdint.h>
#include <stddef.h>
#include <libhydrix/sdefs.h>
#include <libhydrix/hmem/smem/heap.h>
/// @brief Stretch an image
BMPI *StretchImage(BMPI *image, int width, int height);

BMPA *StretchAlphaImage(BMPA *image, int width, int height);