
// rgba_t
#include "gfxlib.hpp"

// static __vtbl__20FuncPtrBase__pt__2_v;
struct DrawMode {
    u32 _000;
    u32 mode; // _004
};

class BaseMaterial;
class Window;

u8* GenChildName(char *, char *);

int BitNum(int);

u32 RenderMode(DrawMode *);

u32 RenderMode2(DrawMode *);


class DisplayList {
    public:
        DisplayList(char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
        void Reset(void);
        void Overflow(void);
        void PrintUsage(void);
        void GenSetCombineMode1(DrawMode*);
        void GenSetCombineMode2(DrawMode*);
        void GenSetCombineMode(DrawMode*);
        void GenSetGeometryMode(DrawMode*);
        void GenSetRenderMode(DrawMode*);
        void GenSetCycleMode(DrawMode*);
        void GenSetFogParms(short,short,rgba_t<float>&);
        void GenStartShape(void);
        void GenEndDraw(void);
        void GenSetColourBuffer(unsigned short*,int);
        void GenSetZBuffer(unsigned short*);
        void GenEnd(void);
        void GenLoadTexBlock(BaseMaterial*,int);
        void GenStartDraw(Window*);
        void GenFrameBufferSetup(unsigned short*,unsigned short*,int,int,rgba_t<float>&,int,int,int,int,int,int);        
};


class SubDisplayList {
    public:
        SubDisplayList(char *);
        SubDisplayList(char *, DisplayList *);
        SubDisplayList(char *, int, DisplayList *);
        void SetParent(DisplayList*);
};
