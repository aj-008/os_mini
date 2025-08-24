#include "string.h"


/* itoa
 * Converts integer values into ASCII text in str
 * Bases available: 10, 16, 2
 * Assumes valid space in str
 */
void itoa(int n, char *str, int base) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        int rem = n % base;
        str[i++] = (rem < 10) ? rem + '0' : rem - 10 + 'A';
    } while ((n /= base) > 0);

    if (base == 16) {
        str[i++] = 'x';
        str[i++] = '0';
    } else if (base == 2) {
        str[i++] = 'b';
        str[i++] = '0';
    }

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    strrev(str);
}


/* strrev
 * Reverses target via a buffer tmp
 * Reversed string found in target
 */
void strrev(char *target) {
    int len = strlen(target) - 1;
    for (int i = 0; i < len; i++, len--) {
        char tmp = target[i];
        target[i] = target[len];
        target[len] = tmp;
    }
}


/* strlen
 * Returns length of s
 */
int strlen(char *s) {
    int n = 0;
    while (*s != '\0') {
        s++;
        n++;
    }
    return n;
}


/* strcmp
 * Returns 0 if s and t are equal, otherwise,
 * returns the difference between the pointers
 */
int strcmp(char *s, char *t) {
    while (*s && (*s == *t)) {
        s++;
        t++;
    }
    return *s - *t;
}


/* backspace
 * Replaces the last character of s with null char
 * Used in conjunction with printchar found in screen.h
 */
void backspace(char *s) {
    s[strlen(s) - 1] = '\0';
}


/* append
 * Adds n + null char to the end of s
 * Assumes valid space
 */
void append(char *s, char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

