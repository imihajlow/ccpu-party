#include <string.h>
#include <libsys/vga.h>

void main(void) {
    vga_clear(COLOR(COLOR_GRAY, COLOR_BLACK));
    strcpy(VGA_CHAR_SEG, "Hello");
    while (1) ;
}

int getchar(void) { return 0; }
int putchar(int c) { return 0; }
