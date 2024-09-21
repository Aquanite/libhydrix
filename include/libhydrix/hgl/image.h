#pragma once

#include <stdint.h>
#include <stddef.h>
#include <libhydrix/sdefs.h>
#include <libhydrix/hmem/smem/heap.h>
/// @brief Stretch an image
/// @param image The image
/// @param width The new width
/// @param height The new height
/// @return The stretched image
BMPI *StretchImage(BMPI *image, int width, int height);

/// @brief Stretch an alpha image
/// @param image The image
/// @param width The new width
/// @param height The new height
/// @return The stretched image
BMPA *StretchAlphaImage(BMPA *image, int width, int height);