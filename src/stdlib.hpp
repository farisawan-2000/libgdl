#ifndef STDLIB_H
#define STDLIB_H

typedef u32 size_t;
#define CLINK extern "C"

extern "C" {
    int strlen(char *);
    void error(char *, ...);
    void printf(const char *, ...);
    int atoi(char *);
    int puts(const char *);
    void *memset(char *s, int c, size_t n);
    int toupper(int x);
    char *strcat(char *, char *);
    float atan2f(float, float);
    void noprintf(const char *fmt, ...);
    u8 *strrchr(u8 *s, int c);
    char* strcpy(char *dst, char *src);
    char *strdup(char *s);
}


#endif
