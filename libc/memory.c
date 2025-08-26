#include "memory.h"

void memory_copy(char *target, const char *source, int length) {
    for (int i = 0; i < length; i++) {
         target[i] = source[i];
    }
}

void memory_set(char *d, char val, uint32_t len) {
    char *tmp = d;
    for ( ; len != 0; len--) *tmp++ = val;
}

char *memory_move(char *d, char *s, uint32_t n) {
    if (d == s || n == 0) return d;

    if (d < s) {
        for (int i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        for (int i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }
    return d;
}
