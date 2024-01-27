#include <string.h>
#include <stdlib.h>
#include <libsys/vga.h>

#define COLOR_FIRE  224
#define FIRE_RANGE 16

#define VPIXELS(col, row) (vpixels[(row) * VGA_COLS + (col)])

const uint8_t vpixels_rows = 2 * VGA_ROWS;
const uint8_t vpixels_size = vpixels_rows * VGA_COLS;
uint8_t vpixels[2 * VGA_COLS * VGA_ROWS];

void step(void) {
    int i = 0;
    for (; i != 2 * VGA_COLS * (VGA_ROWS - 1); i++) {
        VPIXELS[i] = (VPIXELS[i + VGA_COLS] + VPIXELS[i + VGA_COLS - 1] + VPIXELS[i + VGA_COLS + 1]) / 3;
    }
    for (; i != 2 * VGA_COLS * VGA_ROWS; i++) {
        VPIXELS[i] = rand();
    }
}

void    vpixels_render(void)
{
    for (int row = 0; row < vpixels_rows; row += 2)
    {
        for (int col = 0; col < VGA_COLS; col++)
        {
            // divide by 32 because divide by 2 to get average of 2 cells
            // and divide by 16 to map the range of 0-255 to range of 0-15
            VGA_CHAR_SEG[VGA_OFFSET(col, row/2)] = VPIXELS(col, row);
                //(VPIXELS(col, row) + VPIXELS(col, row + 1)) / 32 + COLOR_FIRE;
        }
    }
}

void main(void) {
    vga_clear(COLOR(COLOR_RED, COLOR_WHITE));
    memset(vpixels, 'a', vpixels_size);
    vpixels_render();
    while (1) ;
}

int getchar(void) { return 0; }
int putchar(int c) { return 0; }
