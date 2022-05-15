#define volatile
#include <ultra64.h>
#include <stdlib.h>
#include <stdarg.h>
#include <align.h>
#include <PR/os_internal.h>
#include "stdlib.hpp"
#include "syslib.hpp"
#include "console.hpp"
#include "boot.h"

extern "C" void *gdlAllocTemp(u32 siz) {
    return sys.AllocTempBuffer(siz);
}

extern "C" void gdlFreeTemp(void *thing) {
    sys.FreeTempBuffer(thing);
}

extern "C" f32 debugTime(void) {
    // return GetTime__6SysLibFv(&sys) / gfx._20C; // _20C is an f32
    return 0.0f;
}

extern "C" void __assert(char *cond, char *file, u32 line) {
    error("Assertion failed: '%s' in file '%s' line %d", cond, file, line);
}


// DONT be fooled here; all references to `printStream` are actually
//  struct members within `printStream`!
// use the asm for reference!!!
void istest(void) {
    // char buf[50];

    // strcpy(buf, "arse");
    // printStream.GetAccess();
    // phi_s5 = &buf;
    // for (phi_s4 = 8; phi_s4 >= 0; phi_s4--) {
    //     temp_a0 = phi_s5 & 7;
    //     temp_v0 = printStream - printStream;
    //     phi_s2 = phi_s4;
    //     if (temp_v0 < phi_s4) {
    //         phi_s2 = temp_v0;
    //     }
    //     phi_s2_2 = phi_s2;
    //     phi_s2_3 = phi_s2;
    //     phi_s2_4 = phi_s2;
    //     if (phi_s2 != 0) {
    //         if (temp_a0 != 0) {
    //             temp_v1 = 8 - temp_a0;
    //             phi_v0 = 0;
    //             if (temp_v1 < phi_s2) {
    //                 phi_s2_2 = temp_v1;
    //             }
    //             phi_s2_3 = phi_s2_2;
    //             if (phi_s2_2 != 0) {
    //                 phi_v1 = phi_s5;
    //                 phi_a0 = &printStream;
    //                 do {
    //                     temp_v0_2 = phi_v0 + 1;
    //                     temp_a0_2 = phi_a0 + 1;
    //                     temp_a0_2->unk-1 = *phi_v1;
    //                     phi_v1 += 1;
    //                     phi_a0 = temp_a0_2;
    //                     phi_v0 = temp_v0_2;
    //                 } while (temp_v0_2 < phi_s2_2);
    //             }
    //             RawWrite__8isStreamFUlPvT1(&printStream, printStream, &printStream, phi_s2_2);
    //         } else {
    //             RawWrite__8isStreamFUlPvT1(&printStream, printStream, phi_s5, phi_s2);
    //         }
    //         temp_a2 = printStream + phi_s2_3;
    //         printStream = temp_a2;
    //         RawWrite__8isStreamFUlT1(&printStream, printStream, temp_a2);
    //         phi_s2_4 = phi_s2_3;
    //     }
    //     temp_t3 = printStream;
    //     if (printStream == temp_t3) {
    //         printStream = temp_t3;
    //         RawWrite__8isStreamFUlT1(&printStream, printStream + 0xC, temp_t3);
    //         if (printStream != printStream) {
    //             Error__8isStreamFPc(&printStream, &D_00000000);
    //         }
    //         RawWrite__8isStreamFUlT1(&printStream, printStream + 8, 0x12340001);
    //         while (printStream.RawRead(printStream + 8) != 0x12340002);
    //         temp_a2_2 = printStream;
    //         printStream = temp_a2_2;
    //         RawWrite__8isStreamFUlT1(&printStream, printStream, temp_a2_2);
    //         RawWrite__8isStreamFUlT1(&printStream, printStream + 8, 0x12340003);
    //         while (printStream.RawRead(printStream + 8) != 0x12340002);
    //     }
    //     temp_s4 = phi_s4 - phi_s2_4;
    //     phi_s4 = temp_s4;
    //     phi_s5 += phi_s2_4;
    //     if (temp_s4 < 0) {
    //         printStream.Error(&D_00000000);
    //     }
    //     if (temp_s4 != 0) {
    //         printStream.Yield();
    //     }
    // }
    // printStream.RelAccess();
}

struct DMAThing {
    /* 0x000 */ OSIoMesg mesg;
    /* 0x018 */ OSMesgQueue mq;
    /* 0x030 */ void *_030;
    /* 0x034 */ void *_034;
    /* 0x038 */ u32 _038;
    /* 0x03C */ u32 _03C;
    /* 0x040 */ u32 _040;
};

// check if 9 or 10
extern DMAThing DMAqueue[10];

void DoReadDMA(s32 idx, void *dst, void *src, u32 len) {
    DMAThing *dma;

    if ((u32)dst & 0x7) {
        error("read not aligned %d %x", idx, dst);
    }
    if ((u32)len & 1) {
        error("bad read len %d", len);
    }

    dma = &DMAqueue[idx];
    dma->_03C = 1;
    SysLib::WritebackDCache(dst, len);
    osPiStartDma(&dma->mesg, 0, OS_READ, (u32) src, dst, len, &dma->mq);
    dma->_034 = dst;
    dma->_038 = len;
    dma->_040 = 1;
}

void DoWriteDMA(s32 idx, void *dst, void *src, u32 len) {
    DMAThing *dma;

    if ((u32)dst & 0x7) {
        error("write not aligned %d %x", idx, dst);
    }
    if ((u32)len & 1) {
        error("bad write len %d", len);
    }

    dma = &DMAqueue[idx];
    dma->_03C = 1;
    SysLib::WritebackDCache(src, len);
    osPiStartDma(&dma->mesg, 0, OS_WRITE, (u32) dst, src, len, &dma->mq);
    dma->_040 = 0;
}

void WaitDMA(s32 idx) {
    DMAThing *dma;
    OSMesg msg;

    dma = &DMAqueue[idx];
    if (dma->_03C != 0) {
        osRecvMesg(&dma->mq, &msg, 1);
        if (dma->_040 != 0) {
            SysLib::InvalCache(dma->_034, dma->_038);
        }
        dma->_03C = 0;
    }
}

// TODO: DMAqueue[0] should be something like DMAqueue[SYNCIDX]
extern "C" void SyncReadDMA(void *dst, void *src, u32 len) {
    while (DMAqueue[0]._03C != 0) {
        osYieldThread();
    }
    DoReadDMA(0, dst, src, len);
    WaitDMA(0);
}

extern "C" void SyncWriteDMA(void *dst, void *src, u32 len) {
    while (DMAqueue[0]._03C != 0) {
        osYieldThread();
    }
    DoWriteDMA(0, dst, src, len);
    WaitDMA(0);
}


s32 AllocDMA() {
    DMAThing *dma = &DMAqueue[0];
    int i = 1; // 0 is reserved for sync DMA

    while (1) {
        if (dma->_03C == 0) {
            return i;
        }
        i++;
        dma++;
        if (i == 10) {
            error("Out of DMA slots");
            return 0;
        }
    }
}

extern "C" s32 AsyncReadDMA(void *dst, void *src, u32 len) {
    int idx = AllocDMA();
    DoReadDMA(idx, dst, src, len);
    return idx;
}

extern "C" s32 AsyncWriteDMA(void *dst, void *src, u32 len) {
    int idx = AllocDMA();
    DoWriteDMA(idx, dst, src, len);
    return idx;
}

extern "C" void InitDMAQueue(void) {
    for (int i = 0; i < 10; i++) {
        DMAqueue[i]._030 = 0;
        osCreateMesgQueue(&DMAqueue[i].mq, &DMAqueue[i]._030, 1);
    }
}

void isWriteHost(void *a0, u32 a1) {
    // decomp
}

void isReadHost(void *a0, u32 a1) {
    // decomp
}

// figure out the structure of gfx
void SysConDisplay() {
    // decomp
}

// decompile control.cpp and gfxlib.cpp and app.cpp
void SysConsolePrint() {
    // decomp
}

extern u8 *threadNames[];

u8 *ThreadName(int idx) {
    return threadNames[idx];
}

u8 *ThreadState(int idx) {
    switch (idx) {
        case OS_STATE_STOPPED:
            return (u8*) "Stopped";
        case OS_STATE_RUNNABLE:
            return (u8*) "Runnable";
        case OS_STATE_RUNNING:
            return (u8*) "Running";
        case OS_STATE_WAITING:
            return (u8*) "Waiting";
        default:
            return (u8*) "Unknown";
    }
}

extern OSThread *__osActiveQueue;

void PrintThreadPCs() {
    u32 usoNum;
    u8 *usoName;

    OSThread *currThread = __osActiveQueue;
    printf("Threads:");
    while (currThread->priority != -1) {
        if (usodata != NULL) {
            usodata->getName((u32)currThread->context.pc, &usoName, &usoNum);
        } else {
            usoName = (u8*)"";
        }
        // example output:
        // main (3): Running : (, 0x0) PC=0x80000400
        printf("%s (%d): %s : (%s,0x%x) PC=0x%x",
            ThreadName(currThread->id),
            currThread->id,
            ThreadState(currThread->state),
            usoName,
            usoNum,
            currThread->context.pc
        );
        currThread = currThread->tlnext;
    }
}

static OSThread Fault_Thread;
static OSMesgQueue FaultMsgQ;
static OSMesg FaultMsgBuf[1];

void printFaultData(OSThread *);

void FaultThreadRoutine(void *arg) {
    OSMesg msg;
    static OSThread *curr; // _1964
    static OSThread *last; // _1968
    u32 usoNum;
    u8 *usoName;

    osSetEventMesg(OS_EVENT_FAULT, &FaultMsgQ, (OSMesg) 0x10);
    last = 0;
    while (1) {
        osRecvMesg(&FaultMsgQ, &msg, 1);
        curr = __osGetCurrFaultedThread();
        if (curr == NULL) {
            continue;
        }

        if (usodata != NULL) {
            usodata->getName((u32)curr->context.pc, &usoName, &usoNum);
        } else {
            usoName = (u8*)"";
        }
        printf("****************");
        printFaultData(curr);
        error("Fault (%s,0x%x) 0x%x in Thread %s (%d)",
            usoName,
            usoNum,
            (u32)curr->context.pc,
            ThreadName(curr->id),
            curr->id
        );
    }
}

void Start_FaultThread(void) {
    static u64 Stack[0x2000 / sizeof(u64)];

    osCreateMesgQueue(&FaultMsgQ, FaultMsgBuf, 1);
    osCreateThread(&Fault_Thread, 5, FaultThreadRoutine, 0, Stack + (0x2000 / sizeof(u64)), 12);
    osStartThread(&Fault_Thread);
}

void *_printf(void *, const char *, int) {
    return 0;
}

extern "C" void printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    _Printf(_printf, 0, fmt, (va_list)ALIGN4(args));

    va_end(args);
}

extern "C" void exit(int res) {
    while (1);
}

extern u32 memSize;
extern void *memBase;

extern "C" void InitMem(void *base, u32 size) {
    memBase = base;
    memSize = size;
}

typedef u32 Node;
void GenHostButtons(Node *) {

}

void ResetHostIO() {
    // extern HostIO hio;
}

extern "C" void __pure_virtual_called() {
    error("pure_virtual_called");
}

static OSPiHandle sramMgr;
extern OSPiHandle *B_171C;

class StdSysLib {
    public:
        static void DebugPrint(char* ...);
        static void *_DebugPrintPos(void*,const char*,int);
};

void SysLib::Init() {
    // StdSysLib::Init();
    Start_FaultThread();
    this->InitControllers();
    this->Reset();

    if (usodata != NULL) {
        usodata->_08C = (u32) StdSysLib::DebugPrint;
        usodata->_090 = (u32) StdSysLib::_DebugPrintPos;
    }
    if (sramMgr.baseAddress != 0xA8000000) {
        sramMgr.type = 3;
        sramMgr.baseAddress = 0xA8000000;
        sramMgr.latency = 5;
        sramMgr.pulse = 0xC;
        sramMgr.relDuration = 2;
        sramMgr.pageSize = 0xD;
        sramMgr.domain = 1;
        sramMgr.speed = 0;
        bzero(&sramMgr.transferInfo, sizeof(__OSTranxInfo));
        osEPiLinkHandle(&sramMgr);
    }
    B_171C = &sramMgr;
}

void SysLib::Reset() {
    CheckStacks();
    // SydSyslib::Reset();
    contMgr.Reset();
}

void SysLib::FlushIO() {
    for (int i = 0; i < 10; i++) {
        WaitDMA(i);
    }
}

void SysLib::GetMemory(void **base, u32 *siz) {
    *base = memBase;
    *siz = memSize;
}

u32 SysLib::GetBootUpSize() {
    return 0x80000000 + (u32)memBase;
}

void SysLib::WritebackDCacheAll() {
    u32 saveMask = osSetIntMask(1);

    osWritebackDCacheAll();

    osSetIntMask(saveMask);
}

void SysLib::WritebackDCache(void *base, u32 len) {
    u32 saveMask = osSetIntMask(1);

    osWritebackDCacheAll();

    osSetIntMask(saveMask);
}

void SysLib::InvalCache(void *base, u32 len) {
    u32 saveMask = osSetIntMask(1);

    osInvalDCache(base, len);
    osInvalICache(base, len);

    osSetIntMask(saveMask);
}

int SysLib::ReadController(Controller *c) {
    return 0;
}

int SysLib::InitControllers() {
    contMgr.Init();
    return 1;
}

void SysLib::ControllerShake(int a, int b) {
    contMgr.ShakeController((u32) a, b);
}

void SysLib::ControllerVibration(int a, int b, int c) {
    contMgr.JoltController((u32) a, b, c);
}
void SysLib::ControllerJolt(int, int, int, int, int) {
    
}

void SysLib::ControllerFriction(int a, float b) {

}

u8 SysLib::CanShakeController(int) {
    return 1;
}

void SysLib::ReadControllers() {

}

void SysLib::WaitControllers() {

}

u32 SysLib::ConnectedControllers() {
    return 1;
}

void SysLib::RunApp(App *) {

}

u32 SysLib::GetTime() {
    return 1;
}

void SysLib::LoadUSO(char *) {

}

void SysLib::UnLoadUSO(char *) {

}

void SysLib::TempBuffer(void *, u32) {

}

void *SysLib::AllocTempBuffer(u32) {
    return 0;
}

void SysLib::FreeTempBuffer(void *) {

}

u8 SysLib::ResetType() {
    return 1;
}

void *SysLib::OpenFile(char *, char *) {
    return 0;
}

int SysLib::ReadFile(void *, u32) {
    return 0;
}

int SysLib::AsyncReadFile(void *, u32) {
    return 0;
}

void SysLib::WaitAsyncFile(int) {

}

int SysLib::SeekFile(GDL_FSEEK, u32) {
    return 0;
}

int SysLib::WriteFile(void *, u32) {
    return 0;
}

void SysLib::UseFile(void *) {

}

int SysLib::FileInfo(char *, void **) {
    return 0;
}

u32 SysLib::FileSize() {
    return 0;
}

void SysLib::CloseFile() {

}

int SysLib::FileError() {
    return 0;
}

void *SysLib::CurrFile() {
    return 0;
}

int SysLib::WriteHost(void *, u32) {
    return 0;
}

int SysLib::ReadHost(void *, u32) {
    return 0;
}

int SysLib::TestHost() {
    return 0;
}

void SysLib::RawReadDMA(void *, void *, u32) {

}

