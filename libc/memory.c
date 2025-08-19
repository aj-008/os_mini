#include "memory.h"

void memory_copy(char *target, const char *source, int length) {
    for (int i = 0; i < length; i++) {
         target[i] = source[i];
    }
}

void memory_set(uint8_t *d, uint8_t val, uint32_t len) {
    uint8_t *tmp = d;
    for ( ; len != 0; len--) *tmp++ = val;
}
