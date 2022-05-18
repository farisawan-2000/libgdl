#define volatile
#include <ultra64.h>

#include "stdlib.hpp"

// begin file /usr/include/PR/os_vi.h
#include "dl.hpp"
// begin file /usr/include/PR/os_convert.h
// begin file /usr/include/PR/os.h
// begin file /usr/include/ultra64.h
// begin file ..//include/math.hpp
// begin file ..//include/shapefmt.hpp
// begin file ..//include/shape.hpp
// begin file ..//include/app.hpp
// begin file ..//include/stdgfx.hpp
// begin file ..//u64/include/gfxlib.hpp
// begin file ..//include/stdsys.hpp
// begin file ..//include/string.h
// begin file ..//u64/include/syslib.hpp
// begin file dl.cpp

u8 *GenChildName(char *child, char *parent) {
    char buf[64];

    strcpy(buf, child);
    strcat(buf, " (Child of ");
    strcat(buf, parent);
    strcat(buf, ")");
    return (u8*)strdup(buf);
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
    switch (rm) {
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

u32 RenderMode2(DrawMode *dm) {
    u8 rm  = dm->mode;

    switch (rm) {
        case 0x0:
            return 0x03024000;
        case 0x3:
            return 0x112478;
        case 0x23:
            return 0x112438;
        case 0x7:
            return 0x113078;
        case 0x6:
            return 0x113078;
        case 0x1B:
        case 0x1F:
            return 0x20004DD8;
        case 0xB:
        case 0xF:
            return 0x1045D8;
        case 0x1:
            return 0x112048;
        case 0x5:
            return 0x113048;
        case 0x2:
            return 0x112230;
        case 0xA:
            return 0x104A50;
        case 0x4A:
            return 0x105078;
        case 0x4:
            return 0x03027008;
        case 0x8:
            return 0x104240;
        case 0x9:
            return 0x1041C8;
        default:
            error("unsupported RM2 mode: %x", rm);
            return 0;
    }
}

DisplayList::DisplayList(char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) {

}

void DisplayList::Reset(void) {
    // this->_078 &= -2;
    // this->unk4 = 0;
    // this->unk14 = 0;
    // this->unk24 = 0;
    // this->unk34 = 0;
    // this->unk44 = 0;
    // this->unk54 = 0;
    // this->unk60 = this->unkC->unk0 + (this->unkC->unk4 * 8);
    // this->unk64 = this->unkC->unk4;
}

void DisplayList::Overflow(void) {
    // this->PrintUsage();
    // error("something in '%s' DisplayList overflowed", this->_070);
}

void DisplayList::PrintUsage(void) {
    // s32 sp7C;
    // s32 sp74;
    // s32 sp6C;
    // s32 sp64;
    // s32 sp5C;
    // s32 sp54;
    // s32 sp4C;
    // void *temp_t0;
    // void *temp_t1;
    // void *temp_t2;
    // void *temp_t3;
    // void *temp_v0;
    // void *temp_v1;

    // temp_t0 = this->unk2C;
    // temp_v1 = this->unk1C;
    // temp_v0 = this->unkC;
    // sp7C = temp_t0->unk8;
    // temp_t1 = this->unk3C;
    // sp74 = temp_t1->unk4;
    // sp6C = temp_t1->unk8;
    // temp_t2 = this->unk4C;
    // sp64 = temp_t2->unk4;
    // sp5C = temp_t2->unk8;
    // temp_t3 = this->unk5C;
    // sp54 = temp_t3->unk4;
    // sp4C = temp_t3->unk8;
    // printf("%s : Gfx %d/%d, Vtx %d/%d, Light %d/%d, Mtx %d/%d, Vp %d/%d, Hilite %d/%d",
    //     this->unk70, //nm
    //     temp_v0->unk4, //usedGFX
    //     temp_v0->unk8, //totGFX
    //     temp_v1->unk4, //usedVTX
    //     temp_v1->unk8, //totVTX
    //     temp_t0->unk4, //usedLIGHT
    //     sp7C,          //totLIGHT
    //     sp74,          //usedMTX
    //     sp6C,          //totMTX
    //     sp64,          //used VP
    //     sp5C,          // total VP
    //     sp54,          // used HILIGHT
    //     sp4C           // tot HIGHLITE
    // );
}

void DisplayList::GenSetCombineMode1(DrawMode*) {
    // s32 temp_a2;
    // s32 temp_v0;
    // s32 temp_v1;
    // s32 temp_v1_10;
    // s32 temp_v1_11;
    // s32 temp_v1_12;
    // s32 temp_v1_2;
    // s32 temp_v1_3;
    // s32 temp_v1_4;
    // s32 temp_v1_5;
    // s32 temp_v1_6;
    // s32 temp_v1_7;
    // s32 temp_v1_8;
    // s32 temp_v1_9;
    // void *temp_a0;
    // void *temp_a0_10;
    // void *temp_a0_11;
    // void *temp_a0_12;
    // void *temp_a0_13;
    // void *temp_a0_2;
    // void *temp_a0_3;
    // void *temp_a0_4;
    // void *temp_a0_5;
    // void *temp_a0_6;
    // void *temp_a0_7;
    // void *temp_a0_8;
    // void *temp_a0_9;
    // void *temp_a1;
    // void *temp_a1_10;
    // void *temp_a1_11;
    // void *temp_a1_12;
    // void *temp_a1_13;
    // void *temp_a1_2;
    // void *temp_a1_3;
    // void *temp_a1_4;
    // void *temp_a1_5;
    // void *temp_a1_6;
    // void *temp_a1_7;
    // void *temp_a1_8;
    // void *temp_a1_9;
    // s32 phi_v0;
    // void *phi_a0;
    // s32 phi_v0_2;
    // void *phi_a0_2;
    // s32 phi_v0_3;
    // void *phi_a0_3;
    // s32 phi_v0_4;
    // void *phi_a0_4;
    // s32 phi_v0_5;
    // void *phi_a0_5;
    // s32 phi_v0_6;
    // void *phi_a0_6;
    // s32 phi_v0_7;
    // void *phi_a0_7;
    // s32 phi_v0_8;
    // void *phi_a0_8;
    // s32 phi_v0_9;
    // void *phi_a0_9;
    // s32 phi_v0_10;
    // void *phi_a0_10;
    // s32 phi_v0_11;
    // void *phi_a0_11;
    // s32 phi_v0_12;
    // void *phi_a0_12;
    // s32 phi_v0_13;
    // void *phi_a0_13;

    // temp_a2 = dm->unk4 & 0xF00;
    // switch (temp_a2) {                              /* irregular */
    // case 0x0:
    //     temp_a0 = this->unkC;
    //     phi_v0_13 = 0;
    //     phi_a0_13 = temp_a0;
    //     if (temp_a0->unk8 < (temp_a0->unk4 + 1)) {
    //         phi_v0_13 = 1;
    //     }
    //     if (phi_v0_13 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_13 = this->unkC;
    //     }
    //     temp_v0 = phi_a0_13->unk4;
    //     phi_a0_13->unk4 = temp_v0 + 1;
    //     temp_a1 = *this->unkC + (temp_v0 * 8);
    //     temp_a1->unk0 = 0xFCFFFFFF;
    //     temp_a1->unk4 = 0xFFFE793C;
    //     return;
    // case 0x400:
    //     temp_a0_2 = this->unkC;
    //     phi_v0_12 = 0;
    //     phi_a0_12 = temp_a0_2;
    //     if (temp_a0_2->unk8 < (temp_a0_2->unk4 + 1)) {
    //         phi_v0_12 = 1;
    //     }
    //     if (phi_v0_12 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_12 = this->unkC;
    //     }
    //     temp_v1 = phi_a0_12->unk4;
    //     phi_a0_12->unk4 = temp_v1 + 1;
    //     temp_a1_2 = *this->unkC + (temp_v1 * 8);
    //     temp_a1_2->unk0 = 0xFCFFFFFF;
    //     temp_a1_2->unk4 = 0xFFFDF6FB;
    //     return;
    // case 0x700:
    //     temp_a0_3 = this->unkC;
    //     phi_v0_11 = 0;
    //     phi_a0_11 = temp_a0_3;
    //     if (temp_a0_3->unk8 < (temp_a0_3->unk4 + 1)) {
    //         phi_v0_11 = 1;
    //     }
    //     if (phi_v0_11 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_11 = this->unkC;
    //     }
    //     temp_v1_2 = phi_a0_11->unk4;
    //     phi_a0_11->unk4 = temp_v1_2 + 1;
    //     temp_a1_3 = *this->unkC + (temp_v1_2 * 8);
    //     temp_a1_3->unk0 = 0xFC41C683;
    //     temp_a1_3->unk4 = 0xFF8FFFFF;
    //     return;
    // case 0x100:
    //     temp_a0_4 = this->unkC;
    //     phi_v0_10 = 0;
    //     phi_a0_10 = temp_a0_4;
    //     if (temp_a0_4->unk8 < (temp_a0_4->unk4 + 1)) {
    //         phi_v0_10 = 1;
    //     }
    //     if (phi_v0_10 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_10 = this->unkC;
    //     }
    //     temp_v1_3 = phi_a0_10->unk4;
    //     phi_a0_10->unk4 = temp_v1_3 + 1;
    //     temp_a1_4 = *this->unkC + (temp_v1_3 * 8);
    //     temp_a1_4->unk0 = 0xFCFFFFFF;
    //     temp_a1_4->unk4 = 0xFFFCF279;
    //     return;
    // case 0x600:
    //     temp_a0_5 = this->unkC;
    //     phi_v0_9 = 0;
    //     phi_a0_9 = temp_a0_5;
    //     if (temp_a0_5->unk8 < (temp_a0_5->unk4 + 1)) {
    //         phi_v0_9 = 1;
    //     }
    //     if (phi_v0_9 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_9 = this->unkC;
    //     }
    //     temp_v1_4 = phi_a0_9->unk4;
    //     phi_a0_9->unk4 = temp_v1_4 + 1;
    //     temp_a1_5 = *this->unkC + (temp_v1_4 * 8);
    //     temp_a1_5->unk0 = 0xFC60FEC1;
    //     temp_a1_5->unk4 = 0x44FE773B;
    //     return;
    // case 0x200:
    //     temp_a0_6 = this->unkC;
    //     phi_v0_8 = 0;
    //     phi_a0_8 = temp_a0_6;
    //     if (temp_a0_6->unk8 < (temp_a0_6->unk4 + 1)) {
    //         phi_v0_8 = 1;
    //     }
    //     if (phi_v0_8 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_8 = this->unkC;
    //     }
    //     temp_v1_5 = phi_a0_8->unk4;
    //     phi_a0_8->unk4 = temp_v1_5 + 1;
    //     temp_a1_6 = *this->unkC + (temp_v1_5 * 8);
    //     temp_a1_6->unk0 = 0xFC30B261;
    //     temp_a1_6->unk4 = 0x44664924;
    //     return;
    // case 0x300:
    //     temp_a0_7 = this->unkC;
    //     phi_v0_7 = 0;
    //     phi_a0_7 = temp_a0_7;
    //     if (temp_a0_7->unk8 < (temp_a0_7->unk4 + 1)) {
    //         phi_v0_7 = 1;
    //     }
    //     if (phi_v0_7 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_7 = this->unkC;
    //     }
    //     temp_v1_6 = phi_a0_7->unk4;
    //     phi_a0_7->unk4 = temp_v1_6 + 1;
    //     temp_a1_7 = *this->unkC + (temp_v1_6 * 8);
    //     temp_a1_7->unk0 = 0xFC121824;
    //     temp_a1_7->unk4 = 0xFF33FFFF;
    //     return;
    // case 0x500:
    //     temp_a0_8 = this->unkC;
    //     phi_v0_6 = 0;
    //     phi_a0_6 = temp_a0_8;
    //     if (temp_a0_8->unk8 < (temp_a0_8->unk4 + 1)) {
    //         phi_v0_6 = 1;
    //     }
    //     if (phi_v0_6 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_6 = this->unkC;
    //     }
    //     temp_v1_7 = phi_a0_6->unk4;
    //     phi_a0_6->unk4 = temp_v1_7 + 1;
    //     temp_a1_8 = *this->unkC + (temp_v1_7 * 8);
    //     temp_a1_8->unk0 = 0xFC30B261;
    //     temp_a1_8->unk4 = 0xFF67FFFF;
    //     return;
    // case 0x900:
    //     temp_a0_9 = this->unkC;
    //     phi_v0_5 = 0;
    //     phi_a0_5 = temp_a0_9;
    //     if (temp_a0_9->unk8 < (temp_a0_9->unk4 + 1)) {
    //         phi_v0_5 = 1;
    //     }
    //     if (phi_v0_5 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_5 = this->unkC;
    //     }
    //     temp_v1_8 = phi_a0_5->unk4;
    //     phi_a0_5->unk4 = temp_v1_8 + 1;
    //     temp_a1_9 = *this->unkC + (temp_v1_8 * 8);
    //     temp_a1_9->unk0 = 0xFC30B261;
    //     temp_a1_9->unk4 = 0x5566FF7F;
    //     return;
    // case 0xA00:
    //     temp_a0_10 = this->unkC;
    //     phi_v0_4 = 0;
    //     phi_a0_4 = temp_a0_10;
    //     if (temp_a0_10->unk8 < (temp_a0_10->unk4 + 1)) {
    //         phi_v0_4 = 1;
    //     }
    //     if (phi_v0_4 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_4 = this->unkC;
    //     }
    //     temp_v1_9 = phi_a0_4->unk4;
    //     phi_a0_4->unk4 = temp_v1_9 + 1;
    //     temp_a1_10 = *this->unkC + (temp_v1_9 * 8);
    //     temp_a1_10->unk0 = 0xFC40B281;
    //     temp_a1_10->unk4 = 0x3365FEFF;
    //     return;
    // case 0x800:
    //     temp_a0_11 = this->unkC;
    //     phi_v0_3 = 0;
    //     phi_a0_3 = temp_a0_11;
    //     if (temp_a0_11->unk8 < (temp_a0_11->unk4 + 1)) {
    //         phi_v0_3 = 1;
    //     }
    //     if (phi_v0_3 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_3 = this->unkC;
    //     }
    //     temp_v1_10 = phi_a0_3->unk4;
    //     phi_a0_3->unk4 = temp_v1_10 + 1;
    //     temp_a1_11 = *this->unkC + (temp_v1_10 * 8);
    //     temp_a1_11->unk0 = 0xFC127E24;
    //     temp_a1_11->unk4 = -0x805;
    //     return;
    // case 0xC00:
    //     temp_a0_12 = this->unkC;
    //     phi_v0_2 = 0;
    //     phi_a0_2 = temp_a0_12;
    //     if (temp_a0_12->unk8 < (temp_a0_12->unk4 + 1)) {
    //         phi_v0_2 = 1;
    //     }
    //     if (phi_v0_2 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_2 = this->unkC;
    //     }
    //     temp_v1_11 = phi_a0_2->unk4;
    //     phi_a0_2->unk4 = temp_v1_11 + 1;
    //     temp_a1_12 = *this->unkC + (temp_v1_11 * 8);
    //     temp_a1_12->unk0 = 0xFC11FE23;
    //     temp_a1_12->unk4 = -0x805;
    //     return;
    // case 0xD00:
    //     temp_a0_13 = this->unkC;
    //     phi_v0 = 0;
    //     phi_a0 = temp_a0_13;
    //     if (temp_a0_13->unk8 < (temp_a0_13->unk4 + 1)) {
    //         phi_v0 = 1;
    //     }
    //     if (phi_v0 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0 = this->unkC;
    //     }
    //     temp_v1_12 = phi_a0->unk4;
    //     phi_a0->unk4 = temp_v1_12 + 1;
    //     temp_a1_13 = *this->unkC + (temp_v1_12 * 8);
    //     temp_a1_13->unk0 = 0xFCFFB3FF;
    //     temp_a1_13->unk4 = 0xFF65FEFF;
    //     return;
    // default:
    //     error(&sr, temp_a2, temp_a2, this);
    //     return;
    // }
}

void DisplayList::GenSetCombineMode2(DrawMode*) {
    // s32 temp_a2;
    // s32 temp_v0;
    // s32 temp_v0_2;
    // s32 temp_v1;
    // s32 temp_v1_2;
    // s32 temp_v1_3;
    // s32 temp_v1_4;
    // s32 temp_v1_5;
    // s32 temp_v1_6;
    // s32 temp_v1_7;
    // s32 temp_v1_8;
    // s32 temp_v1_9;
    // void *temp_a0;
    // void *temp_a0_10;
    // void *temp_a0_2;
    // void *temp_a0_3;
    // void *temp_a0_4;
    // void *temp_a0_5;
    // void *temp_a0_6;
    // void *temp_a0_7;
    // void *temp_a0_8;
    // void *temp_a0_9;
    // void *temp_a1;
    // void *temp_a1_10;
    // void *temp_a1_2;
    // void *temp_a1_3;
    // void *temp_a1_4;
    // void *temp_a1_5;
    // void *temp_a1_6;
    // void *temp_a1_7;
    // void *temp_a1_8;
    // void *temp_a1_9;
    // s32 phi_v0;
    // void *phi_a0;
    // s32 phi_v0_2;
    // void *phi_a0_2;
    // s32 phi_v0_3;
    // void *phi_a0_3;
    // s32 phi_v0_4;
    // void *phi_a0_4;
    // s32 phi_v0_5;
    // void *phi_a0_5;
    // s32 phi_v0_6;
    // void *phi_a0_6;
    // s32 phi_v0_7;
    // void *phi_a0_7;
    // s32 phi_v0_8;
    // void *phi_a0_8;
    // s32 phi_v0_9;
    // void *phi_a0_9;
    // s32 phi_v0_10;
    // void *phi_a0_10;

    // temp_v0 = dm->unk4;
    // temp_a2 = temp_v0 & 0xF00;
    // switch (temp_a2) {                              /* irregular */
    // case 0x0:
    //     temp_a0 = this->unkC;
    //     phi_v0_10 = 0;
    //     phi_a0_10 = temp_a0;
    //     if (temp_a0->unk8 < (temp_a0->unk4 + 1)) {
    //         phi_v0_10 = 1;
    //     }
    //     if (phi_v0_10 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_10 = this->unkC;
    //     }
    //     temp_v0_2 = phi_a0_10->unk4;
    //     phi_a0_10->unk4 = temp_v0_2 + 1;
    //     temp_a1 = *this->unkC + (temp_v0_2 * 8);
    //     temp_a1->unk0 = 0xFCFFFFFF;
    //     temp_a1->unk4 = 0xFFFE7838;
    //     return;
    // case 0x400:
    //     temp_a0_2 = this->unkC;
    //     phi_v0_9 = 0;
    //     phi_a0_9 = temp_a0_2;
    //     if (temp_a0_2->unk8 < (temp_a0_2->unk4 + 1)) {
    //         phi_v0_9 = 1;
    //     }
    //     if (phi_v0_9 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_9 = this->unkC;
    //     }
    //     temp_v1 = phi_a0_9->unk4;
    //     phi_a0_9->unk4 = temp_v1 + 1;
    //     temp_a1_2 = *this->unkC + (temp_v1 * 8);
    //     temp_a1_2->unk0 = 0xFCFFFFFF;
    //     temp_a1_2->unk4 = 0xFFFDF638;
    //     return;
    // case 0x100:
    //     temp_a0_3 = this->unkC;
    //     phi_v0_8 = 0;
    //     phi_a0_8 = temp_a0_3;
    //     if (temp_a0_3->unk8 < (temp_a0_3->unk4 + 1)) {
    //         phi_v0_8 = 1;
    //     }
    //     if (phi_v0_8 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_8 = this->unkC;
    //     }
    //     temp_v1_2 = phi_a0_8->unk4;
    //     phi_a0_8->unk4 = temp_v1_2 + 1;
    //     temp_a1_3 = *this->unkC + (temp_v1_2 * 8);
    //     temp_a1_3->unk0 = 0xFCFFFFFF;
    //     temp_a1_3->unk4 = 0xFFFCF238;
    //     return;
    // case 0x200:
    // case 0x600:
    //     temp_a0_4 = this->unkC;
    //     phi_v0_7 = 0;
    //     phi_a0_7 = temp_a0_4;
    //     if (temp_a0_4->unk8 < (temp_a0_4->unk4 + 1)) {
    //         phi_v0_7 = 1;
    //     }
    //     if (phi_v0_7 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_7 = this->unkC;
    //     }
    //     temp_v1_3 = phi_a0_7->unk4;
    //     phi_a0_7->unk4 = temp_v1_3 + 1;
    //     temp_a1_4 = *this->unkC + (temp_v1_3 * 8);
    //     temp_a1_4->unk0 = 0xFC30B3FF;
    //     temp_a1_4->unk4 = 0x4FFE4838;
    //     return;
    // case 0x500:
    //     temp_a0_5 = this->unkC;
    //     phi_v0_6 = 0;
    //     phi_a0_6 = temp_a0_5;
    //     if (temp_a0_5->unk8 < (temp_a0_5->unk4 + 1)) {
    //         phi_v0_6 = 1;
    //     }
    //     if (phi_v0_6 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_6 = this->unkC;
    //     }
    //     temp_v1_4 = phi_a0_6->unk4;
    //     phi_a0_6->unk4 = temp_v1_4 + 1;
    //     temp_a1_5 = *this->unkC + (temp_v1_4 * 8);
    //     temp_a1_5->unk0 = 0xFC30B3FF;
    //     temp_a1_5->unk4 = -0x1C8;
    //     return;
    // case 0xA00:
    //     temp_a0_6 = this->unkC;
    //     phi_v0_5 = 0;
    //     phi_a0_5 = temp_a0_6;
    //     if (temp_a0_6->unk8 < (temp_a0_6->unk4 + 1)) {
    //         phi_v0_5 = 1;
    //     }
    //     if (phi_v0_5 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_5 = this->unkC;
    //     }
    //     temp_v1_5 = phi_a0_5->unk4;
    //     phi_a0_5->unk4 = temp_v1_5 + 1;
    //     temp_a1_6 = *this->unkC + (temp_v1_5 * 8);
    //     temp_a1_6->unk0 = 0xFC40B3FF;
    //     temp_a1_6->unk4 = 0x3FFDFE38;
    //     return;
    // case 0xB00:
    //     temp_a0_7 = this->unkC;
    //     phi_v0_4 = 0;
    //     phi_a0_4 = temp_a0_7;
    //     if (temp_a0_7->unk8 < (temp_a0_7->unk4 + 1)) {
    //         phi_v0_4 = 1;
    //     }
    //     if (phi_v0_4 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_4 = this->unkC;
    //     }
    //     temp_v1_6 = phi_a0_4->unk4;
    //     phi_a0_4->unk4 = temp_v1_6 + 1;
    //     temp_a1_7 = *this->unkC + (temp_v1_6 * 8);
    //     temp_a1_7->unk0 = 0xFC40E3FF;
    //     temp_a1_7->unk4 = 0x3FFDCE38;
    //     return;
    // case 0x900:
    //     temp_a0_8 = this->unkC;
    //     phi_v0_3 = 0;
    //     phi_a0_3 = temp_a0_8;
    //     if (temp_a0_8->unk8 < (temp_a0_8->unk4 + 1)) {
    //         phi_v0_3 = 1;
    //     }
    //     if (phi_v0_3 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_3 = this->unkC;
    //     }
    //     temp_v1_7 = phi_a0_3->unk4;
    //     phi_a0_3->unk4 = temp_v1_7 + 1;
    //     temp_a1_8 = *this->unkC + (temp_v1_7 * 8);
    //     temp_a1_8->unk0 = 0xFC30B3FF;
    //     temp_a1_8->unk4 = 0x5FFEFE38;
    //     return;
    // case 0x300:
    //     if (temp_v0 & 0x80000) {
    //         temp_a0_9 = this->unkC;
    //         phi_v0 = 0;
    //         phi_a0 = temp_a0_9;
    //         if (temp_a0_9->unk8 < (temp_a0_9->unk4 + 1)) {
    //             phi_v0 = 1;
    //         }
    //         if (phi_v0 != 0) {
    //             this->Overflow(temp_a2, this);
    //             phi_a0 = this->unkC;
    //         }
    //         temp_v1_8 = phi_a0->unk4;
    //         phi_a0->unk4 = temp_v1_8 + 1;
    //         temp_a1_9 = *this->unkC + (temp_v1_8 * 8);
    //         temp_a1_9->unk0 = 0xFC127FFF;
    //         temp_a1_9->unk4 = -0xDC8;
    //         return;
    //     }
    //     temp_a0_10 = this->unkC;
    //     phi_v0_2 = 0;
    //     phi_a0_2 = temp_a0_10;
    //     if (temp_a0_10->unk8 < (temp_a0_10->unk4 + 1)) {
    //         phi_v0_2 = 1;
    //     }
    //     if (phi_v0_2 != 0) {
    //         this->Overflow(temp_a2, this);
    //         phi_a0_2 = this->unkC;
    //     }
    //     temp_v1_9 = phi_a0_2->unk4;
    //     phi_a0_2->unk4 = temp_v1_9 + 1;
    //     temp_a1_10 = *this->unkC + (temp_v1_9 * 8);
    //     temp_a1_10->unk0 = 0xFC257E04;
    //     temp_a1_10->unk4 = 0x1FFCF3F8;
    //     return;
    // default:
    //     error(&D_00000000, temp_a2, temp_a2, this);
    //     return;
    // }
}

void DisplayList::GenSetCombineMode(DrawMode *dm) {
    if (((dm->mode << 0xC) < 0) || (dm->mode & 0x800000)) {
        this->GenSetCombineMode2(dm);
    } else {
        this->GenSetCombineMode1(dm);
    }
}

void DisplayList::GenSetGeometryMode(DrawMode*) {

}

void DisplayList::GenSetRenderMode(DrawMode*) {

}

void DisplayList::GenSetCycleMode(DrawMode*) {

}

void DisplayList::GenSetFogParms(short,short,rgba_t<float>&) {

}

void DisplayList::GenStartShape(void) {

}

void DisplayList::GenEndDraw(void) {
    // s32 v0 = 0;

    // if (this->unkC[2] < (this->unkC[1] + 1)) {
    //     v0 = 1;
    // }
    // if (v0 != 0) {
    //     this->Overflow();
    // }

    // gDPFullSync(this->unkC[this->unkC[1]++ * 2]);
    // this->GenEnd();
}



void DisplayList::GenSetColourBuffer(unsigned short*,int) {

}

void DisplayList::GenSetZBuffer(unsigned short*) {

}

void DisplayList::GenEnd(void) {

}

void DisplayList::GenLoadTexBlock(BaseMaterial*,int) {
 // good luck have fun
}

void DisplayList::GenStartDraw(Window*) {

}

void DisplayList::GenFrameBufferSetup(unsigned short*,unsigned short*,int,int,rgba_t<float>&,int,int,int,int,int,int) {

}

SubDisplayList::SubDisplayList(char *) {

}

SubDisplayList::SubDisplayList(char *, DisplayList *) {

}

SubDisplayList::SubDisplayList(char *, int, DisplayList *) {

}

void SubDisplayList::SetParent(DisplayList*) {

}
