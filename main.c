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
    uint16_t sum = vpixels[VGA_COLS] + vpixels[VGA_COLS - 1]; // sum of middle and right from last iteration
    for (; i != 2 * VGA_COLS * (VGA_ROWS - 1); i++) {
        const uint8_t right = vpixels[i + VGA_COLS + 1];
        const uint8_t down = vpixels[i + VGA_COLS + VGA_COLS];
        const uint8_t left = vpixels[i + VGA_COLS - 1];
        sum += right;
        vpixels[i] = (sum + down) / 4 - 1;
        sum -= left;
    }
    for (; i != 2 * VGA_COLS * VGA_ROWS; i++) {
        vpixels[i] = rand();
    }
}

void    vpixels_render(void)
{
    uint8_t *vpixel = vpixels;
    const int pixel_offset = VGA_OFFSET(0,1) - VGA_OFFSET(VGA_COLS,0);
    uint8_t *pixel = VGA_CHAR_SEG;
    for (int row = 0; row < vpixels_rows; row += 2)
    {
        for (int col = 0; col < VGA_COLS; col++)
        {
            const uint8_t upper_color = *vpixel >> 6;
            const uint8_t lower_color = ((*(vpixel + VGA_COLS) >> 4) & 0b11111100);
            *pixel = upper_color + lower_color + COLOR_FIRE; 
            vpixel++;
            pixel++;
        }
        vpixel += VGA_COLS;
        pixel += pixel_offset;
    }
}

void main(void) {
    vga_clear(COLOR(COLOR_RED, COLOR_WHITE));
    memset(vpixels, 1, vpixels_size);
    vpixels_render();
    while (1)
    {
        step();
        vpixels_render();
    }
}

int getchar(void) { return 0; }
int putchar(int c) { return 0; }
