#pragma once

struct DisplayInfo {
    void *address;
    int bpp; // bits per pixel
    int width; // width in pixels
    int height; // height in pixels
    int refresh; // refresh rate in Hz
};