#ifndef UTIL_H
#define UTIL_H
#include "stddef.h"
void memory_copy(char *target, const char *source, int length);
void itoa(int n, char *str, int base);
void str_rev(char *target);
int str_len(char *s);
void int_to_ascii(int n, char str[]);
#endif
