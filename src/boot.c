#include <ultra64.h>

#include "boot.h"

#define STACKSIZE (0x2000 / sizeof(u64))

static OSThread mainThread;
static u64 mainThreadStack[STACKSIZE];

static OSThread idleThread;
static u64 idleThreadStack[STACKSIZE];

#define NUM_PI_MSGS 50
static OSMesg PiMessages[NUM_PI_MSGS];
static OSMesgQueue PiMessageQ;

Gfx someDL[] = {
    gsSPClearGeometryMode(G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0xFF60CDF8),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

OSThread *boottest() {
    return &idleThread;
}

void ReadDMA(u32 dst, u32 src, u32 len) {
    u32 remSize = 10000;

    while (len != 0) {
        if (len < remSize) {
            remSize = len;
        }

        SyncReadDMA(dst, src, remSize);
        len -= remSize;
        dst += remSize;
        src += remSize;
    }
}

void WriteDMA(s32 dst, s32 src, u32 len) {
    u32 remSize = 10000;
    
    while (len != 0) {
        if (len < remSize) {
            remSize = len;
        }

        SyncWriteDMA(dst, src, remSize);
        len -= remSize;
        dst += remSize;
        src += remSize;
    }
}

void tryload(char *filename) {
    s32 result;

    result = usodata->load();

    if (result < 0) {
        error("usoLoad() error loading file %s: %d", filename, result);
    }
}

void *CNew(u32 siz, u32 align);
int debugTime();
void *gdlAllocTemp();
void *gdlFreeTemp();

void main2(void *arg) {
    osCreateViManager(OS_PRIORITY_VIMGR);
    osCreatePiManager(OS_PRIORITY_PIMGR, &PiMessageQ, PiMessages, NUM_PI_MSGS);
    InitDMAqueue();
    osViSetMode(&osViModeTable[0]);
    osViSetSpecialFeatures(0x42);
    osViBlack(1);

    if (usodata != NULL) {
        if (usodata->warning != 0) {
            printf("USO warning num %d, data=%x, %x",
                usodata->warning,
                usodata->_014,
                usodata->_01C
            );
        }

        if (usodata->error != 0) {
            error("USO error num %d, data=%x", usodata->error, usodata->_010);
        }

        printf("Bootup Code size %dk", (0x80000000 + usodata->bootSize) >> 10);
        usodata->dmaFunc = ReadDMA;
        usodata->newFunc = CNew;
        usodata->printFunc = printf;
        usodata->allocFunc = gdlAllocTemp;
        usodata->freeFunc = gdlFreeTemp;
        usodata->timerFunc = debugTime;
    }

    main();
}

void reset(void) {
    u32 result;

    usodata->newFunc = usodata->_030;
    usodata->destroy("mainuso");

    result = usodata->load("mainuso");
    if (result != 0) {
        error("cant reload mainuso %d", result);
    }

    printf("ret=%d", result);
    printf("memory %x %x", usodata->bootSize, usodata->_004);
}

void idle(void *arg) {
    osCreateThread(&mainThread, 2, main2, 0, mainThreadStack + STACKSIZE, 0xA);
    mainThreadStack[0] = 0x1234567812345678;
    osStartThread(&mainThread);
    osSetThreadPri(0, 0);
    while (1) {

    }
}

void CheckStacks(void) {
    if (mainThreadStack[0] != 0x1234567812345678) {
        error("mainThread stack overflow");
    }
    if (idleThreadStack[0] != 0x1234567812345678) {
        error("idleThread stack overflow");
    }
}

void boot(u32 bs, u32 a1) {
    InitMem(bs, a1);
    osInitialize();
    osCreateThread(&idleThread, 1, idle, 0, idleThreadStack + STACKSIZE, 1);
    idleThreadStack[0] = 0x1234567812345678;
    osStartThread(&idleThread);
}

void simpleboot() {
    osInitialize();
    osCreateThread(&idleThread, 1, idle, 0, idleThreadStack + STACKSIZE, 1);
    idleThreadStack[0] = 0x1234567812345678;
    osStartThread(&idleThread);
}

void usomain(struct USODATA *u) {
    usodata = u;
    boot(u->bootSize, u->_004);
}

void _main() {

}

void __vec_new() {

}


