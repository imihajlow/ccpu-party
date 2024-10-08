
#include <string.h>
#include <../../ccpu-libsys/include/libsys/vga.h>

void _sleep(uint16_t time, uint16_t factor)
{
    while(factor--)
        for (uint16_t i = 0; i < time; ++i);
}

int main(void) {
    const char *smily_face =
"          DDDDDDDDDDDDDDDDDDDDDDDDD          "
"      DDDDDD                     DDDDDD      "
"   DDDDD                              DDDD   "
" DDDD                                   DDDD "
"D                                           D"
"D                                           D"
"D        0000                0000           D"
"D       00 .00              00 .00          D"
"D        0000                0000           D"
"D                                           D"
"D                                           D"
"D                                           D"
"D                                           D"
"D             lOl          lOl              D"
"D               0l;::::::::xK               D"
"D                  olloool                  D"
"D                                           D"
" DDDD                                   DDDD "
"   DDDDD                              DDDD   "
"      DDDDDD                     DDDDDD      "
"          DDDDDDDDDDDDDDDDDDDDDDDDD          ";

    const char *dead_face =
"          DDDDDDDDDDDDDDDDDDDDDDDDD          "
"      DDDDDD                     DDDDDD      "
"   DDDDD                              DDDD   "
" DDDD                                   DDDD "
"D                                           D"
"D                                           D"
"D        XX  XX                XX  XX       D"
"D          XX                    XX         D"
"D        XX  XX                XX  XX       D"
"D                                           D"
"D                                           D"
"D                                           D"
"D                                           D"
"D                  olloool                  D"
"D               0l;::::::::xK               D"
"D             lOl          lOl              D"
"D                                           D"
" DDDD                                   DDDD "
"   DDDDD                              DDDD   "
"      DDDDDD                     DDDDDD      "
"          DDDDDDDDDDDDDDDDDDDDDDDDD          ";

    vga_clear(COLOR(COLOR_RED, COLOR_WHITE));
    while (1) {
        for (int i = 0; i != 21; ++i) {
            memcpy(VGA_CHAR_SEG + VGA_OFFSET(2, i + 2), smily_face + i * 45, 45);
        }  

        _sleep(25000, 2);

        for (int i = 0; i != 21; ++i) {
            memcpy(VGA_CHAR_SEG + VGA_OFFSET(2, i + 2), dead_face + i * 45, 45);
        }

        _sleep(25000, 4);

    }
}

int getchar(void) { return 0; }
int putchar(int c) { return 0; }
