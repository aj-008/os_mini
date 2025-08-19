#include "string.h"

void itoa(int n, char *str, int base) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    strrev(str);
}

void strrev(char *target) {
    int len = strlen(target) - 1;
    for (int i = 0; i < len; i++, len--) {
        char tmp = target[i];
        target[i] = target[len];
        target[len] = tmp;
    }
}

int strlen(char *s) {
    int n = 0;
    while (*s != '\0') {
        s++;
        n++;
    }
    return n;
}

int strcmp(char *s, char *t) {
    while (*s && (*s == *t)) {
        s++;
        t++;
    }
    return *s - *t;
}

void backspace(char *s) {
    s[strlen(s) - 1] = '\0';
}

void append(char *s, char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

