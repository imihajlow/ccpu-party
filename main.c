#include <string.h>
#include <stdlib.h>
#include <libsys/vga.h>

#define COLOR_FIRE  224
#define FIRE_RANGE 16

#define VPIXELS(col, row) (vpixels[(row) * VGA_COLS + (col)])

const uint8_t vpixels_rows = 2 * VGA_ROWS;
const size_t vpixels_size = vpixels_rows * VGA_COLS;
uint8_t vpixels[2 * VGA_COLS * VGA_ROWS];

void step(void) {
    int i = 0;
    for (; i != 2 * VGA_COLS * (VGA_ROWS - 1); i++) {
        vpixels[i] = (vpixels[i + VGA_COLS] + vpixels[i + VGA_COLS - 1] + vpixels[i + VGA_COLS + 1]) / 3;
    }
    for (; i != 2 * VGA_COLS * VGA_ROWS; i++) {
        vpixels[i] = rand();
    }
}

void    vpixels_render(void)
{
    uint8_t *pixel = vpixels;
    for (int row = 0; row < vpixels_rows; row += 2)
    {
        for (int col = 0; col < VGA_COLS; col++)
        {
            // divide by 32 because divide by 2 to get average of 2 cells
            // and divide by 16 to map the range of 0-255 to range of 0-15
            const uint8_t upper_color = *pixel >> 6;
            const uint8_t lower_color = ((*(pixel + VGA_COLS) >> 4) & 0b11111100);
            VGA_CHAR_SEG[VGA_OFFSET(col, row/2)] = upper_color + lower_color + COLOR_FIRE; 
            pixel++;
        }
        pixel += VGA_COLS;
    }
}

void main(void) {
    vga_clear(COLOR(COLOR_RED, COLOR_WHITE));
    memset(vpixels, 0, vpixels_size);
    vpixels_render();
    while (1)
    {
        step();
        vpixels_render();
    }
}

int getchar(void) { return 0; }
int putchar(int c) { return 0; }
