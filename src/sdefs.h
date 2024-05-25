#pragma once
#include <stdint.h>
#include <stddef.h>
/// @brief A function pointer that can accept any amount of arguments and return any type.
typedef void (*function_pointer)();
/// @brief Basic handle in general.
#define HANDLE void*
/// @brief An address in memory.
#define ADDRESS void*
/// @brief A Point, with x and y coordinates.
typedef struct _point {
    /// @brief The x coordinate.
    int x;
    /// @brief The y coordinate.
    int y;
} Point;

/// @brief A Floating Point, with x and y coordinates.
typedef struct _fpoint {
    /// @brief The x coordinate.
    float x;
    /// @brief The y coordinate.
    float y;
} FPoint;

/// @brief A Rectangle, with x, y, width, and height.
typedef struct _rect {
    /// @brief The x coordinate.
    int x;
    /// @brief The y coordinate.
    int y;
    /// @brief The width.
    int w;
    /// @brief The height.
    int h;
} Rect;

/// @brief A Floating Rectangle, with x, y, width, and height.
typedef struct _frect {
    /// @brief The x coordinate.
    float x;
    /// @brief The y coordinate.
    float y;
    /// @brief The width.
    float w;
    /// @brief The height.
    float h;
} FRect;

/// @brief A Size, with width and height.
typedef struct _size {
    /// @brief The width.
    int w;
    /// @brief The height.
    int h;
} Size;

/// @brief A Floating Size, with width and height.
typedef struct _fsize {
    /// @brief The width.
    float w;
    /// @brief The height.
    float h;
} FSize;

/// @brief A Color
typedef struct _color {
    /// @brief The red value.
    uint8_t r;
    /// @brief The green value.
    uint8_t g;
    /// @brief The blue value.
    uint8_t b;
} Color;

/// @brief A Color with alpha
typedef struct _color {
    /// @brief The red value.
    uint8_t r;
    /// @brief The green value.
    uint8_t g;
    /// @brief The blue value.
    uint8_t b;
    /// @brief The alpha value.
    uint8_t a;
} ColorA;
