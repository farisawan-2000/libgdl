#ifndef APP_HPP
#define APP_HPP

#include "console.hpp"

class App {
    public:
        App();
        void Init();
        void Reset();
        void HardReset();
        void SoftReset();
        void PreNMI();
        void InitInstance();
        void GenHostIO();
        void Update();
        void Display();
        void LoadVersion(char *);
        void MemDebug(int);
        static int MemoryLevel(int);
        static int MemoryLevel();
        static void FreeMemoryLevel(int);
        static int PrintFreeMem(Console *);
        static void PrintMemUsage();
        static void DumpMemory();
        static u32 GetMemUsed();
};

#endif
