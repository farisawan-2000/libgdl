#define volatile
#include <ultra64.h>

#include "stdlib.hpp"

struct DrawMode {
    u32 _000;
    u32 mode; // _004
};



char *GenChildName(char *child, char *parent) {
    char buf[64];

    strcpy(buf, child);
    strcat(buf, " (Child of ");
    strcat(buf, parent);
    strcat(buf, ")");
    return strdup(buf);
}

int BitNum(int number) {
    switch (number) {
        case 0x1:
            return 0;
        case 0x2:
            return 1;
        case 0x4:
            return 2;
        case 0x8:
            return 3;
        case 0x10:
            return 4;
        case 0x20:
            return 5;
        case 0x40:
            return 6;
        case 0x80:
            return 7;
        case 0x100:
            return 8;
        case 0x200:
            return 9;
        case 0x400:
            return 10;
        default:
            return 11;
    }
}

u32 RenderMode(DrawMode *dm) {
    u8 rm;
    s32 gfxMode;

    gfxMode = dm->mode;
    if (gfxMode & 0x80000 != 0) {
        return 0xC8000000;
    }
    if ((gfxMode & 0x80000 != 0) || (gfxMode & 0x800000)) {
        return 0x0C080000;
    }
    rm = gfxMode & 0xFF;
    if (gfxMode & 0x40000) {
        return 0x0C4C3078;
    }
    switch (rm) {                              /* irregular */
        case 0x0:
            return 0x0C084000;
        case 0x3:
            return 0x442478;
        case 0x22:
            return 0x442438;
        case 0x23:
            return 0x442438;
        case 0x21:
            return 0x442008;
        case 0x7:
            return 0x443078;
        case 0x6:
            return 0x443078;
        case 0x1B:
        case 0x1F:
            return 0x404DD8;
        case 0x9B:
        case 0x9F:
            return 0x40484DD8;
        case 0x80:
            return 0x0C084200;
        case 0x13:
            return 0x442D58;
        case 0xD:
            return 0x4041C8;
        case 0xB:
        case 0xF:
            return 0x4045D8;
        case 0x8B:
        case 0x8F:
            return 0x404845D8;
        case 0xCB:
            return 0x404845F8;
        case 0x1:
            return 0x442048;
        case 0x5:
            return 0x443048;
        case 0x2:
            return 0x442230;
        case 0xA:
            return 0x404A50;
        case 0x4A:
        case 0x4B:
            return 0x405078;
        case 0x4:
            return 0x0C087008;
        case 0x8:
            return 0x404240;
        case 0x9:
            return 0x4041C8;
    default:
        error("unsupported RM mode: %x", rm);
        return 0;
    }
}


unsigned int RenderMode2__FP8DrawMode();

class DisplayList {
    public:
        DisplayList(char *, u32, u32, u32, u32, u32) ;
};

void Reset__11DisplayListFv();

void Overflow__11DisplayListFv();

void PrintUsage__11DisplayListFv();

void GenSetCombineMode1__11DisplayListFP8DrawMode();

void GenSetCombineMode2__11DisplayListFP8DrawMode();

void GenSetCombineMode__11DisplayListFP8DrawMode();

void GenSetGeometryMode__11DisplayListFP8DrawMode();

void GenSetRenderMode__11DisplayListFP8DrawMode();

void GenSetCycleMode__11DisplayListFP8DrawMode();

void GenSetFogParms__11DisplayListFsT1R15rgba_t__pt__2_f();

void GenStartShape__11DisplayListFv();

void GenEndDraw__11DisplayListFv();

void GenSetColourBuffer__11DisplayListFPUsi();

void GenSetZBuffer__11DisplayListFPUs();

void GenEnd__11DisplayListFv();

void GenLoadTexBlock__11DisplayListFP12BaseMateriali();

void GenStartDraw__11DisplayListFP6Window();

void GenFrameBufferSetup__11DisplayListFPUsT1iT3R15rgba_t__pt__2_fN63();

class SubDisplayList {
    SubDisplayList(char *);
    SubDisplayList(char *, DisplayList *);
    SubDisplayList(char *, int, DisplayList *);
};

void SetParent__14SubDisplayListFP11DisplayList();
