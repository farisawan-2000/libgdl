#ifndef SYSLIB_HPP
#define SYSLIB_HPP

#include "control.hpp"
#include "app.hpp"

typedef u32 GDL_FSEEK;

class SysLib {
    public:
        void Init();
        void Reset();
        void FlushIO();
        void GetMemory(void **, u32 *);
        u32 GetBootUpSize();
        static void WritebackDCacheAll();
        static void WritebackDCache(void *, u32);
        static void InvalCache(void *, u32);
        int ReadController(Controller *);
        int InitControllers();
        void ControllerShake(int, int);
        void ControllerVibration(int, int, int);
        void ControllerJolt(int, int, int, int, int);
        void ControllerFriction(int, float);
        u8 CanShakeController(int);
        void ReadControllers();
        void WaitControllers();
        u32 ConnectedControllers();
        void RunApp(App *);
        u32 GetTime();
        void LoadUSO(char *);
        void UnLoadUSO(char *);
        void TempBuffer(void *, u32);
        void* AllocTempBuffer(u32);
        void FreeTempBuffer(void *);
        u8 ResetType();
        void* OpenFile(char *, char *);
        int ReadFile(void *, u32);
        int AsyncReadFile(void *, u32);
        void WaitAsyncFile(int);
        int SeekFile(GDL_FSEEK, u32);
        int WriteFile(void *, u32);
        void UseFile(void *);
        int FileInfo(char *, void **);
        u32 FileSize();
        void CloseFile();
        int FileError();
        void* CurrFile();
        int WriteHost(void *, u32);
        int ReadHost(void *, u32);
        int TestHost();
        void RawReadDMA(void *, void *, u32);
};

extern SysLib sys;

#endif
