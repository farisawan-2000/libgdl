#ifndef ISSTREAM_HPP
#define ISSTREAM_HPP

typedef u32 ISLONG;

extern "C" void isInit;

class isStream {
    public:
        void StartLink();
        void Error(char *);
        void GetAccess();
        void RelAccess();
        ISLONG RawRead(u32);
        void RawRead(u32, void *, u32);
        void RawWrite(u32, u32);
        void RawWrite(u32, void *, u32);
        void Yield();
};

extern isStream printStream;
extern isStream gameStream;
extern isStream hostStream;

#endif
