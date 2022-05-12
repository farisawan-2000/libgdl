#define NONMATCH
#define volatile
#include <ultra64.h>
#include "stdlib.hpp"


void _force_load_atan2f() {
    atan2f(0.0f, 0.0f);
}

void noprintf(const char *fmt, ...) {
    return;
}
// strcmp
// strstr

char* strcpy(char *dst, char *src) {
    int count = 1;

    while (*src) {
        *dst++ = *src++;
        count++;
    }

    return (char *)(dst - count - 1);
}


NONMATCH char *strcat(char *dst, char *src) {
    s32 count;

    while (*dst++ != 0) {
        count++;
    }

    if (*src != 0) {
        count--;

        *dst = *src;
        while (*src != 0) {
            *dst++ = *src++;
            count++;
        }
    }

    return dst - count - 1;
}

int toupper(int x) {
    return x & 0x5F;
}

NONMATCH u8 *strncpy(u8 *dst, u8 *src, s32 n) {
    s32 i;
    char tmp;

    for (i = 0; i < n; i++) {
        tmp = *src;

        *dst++ = *src++;

        if (tmp == 0) { // end of str
            i++; // skip curr
            i++; // skip \0 term
            while (i < n) {
                i += 1;
                *dst++ = 0;
            }
        } else {
            i++;
        }
    }
    return dst;
}

NONMATCH u8 *strrchr(u8 *s, int c) {
    u8 *rtnval = 0;

    while (*s++ != 0) {
        if (*s == c) rtnval = s - 1;
    }

    return (rtnval);
}

NONMATCH void *memset(char *s, int c, size_t n) {
    while (n-- != 0) {
        *s++ = c;
    }
    return s;
}

int puts(const char *) {
    return 0;
}

int atoi(char *s) {
    int ret;
    int i = 0;

    if (s[0] == '0' && s[1] == 'x') {
        char *hxd = &s[2];

        while (hxd != 0) {
            int digit;
            if (*hxd >= '0' && *hxd <= '9') {
                digit = *hxd - '0';
            } else if (*hxd >= 'a' && *hxd <= 'f') {
                digit = *hxd - 0x57;
            } else if (*hxd >= 'A' && *hxd <= 'F') {
                digit = *hxd - 0x37;
            }

            if (*(hxd + 1) != 0) {
                digit *= 16;
            }
            ret += digit;
        }

        return ret;
    } else {
        // handle ints
    }
    return 0;
}

double strtod(char *a0, char **a1) {
    return atoi(a0);
}

char* convstr2upper(char *arg0) {
    while (*arg0 != 0) {
        if ((*arg0 >= 0x61) && (*arg0 < 0x7B)) {
            *arg0 &= 0xDF;
        }
        arg0++;
    }
    return 0;
}

char *strdup(char *s) {
    char *ret = new char(strlen(s) + 1);

    if (ret == 0) {
        error("strdup(): out of memory");
    }

    strcpy(ret, s);

    return ret;
}

int strlen(char *s) {
    int ret = 0;
    while (*s++ != 0) ret++;

    return ret;
}

