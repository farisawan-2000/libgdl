#define volatile
#include <ultra64.h>

// begin file ..//include/hostio.hpp
// begin file ..//include/parameter.hpp
// begin file ..//include/app.hpp
// begin file ..//include/math.hpp
#include "math.hpp"
// begin file ..//include/shapefmt.hpp
// begin file ..//include/stdsys.hpp
// begin file ..//u64/include/syslib.hpp
// begin file ..//include/hair.hpp
#include "hair.hpp"
// begin file ..//include/node.hpp
// begin file ..//include/shape.hpp
// begin file ..//include/stdgfx.hpp
// begin file ..//u64/include/gfxlib.hpp
// begin file /home2/giles/src/gdl/lib/system/hair.cpp


void Wind::Init() {

}

void Wind::Change() {

}

void Wind::Update() {

}

void HairStrand::Init(Vector3<float> &, Vector3<float> &, int) {

}

void HairStrand::Update(void *, Wind &) {

}

Hair::Hair() {

}

Hair::Hair(BasePolyShape *, int) {
}


void Hair::Init() {

}

void Hair::Update() {
    static u32 wank;
    s32 i;

    // this->_0BC->Update();

    // for (i = 0; i < this->unkE4; i++) {
    //     this->_0B8[i].Update(this->unk14, temp_s3);
    // }

    // if (wank == 100) {
    //     this->_0BC->Change();
    //     wank = 0;
    // }
    // wank++;
    
    // this->ProcStrands();

    // MorphPolyShape *a0 = this->_0B4;

    // a0->UpdatePnts(a0->unk60);
}

void Hair::ProcStrands() {

}

void Hair::GenShape() {

}

void Hair::Display() {

}
