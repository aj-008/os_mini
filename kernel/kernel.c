#include "../drivers/screen.h"

void kernel_main() {
    clear_screen();
    kprint_at("12345678901234", 1, 6);
    kprint_at("This text spans multiple lines", 75, 10);
    kprint_at("this contains a line\nbreak", 0, 20);
    kprint("heres another line\nbreak");
    kprint_at("what happens when we run out of space?", 70, 25);
    while (1) ;
}

