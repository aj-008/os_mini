#include "ports.h"

unsigned char port_inb(unsigned short port) {
    unsigned char result;

    asm ("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_outb(unsigned short port, unsigned char data) {
    asm ("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_inw(unsigned short port) {
    unsigned short result;
    asm ("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_outw(unsigned short port, unsigned short data) {
    asm ("out %%ax, %%dx" : : "a" (data), "d" (port));
}
