#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "gfxlib.hpp"

class Console {
    public:
        Console(char *, int, int, int, int, rgba_t<float>);
        void TogglePause();
        void ScrollUp();
        void ScrollDown();
        void ScrollLeft();
        void ScrollRight();
        void Display(int);
        void Print(char *fmt, ...);
        void* _printf(void *, const char *, int);
        void ScrollDataUp();
        void Clear();
        static void* _GLBprintf(void *, const char *, int);

        static Console *currPrint;

        u32 _000;
        u32 _004;
        u32 _008;
        u32 _00C;
        u32 xPos; // _014
        u32 _014;
        u32 yPos; // _018
        u32 _01C;
        u32 _020;
        u32 _024;
        u32 _028;
        u32 _02C;
        u32 _030;
        u32 paused; // _034
        u32 _038;
        u32 _03C;
        u32 _040;
        u32 _044;
        u32 _048;
        u32 _04C;
        u32 _050;
        u32 _054;
}; // size 0x58

class ConsoleMgr {
    public:
        ConsoleMgr();
        void Update();
        void Display();
        void Reset(int);
        void Register(Console *);
        void UnRegister(Console *);
        void DisplayNext();
        void DisplayPrev();
        void Show(int);
        void ToggleDisplay();

};

#endif
