#include "graphics.h"

//graphics::graphics
Graphics::Graphics() {
}

void Graphics::init(limine_framebuffer fb) {
    framebuffer = fb;
    //Set the swap buffer to the framebuffer address + the pitch * height
    SwapBuffer = (uint32_t*)framebuffer.address + (framebuffer.width * framebuffer.height);
}
void Graphics::put_pixel(int x, int y, int color) {
    volatile uint32_t *fb_ptr = static_cast<volatile uint32_t *>(SwapBuffer);
    fb_ptr[y * (framebuffer.pitch / 4) + x] = color;
}
void Graphics::fill_screen(int color) {
    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {
            put_pixel(x, y, color);
        }
    }
}
void Graphics::zero_clear() {
    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {
            //modify address to framebuffer address
            volatile uint32_t *fb_ptr = static_cast<volatile uint32_t *>(framebuffer.address);
            fb_ptr[y * (framebuffer.pitch / 4) + x] = 0;
        }
    }
}
void Graphics::put_string(char* str, int x, int y, int color) {
    //draw char but if space move x by 10
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            x += 1;
        }
        x += 4;
        put_char(str[i], x + i * 10, y, color);
        //2 px padding
    }
}
void Graphics::clear() {
    fill_screen(0);
}
void Graphics::put_char(char c, int x, int y, int color) {
            if (c == 'a' || c == 'A') {
                //bottom left to top left
                put_line(x, y + 20, x, y, color);
                //bottom right to top right
                put_line(x + 10, y + 20, x + 10, y, color);
                //top left to top right
                put_line(x, y, x + 10, y, color);
                //middle left to middle right
                put_line(x, y + 10, x + 10, y + 10, color);
            }
            //b
            else if (c == 'b' || c == 'B') {
                //top left to bottom left
                put_line(x, y, x, y + 20, color);
                //bottom left to bottom right
                put_line(x, y + 20, x + 10, y + 20, color);
                //top left to top right
                put_line(x, y, x + 10, y, color);
                //middle left to middle of character
                put_line(x, y + 10, x + 7, y + 10, color);
                // bottom right to middle right
                put_line(x + 10, y + 20, x + 10, y + 13, color);
                // top right to middle right
                put_line(x + 10, y, x + 10, y + 7, color);
                //from y 7 to middle of char
                put_line(x + 10, y + 7, x + 7, y + 10, color);
                // from y 13 to middle of char
                put_line(x + 10, y + 13, x + 7, y + 10, color);

            }
            //c
            else if (c == 'c' || c == 'C') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //d
            else if (c == 'd' || c == 'D') {
                //Draw top left to middle top
                put_line(x, y, x + 5, y, color);
                //Draw top left to bottom left
                put_line(x, y, x, y + 20, color);
                //Draw bottom left to middle bottom
                put_line(x, y + 20, x + 5, y + 20, color);
                // middle bottom to middle right, diagonal
                put_line(x + 5, y + 20, x + 10, y + 15, color);
                //middle top to middle right, diagonal
                put_line(x + 5, y, x + 10, y + 5, color);
                //line from y + 5 to y + 15
                put_line(x + 10, y + 5, x + 10, y + 15, color);

                


            }
            //e
            else if (c == 'e' || c == 'E') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //f
            else if (c == 'f' || c == 'F') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 10, x + 10, y + 10, color);
            }
            //g
            else if (c == 'g' || c == 'G') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                put_line(x + 10, y + 10, x + 10, y + 20, color);
                put_line(x + 5, y + 20, x + 10, y + 20, color);
            }
            //h
            else if (c == 'h' || c == 'H') {
                put_line(x, y, x, y + 20, color);
                put_line(x + 10, y, x + 10, y + 20, color);
                put_line(x, y + 10, x + 10, y + 10, color);
            }
            //i
            else if (c == 'i' || c == 'I') {
                put_line(x + 5, y, x + 5, y + 20, color);
                put_line(x, y, x + 10, y, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //j
            else if (c == 'j' || c == 'J') {
                //draw line from right top to bottom right
                put_line(x + 10, y, x + 10, y + 20, color);
                //draw line from bottom left to bottom right
                put_line(x, y + 20, x + 10, y + 20, color);
                //from bottom left to middle left
                put_line(x, y + 20, x, y + 10, color);
                //from top left to top right
                put_line(x, y, x + 10, y, color);
            }
            //k
            else if (c == 'k' || c == 'K') {
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 10, x + 10, y, color);
                put_line(x, y + 10, x + 10, y + 20, color);
            }
            //l
            else if (c == 'l' || c == 'L') {
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //m
            else if (c == 'm' || c == 'M') {
                put_line(x, y, x, y + 20, color);
                put_line(x + 10, y, x + 10, y + 20, color);
                put_line(x, y, x + 5, y + 10, color);
                put_line(x + 5, y + 10, x + 10, y, color);
            }
            //n
            else if (c == 'n' || c == 'N') {
                put_line(x, y, x, y + 20, color);
                put_line(x + 10, y, x + 10, y + 20, color);
                put_line(x, y, x + 10, y + 20, color);
            }
            //o
            else if (c == 'o' || c == 'O') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                put_line(x + 10, y, x + 10, y + 20, color);
            }
            //p
            else if (c == 'p' || c == 'P') {
                put_line(x, y, x, y + 20, color);
                put_line(x, y, x + 10, y, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y, x + 10, y + 10, color);
            }
            //q
            else if (c == 'q' || c == 'Q') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                put_line(x + 10, y, x + 10, y + 20, color);
                put_line(x + 5, y + 10, x + 10, y + 20, color);
            }
            //r
            else if (c == 'r' || c == 'R') {
                put_line(x, y, x, y + 20, color);
                put_line(x, y, x + 10, y, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y, x + 10, y + 10, color);
                put_line(x, y + 10, x + 10, y + 20, color);
            }
            //s
            else if (c == 's' || c == 'S') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 10, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y + 10, x + 10, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //t
            else if (c == 't' || c == 'T') {
                put_line(x, y, x + 10, y, color);
                put_line(x + 5, y, x + 5, y + 20, color);
            }
            //u
            else if (c == 'u' || c == 'U') {
                put_line(x, y, x, y + 20, color);
                put_line(x + 10, y, x + 10, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //v
            else if (c == 'v' || c == 'V') {
                put_line(x, y, x + 5, y + 20, color);
                put_line(x + 10, y, x + 5, y + 20, color);
            }
            //w
            else if (c == 'w' || c == 'W') {
                //top left to bottom left
                put_line(x, y, x, y + 20, color);
                //top right to bottom right
                put_line(x + 10, y, x + 10, y + 20, color);
                // bottom left to middle
                put_line(x, y + 20, x + 5, y + 10, color);
                //bottom right to middle
                put_line(x + 10, y + 20, x + 5, y + 10, color);

            }
            //x
            else if (c == 'x' || c == 'X') {
                put_line(x, y, x + 10, y + 20, color);
                put_line(x + 10, y, x, y + 20, color);
            }
            //y
            else if (c == 'y' || c == 'Y') {
                put_line(x, y, x + 5, y + 10, color);
                put_line(x + 10, y, x + 5, y + 10, color);
                put_line(x + 5, y + 10, x + 5, y + 20, color);
            }
            //z
            else if (c == 'z' || c == 'Z') {
                put_line(x, y, x + 10, y, color);
                put_line(x + 10, y, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //space
            else if (c == ' ') {
                return;
            } 
            //0
            else if (c == '0') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                put_line(x + 10, y, x + 10, y + 20, color);
                //line from bottom left to top right
                put_line(x, y + 20, x + 10, y, color);
            }
            //1
            else if (c == '1') {
                put_line(x + 5, y, x + 5, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                //diag
                put_line(x + 5, y, x, y + 5, color);
            }
            //2
            else if (c == '2') {
                put_line(x, y, x + 10, y, color);
                put_line(x + 10, y, x + 10, y + 10, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x, y + 10, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //3
            else if (c == '3') {
                put_line(x, y, x + 10, y, color);
                put_line(x + 10, y, x + 10, y + 20, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //4
            else if (c == '4') {
                put_line(x, y, x, y + 10, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y, x + 10, y + 20, color);
            }
            //5
            else if (c == '5') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 10, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y + 10, x + 10, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //6
            else if (c == '6') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y + 10, x + 10, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //7
            else if (c == '7') {
                put_line(x, y, x + 10, y, color);
                put_line(x + 10, y, x + 10, y + 20, color);
            }
            //8
            else if (c == '8') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y + 10, x + 10, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                //line from top right to bottom right
                put_line(x + 10, y, x + 10, y + 20, color);
            }
            //9
            else if (c == '9') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 10, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y + 10, x + 10, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                //line from top right to middle right
                put_line(x + 10, y, x + 10, y + 10, color);
            }
            //.
            else if (c == '.') {
                put_filled_rect(x + 4, y + 18, 3, 3, color);
            }
            //,
            else if (c == ',') {
                put_filled_rect(x + 4, y + 18, 1, 3, color);
                // pixel under the bottom left of filled rect
                put_filled_rect(x + 3, y + 21, 1, 2, color);
                put_filled_rect(x + 2, y + 22, 1, 2, color);


            }
            //!
            else if (c == '!') {
                put_filled_rect(x + 4, y + 18, 1, 4, color);
                put_filled_rect(x + 4, y, 1, 14, color);
            }
            //?
            else if (c == '?') {
                put_line(x, y, x + 10, y, color);
                put_line(x + 10, y, x + 10, y + 10, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y + 10, x + 10, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                put_line(x + 5, y + 20, x + 5, y + 22, color);
                
            }
            //:
            else if (c == ':') {
                put_filled_rect(x + 4, y + 4, 2, 2, color);
                put_filled_rect(x + 4, y + 16, 2, 2, color);
            }
            //;
            else if (c == ';') {
                put_filled_rect(x + 4, y + 8, 2, 2, color);
                put_filled_rect(x + 4, y + 12, 2, 2, color);
                put_line(x + 5, y + 14, x + 5, y + 16, color);
            }
            //'
            else if (c == '\'') {
                put_line(x + 5, y, x + 5, y + 2, color);
            }
            //"
            else if (c == '"') {
                put_line(x + 3, y, x + 3, y + 2, color);
                put_line(x + 7, y, x + 7, y + 2, color);
            }
            //[
            else if (c == '[') {
                //top left to top middle
                put_line(x, y, x + 5, y, color);
                //top left to bottom left
                put_line(x, y, x, y + 20, color);
                //bottom left to bottom middle
                put_line(x, y + 20, x + 5, y + 20, color);
            }
            //]
            else if (c == ']') {
                //top right to top middle
                put_line(x + 5, y, x + 10, y, color);
                //top right to bottom right
                put_line(x + 10, y, x + 10, y + 20, color);
                //bottom right to bottom middle
                put_line(x + 5, y + 20, x + 10, y + 20, color);
            }
            //{
            else if (c == '{') {
                put_line(x, y, x + 5, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 20, x + 5, y + 20, color);
                put_line(x + 5, y, x + 5, y + 20, color);
            }
            //}
            else if (c == '}') {
                put_line(x, y, x + 5, y, color);
                put_line(x + 5, y, x + 5, y + 20, color);
                put_line(x, y + 20, x + 5, y + 20, color);
                put_line(x, y, x, y + 20, color);
            }
            //+
            else if (c == '+') {
                //horizontal line
                put_line(x, y + 10, x + 10, y + 10, color);
                // vertical line is the same length as the horizontal line
                put_line(x + 5, y + 5, x + 5, y + 15, color);
            }
            //-
            else if (c == '-') {
                put_line(x, y + 10, x + 10, y + 10, color);
            }
            //_
            else if (c == '_') {
                put_line(x, y + 20, x + 10, y + 20, color);
            }
            //=
            else if (c == '=') {
                put_line(x, y + 5, x + 10, y + 5, color);
                put_line(x, y + 15, x + 10, y + 15, color);
            }
            //*
            else if (c == '*') {
                put_line(x, y, x + 10, y + 20, color);
                put_line(x + 10, y, x, y + 20, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 5, y, x + 5, y + 20, color);
            }
            // /
            else if (c == '/') {
                put_line(x, y + 20, x + 10, y, color);
            }
            else if (c == '\\') {
                put_line(x, y + 20, x + 10, y, color);
            }
            // <
            else if (c == '<') {
                put_line(x, y + 10, x + 10, y, color);
                put_line(x, y + 10, x + 10, y + 20, color);
            }
            // >
            else if (c == '>') {
                put_line(x, y, x + 10, y + 10, color);
                put_line(x, y + 20, x + 10, y + 10, color);
            }
            // ^
            else if (c == '^') {
                put_line(x, y, x + 5, y + 10, color);
                put_line(x + 5, y + 10, x + 10, y, color);
            }
            // &
            else if (c == '&') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 10, color);
                put_line(x, y + 10, x + 10, y + 20, color);
                put_line(x + 10, y + 20, x + 10, y + 10, color);
            }
            // %
            else if (c == '%') {
                //small rect top left, line from bottom left to top right, small rect bottom right
                put_rect(x, y, 4, 4, color);
                put_rect(x + 6, y + 16, 4, 4, color);
                put_line(x, y + 20, x + 10, y, color);
            }
            // $
            else if (c == '$') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 10, color);
                put_line(x, y + 10, x + 10, y + 10, color);
                put_line(x + 10, y + 10, x + 10, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                put_line(x, y + 10, x, y + 20, color);
                put_line(x + 10, y, x + 10, y + 10, color);
            }
            // #
            else if (c == '#') {
                //third from top left to third from bottom left
                put_line(x + 3, y, x + 3, y + 20, color);
                //third from top right to third from bottom right
                put_line(x + 7, y, x + 7, y + 20, color);
                // third from top left to middle left to third from top right to middle right
                put_line(x, y + 7, x + 10, y + 7, color);
                // third from bottom left to middle left to third from bottom right to middle right
                put_line(x, y + 13, x + 10, y + 13, color);

            }
            // @
            else if (c == '@') {
                put_line(x, y, x + 10, y, color);
                put_line(x, y, x, y + 20, color);
                put_line(x, y + 20, x + 10, y + 20, color);
                put_line(x + 10, y, x + 10, y + 20, color);
                put_line(x + 5, y + 10, x + 10, y + 10, color);
                put_line(x + 5, y + 10, x + 5, y + 20, color);
            }
            // |
            else if (c == '|') {
                put_line(x + 5, y, x + 5, y + 20, color);
            }
            // ~
            else if (c == '~') {
                put_line(x, y + 10, x + 5, y + 5, color);
                put_line(x + 5, y + 5, x + 10, y + 10, color);
                put_line(x, y + 15, x + 5, y + 10, color);
                put_line(x + 5, y + 10, x + 10, y + 15, color);
            }
            // `
            else if (c == '`') {
                put_line(x + 5, y, x + 7, y + 2, color);
            }
            // else draw box with question mark in it
}
void Graphics::put_line(int x1, int y1, int x2, int y2, int color) {
    int dx = MathI::abs(x2 - x1);
    int dy = MathI::abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;
    while (true) {
        put_pixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }
}
/*void Graphics::put_line_gradient(int x1, int y1, int x2, int y2, int color1, int color2) {
    int dx = MathI::abs(x2 - x1);
    int dy = MathI::abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;
    while (true) {
        int r = lerpf(r1, r2, (float)(x1 - x2) / (float)(x1 - x2));
        int g = lerpf(g1, g2, (float)(x1 - x2) / (float)(x1 - x2));
        int b = lerpf(b1, b2, (float)(x1 - x2) / (float)(x1 - x2));
        put_pixel(x1, y1, rgb(r, g, b));
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }
}*/
void Graphics::put_rect(int x, int y, int w, int h, int color) {
    put_line(x, y, x + w, y, color);
    put_line(x, y, x, y + h, color);
    put_line(x + w, y, x + w, y + h, color);
    put_line(x, y + h, x + w, y + h, color);
}
void Graphics::put_filled_rect(int x, int y, int w, int h, int color) {
    for (int i = 0; i < h; i++) {
        put_line(x, y + i, x + w, y + i, color);
    }
}
void Graphics::put_circle(int x0, int y0, int radius, int color) {
    int x = radius;
    int y = 0;
    int err = 0;
    while (x >= y) {
        put_pixel(x0 + x, y0 + y, color);
        put_pixel(x0 + y, y0 + x, color);
        put_pixel(x0 - y, y0 + x, color);
        put_pixel(x0 - x, y0 + y, color);
        put_pixel(x0 - x, y0 - y, color);
        put_pixel(x0 - y, y0 - x, color);
        put_pixel(x0 + y, y0 - x, color);
        put_pixel(x0 + x, y0 - y, color);
        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}
void Graphics::put_filled_circle(int x0, int y0, int radius, int color) {
    int x = radius;
    int y = 0;
    int err = 0;
    while (x >= y) {
        put_line(x0 - x, y0 + y, x0 + x, y0 + y, color);
        put_line(x0 - y, y0 + x, x0 + y, y0 + x, color);
        put_line(x0 - x, y0 - y, x0 + x, y0 - y, color);
        put_line(x0 - y, y0 - x, x0 + y, y0 - x, color);
        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}
void Graphics::Swap()
{
    //put all the SwapBuffer data into the framebuffer
    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {
            volatile uint32_t *fb_ptr = static_cast<volatile uint32_t *>(framebuffer.address);
            fb_ptr[y * (framebuffer.pitch / 4) + x] = SwapBuffer[y * (framebuffer.pitch / 4) + x];
        }
    }
}