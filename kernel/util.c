#include "util.h"

void memory_copy(char *target, const char *source, int length) {
    for (int i = 0; i < length; i++) {
         target[i] = source[i];
    }
}

void itoa(int n, char *str, int base) {
    int sign, i;
    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        int digit = n % base;
        if (digit < 10) {
            str[i++] = digit + '0';
        } else {
            str[i++] = digit - 10 + 'A';
        }
    } while ((n /= base) > 0);
    if (sign < 0 && base == 10) {
        str[i++] = '-';
    }
    str[i] = '\0';
    strrev(str, i);
}

void strrev(char *target, int length) {
    for (int i = 0; i < length / 2; i++) {
        char temp = target[i];
        target[i] = target[length - i - 1];
        target[length - i - 1] = temp;
    }
}

    

