
struct USODATA {
    /* 0x00 */ u32 bootSize;
    /* 0x04 */ u32 _004;
    /* 0x08 */ u32 error;
    /* 0x0C */ u32 warning;
    /* 0x10 */ u32 _010;
    /* 0x14 */ u32 _014;
    /* 0x18 */ u32 _018;
    /* 0x1C */ u32 _01C;
    /* 0x20 */ u32 _020;
    /* 0x24 */ u32 _024;
    /* 0x28 */ u32 _028;
    /* 0x2C */ u32 _02C;

    /* 0x30 */ u32 _030;
    /* 0x34 */ u32 (*newFunc)(u32 siz, u32 align);
    /* 0x38 */ u32 _038;
    /* 0x3C */ u32 _03C;
    /* 0x40 */ u32 (*load)();
    /* 0x44 */ u32 (*destroy)();
    /* 0x48 */ u32 _048;
    /* 0x4C */ u32 _04C;
    /* 0x50 */ u32 _050;
    /* 0x54 */ u32 _054;
    /* 0x58 */ u32 _058;
    /* 0x5C */ u32 _05C;
    /* 0x60 */ u32 _060;
    /* 0x64 */ u32 _064;
    /* 0x68 */ u32 _068;
    /* 0x6C */ u32 _06C;
    /* 0x70 */ u32 (*getName)(u32 reg, u8 **buf, u32 *num);
    /* 0x74 */ u32 _074;
    /* 0x78 */ u32 _078;
    /* 0x7C */ u32 _07C;
    /* 0x80 */ u32 (*dmaFunc)(u32, u32, u32);
    /* 0x84 */ u32 (*printFunc)(const char *fmt, ...);
    /* 0x88 */ u32 _088;
    /* 0x8C */ u32 _08C;
    /* 0x90 */ u32 _090;
    /* 0x94 */ u32 (*timerFunc)();
    /* 0x98 */ u32 (*allocFunc)();
    /* 0x9C */ u32 (*freeFunc)();
};

extern struct USODATA *usodata;

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C"
#endif
void CheckStacks();
