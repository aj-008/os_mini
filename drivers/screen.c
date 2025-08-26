#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/memory.h"

// PRIVATE FUNCTION DECLARATION //

int get_cursor_offset();
int get_offset(int col, int row);
void set_cursor_offset(int offset);
int get_offset_row(int offset);
int get_offset_col(int offset);
int print_char(char c, int col, int row, char attribute);

void kprint_at(char *message, int col, int row) {
    int offset;
    if (col >=0 && row >=0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *message) {
    kprint_at(message, -1, -1);
}

void kprint_backspace() {
    int offset = get_cursor_offset()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, WHITE_ON_BLACK);
}


// PRIVATE FUNCTIONS //


int print_char(char c, int col, int row, char attribute) {
    unsigned char* video_mem = (unsigned char*) VIDEO_ADDRESS;
    if (!attribute) attribute = WHITE_ON_BLACK;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        video_mem[2 * MAX_COLS * MAX_ROWS - 2] = 'E';
        video_mem[2 * MAX_COLS * MAX_ROWS - 1] = RED_ON_WHITE;
        return get_offset(col, row);
    }


    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else if (c == 0x08) { /* Backspace */
        video_mem[offset] = ' ';
        video_mem[offset+1] = attribute;
    } else {
        video_mem[offset] = c;
        video_mem[offset+1] = attribute;
        offset += 2;
    }

    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memory_copy(get_offset(0, i-1) + (char *)VIDEO_ADDRESS,
                        get_offset(0, i) + (char *)VIDEO_ADDRESS,
                        MAX_COLS * 2);

        /* Blank last line */
        char *last_line = get_offset(0, MAX_ROWS-1) + (char *)VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLS * 2; i++) {
            last_line[i*2] = ' ';
            last_line[i*2+1] = 0x07;
        }

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}


void set_cursor_offset(int offset) {
    offset /= 2;
    port_outb(REG_SCREEN_CTRL, 14);
    port_outb(REG_SCREEN_DATA, (unsigned char) ((offset >> 8) & 0x00ff));
    port_outb(REG_SCREEN_CTRL, 15);
    port_outb(REG_SCREEN_DATA, (unsigned char) (offset & 0x00ff));
}


int get_cursor_offset() {
    port_outb(REG_SCREEN_CTRL, 14);
    int offset = port_inb(REG_SCREEN_DATA) << 8;
    port_outb(REG_SCREEN_CTRL, 15);
    offset += port_inb(REG_SCREEN_DATA);
    return offset * 2;
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    char *screen = (char *) VIDEO_ADDRESS;
    
    int i;
    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0,0));
}


int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset) {
    return (offset - (2 * get_offset_row(offset) * MAX_COLS)) / 2;
}
