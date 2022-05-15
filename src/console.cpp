
#define volatile
#include <ultra64.h>
#include <stdarg.h>
#include "console.hpp"
#include "align.h"

#define NONMATCH

Console::Console(char *, int, int, int, int, rgba_t<float>) {
    //decomp
}

void Console::TogglePause() {
    this->paused ^= 1;
}

void Console::ScrollUp() {
    if (this->yPos >= 0) {
        this->yPos ^= 1;
    }
}

void Console::ScrollDown() {
    if ((this->yPos <  (this->_00C - this->_014))
     && (this->_020 >= (this->yPos + this->_014))
    ) {
        this->yPos++;
    }
}

void Console::ScrollLeft() {
    if (this->xPos > 0) {
        this->xPos--;
    }
}

void Console::ScrollRight() {
    if (this->xPos < (this->_008 - this->_01C)) {
        this->xPos++;
    }
}

void Console::Display(int d) {

}

NONMATCH void Console::Print(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    if (this->paused == 0) {
        Console::currPrint = this;
        _Printf(Console::_GLBprintf, 0, fmt, (va_list)(ALIGN4(args)));
    }

    va_end(args);
}

void *Console::_printf(void *vp, const char *fmt, int a) {
    return 0;
}

void Console::ScrollDataUp() {
    
}

void Console::Clear() {

}

// weird function pls look at it
void* Console::_GLBprintf(void *vp, const char *fmt, int a) {
    Console *con = Console::currPrint;

    return con->_printf(0, (const char *)vp, (int)fmt);
}

ConsoleMgr::ConsoleMgr() {

}

void ConsoleMgr::Update() {

}

void ConsoleMgr::Display() {

}

void ConsoleMgr::Reset(int x) {

}

void ConsoleMgr::Register(Console *con) {

}

void ConsoleMgr::UnRegister(Console *con) {

}

void ConsoleMgr::DisplayNext() {

}

void ConsoleMgr::DisplayPrev() {

}

void ConsoleMgr::Show(int x) {

}

void ConsoleMgr::ToggleDisplay() {

}
