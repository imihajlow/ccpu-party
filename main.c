#include <string.h>
#include <libsys/vga.h>

#define COLOR_FIRE  224
#define FIRE_RANGE 16

#define VPIXELS(col, row) (vpixels[row * VGA_ROWS + VGA_COLS])

const uint8_t vpixels_size = 2 * VGA_COLS * VGA_ROWS; 
uint8_t vpixels[2 * VGA_COLS * VGA_ROWS];

void    vpixels_render(void)
{
    for (int row = 0; row < VGA_ROWS; row += 2)
    {
        for (int col = 0; col < VGA_COLS; col++)
        {
            // divide by 32 because divide by 2 to get average of 2 cells
            // and divide by 16 to map the range of 0-255 to range of 0-15
            VGA_CHAR_SEG[VGA_OFFSET(col, row/2)] = \
                (VPIXELS(col, row) + VPIXELS(col, row + 1)) / 32 + COLOR_FIRE;
        }
    }
}

void main(void) {
    vga_clear(COLOR(COLOR_RED, COLOR_WHITE));
    memset(vpixels, 0, vpixels_size); 
    vpixels_render();
    while (1) ;
}

int getchar(void) { return 0; }
int putchar(int c) { return 0; }
