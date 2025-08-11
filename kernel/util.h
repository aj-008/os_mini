#ifndef UTIL_H
#define UTIL_H
#include "stddef.h"
void memory_copy(char *target, const char *source, int length);
void itoa(int n, char *str, int base);
void strrev(char *target, int length);
void int_to_ascii(int n, char str[]);
#endif
