#include "color.h"
int rgb(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}
int rgba(int r, int g, int b, int a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}