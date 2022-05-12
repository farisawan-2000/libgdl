#define volatile

#include <ultra64.h>
#include "stdlib.hpp"
#include "app.hpp"

void *New(u32, u32);


void *operator new(u32 siz) {
    return New(siz, 0);
}

void *operator new(u32 siz, u32 align) {
    return New(siz, align);
}

void PrintBreak() {
    printf("*****************");
}

class MemHeap {
    public:
        void *MallocH(u32);
        void *MallocL(u32);
        void Free(void *);

        u32 _000;
        u32 _004;
        u32 _008;
        u32 _00C;
        u32 _010;
        u32 _014;
        u32 _018;
        u32 _01C;
        u32 _020;
};

static u32 memDebug;
static u32 __link;
class MemHeap heap;

void *New(u32 siz, u32 align) {
    void *memblk;

    if (align != 0) {
        siz += align;
    }

    if ((heap._020 == 1) || (heap._020 == 7)) {
        memblk = heap.MallocH(siz);
    } else {
        memblk = heap.MallocL(siz);
    }

    if (memblk == NULL) {
        App::PrintMemUsage();
        error("New(): Cant allocate %dk", siz >> 10);
    }

    if (memDebug != 0) {
        printf("%x = New(%d,%d, %d) (%.2fk)",
            memblk,
            ((u32*)memblk)[-4] >> 24,
            siz,
            align,
            siz / 1024.0f
        );
    }

    if (align != 0) {
        memblk = (void *) (((u32) memblk + align) & ~(align - 1));
    }

    return memblk;
}

CLINK void *CNew(u32 siz, u32 align) {
    return New(siz, align);
}

CLINK void CDelete(void *thing) {
    delete thing;
}

void operator delete(void *thing) {
    if (memDebug) {
        printf("delete (%x)", thing);
    }
    heap.Free(thing);
}

void linktest() {
    return;
}

// static initializer

App::App() {

}

void App::Init() {
    // s32 sp34;
    // s32 sp30;

    // memDebug = 0;
    // sys.GetMemory__6SysLibFPPvPUi(&sp34, &sp30);
    // heap.Init(sp34, sp34 + sp30);
    // App::MemoryLevel(0);
    // sysLinks.Init__11vLinkBufferFi(0x32);
    // app = this;
    // this->unkC = "App";
    // mem = MemTrackerMgr();
    // conMgr = ConsoleMgr();
    // BaseWindow::Def.unk4 = 2;
    // BaseWindow::Def.unk0 = 0;
    // BaseWindow::Def.unk10 = 0;
    // BaseWindow::Def.unk14 = 0;
    // BaseWindow::Def.screenHeight = 240; // _00C
    // BaseWindow::Def.screenWidth = 320; // _008
    // BaseWindow::Def.nearPlane = 100.0f; // _018
    // BaseWindow::Def.farPlane = 16000.0f; // _01c
    // BaseWindow::Def.unk0 = 0x406;
    // BaseWindow::Def.unk0 = 0x406 | 6 | 0x400;
    // BaseWindow::Def.unk2C = 1;
    // BaseWindow::Def.screenHeight = 0; // why?
    // BaseWindow::Def.screenWidth = 0;
    // BaseWindow::Def.unk4 = 0;
    // BaseWindow::Def.unk0 = 0;
    // Start__10MemTrackerSFPci("SysLib", 0);
    // sys.Init__6SysLibFv();
    // Stop__10MemTrackerSFv();
    // Start__10MemTrackerSFPci("GfxLib", 0);
    // gfx.Init__6GfxLibFv();
    // Stop__10MemTrackerSFv();

    // Controller *sController = new Controller; // size 0x84
    // if (sController != NULL) {
    //     sController.Init__10ControllerFi(1);
    // }
    // conMgr->unk34 = sController;
    // temp_a2 = this->unk28;
    // temp_a2->unk6C(temp_a2->unk68 + this);
    // sys.RunApp__6SysLibFP3App(this);
}
