#define volatile

#include <ultra64.h>


// begin file ..//include/stdsys.hpp
// begin file ..//include/stdio.h
#include "stdlib.hpp"
// begin file ..//u64/include/syslib.hpp
#include "syslib.hpp"
// begin file ..//include/node.hpp
// begin file ..//include/app.hpp
#include "math.hpp"
// begin file /home2/giles/src/gdl/lib/system/math.cpp


void conv_matrix(matrix4 *);

float mysqrtf(float f) {
    return sqrtf(f);
}

float limitf(float a, float b) {
    if (b < a) {
        a = b;
    } else if (a < -b) {
        a = -b;
    }

    return a;
}

void limitvec(Vector3<float> *vec, float limit) {
    if (vec->x > limit) {
        vec->x = limit;
    } else if (vec->x < -limit) {
        vec->x = -limit;
    }

    if (vec->y > limit) {
        vec->y = limit;
    } else if (vec->y < -limit) {
        vec->y = -limit;
    }

    if (vec->z > limit) {
        vec->z = limit;
    } else if (vec->z < -limit) {
        vec->z = -limit;
    }
}

extern "C" void rotate2d(f32 deg, f32 *x, f32 *y) {
    f32 xP;
    f32 yP;
    f32 rad;

    rad = deg / 57.295776f; // DEG_PER_RAD
    xP = (*x * cosf(rad)) - (*y * sinf(rad));
    yP = (*x * sinf(rad)) + (*y * cosf(rad));
    *x = xP;
    *y = yP;
}

float CalcLength(Vector3<float>*);

void InvertMatrix3d(float src[4][4], float dst[4][4]) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            dst[i][j] = 1.0f / src[i][j];
        }
    }
}

void adjoint(matrix4 *, matrix4 *);

float det4x4(matrix4 *);

float det3x3(float, float, float,
             float, float, float,
             float, float, float
);

float det2x2(float, float, float, float);

void set_obs_position(quat*,Vector3<float>*,float,float,float);

void translate_quaternion(quat*,Vector3<float>*,float,int,int);

void print_vector3(char*,Vector3<float>*);

void print_matrix4(char*,matrix4*);

void print_quat(char*,quat*);

template <class T> void Vector3<T>::GenHostIO(T t1,T t2,T t3,T t4,T t5,T t6) {

}

template <class T> void Vector3<T>::MulByRotMtxT(matrix4 *m) {
    this->x = (m->m[0][0] * this->x) + (m->m[0][1] * this->y) + (m->m[0][2] * this->z);
    this->y = (m->m[1][0] * this->x) + (m->m[1][1] * this->y) + (m->m[1][2] * this->z);
    this->z = (m->m[2][0] * this->x) + (m->m[2][1] * this->y) + (m->m[2][2] * this->z);
}

template <class T> void Vector3<T>::CrossProd(const Vector3<T> *v1, Vector3<T> *v2) {
    v2->x = (this->y * v1->z) - (this->z * v1->y);
    v2->y = (this->z * v1->x) - (this->x * v1->z);
    v2->z = (this->x * v1->y) - (this->y * v1->x);
}

template <class T> int Vector3<T>::Normalise() {
    f32 mag = (this->x * this->x) + (this->y * this->y) + (this->z * this->z);

    if (mag < 1e-6f) {
        this->y = 0.0f;
        this->x = 0.0f;
        this->z = 1.0f;
        return 0;
    } else {
        f32 mag_inv = 1.0f / sqrtf(mag);

        this->x = this->x * mag_inv;
        this->y = (this->y * mag_inv);
        this->z = (this->z * mag_inv);
        return 1;
    }
}

// TODO: verify
static class Vector3<float> coef;

int LongBox::InBox(LongBox *target) {
    if ((this->minX < target->maxX) && (target->minX < this->minX)) {
        if ((this->minZ < target->maxZ) && (target->minZ < this->minZ)) {
            if ((this->minY < target->maxY) && (target->minY < this->minY)) {
                return 1;
            }
        }
    }
    if ((this->maxX < target->maxX) && (target->minX < this->maxX)) {
        if ((this->maxZ < target->maxZ) && (target->minZ < this->maxZ)) {
            if ((this->maxY < target->maxY) && (target->minY < this->maxY)) {
                return 1;
            }
        }
    }
    return 0;
}

void Plane::Init(Vector3<float>*,Vector3<float>*,Vector3<float>*) {

}

void Quat::Conjugate(Quat &) {

}

void Quat::MulVector(Vector3<float> &, Vector3<float> &) {

}

void Quat::SLERP(Quat &q, float arg2, int arg3) {
    // f32 mag = (this->s.x * q.s.x) + (this->s.y * q.s.y) + (this->s.z * q.s.z) + (this->s.w * q.s.w);

    // phi_f14 = arg2;
    // if (mag < 0.0) {
    //     toInvert = 1;
    //     mag = -mag;
    // } else {
    //     toInvert = 0;
    // }
    // if ((1.0f - mag) < R_00000008) {
    //     phi_f2 = 1.0f - arg2;
    // } else {
    //     acosVal = acosf(mag);
    //     sp34 = acosVal + (arg3 * R_00000010);
    //     _1sinVal = sinf(acosVal);
    //     _2sinVal = sinf(acosVal - (arg2 * sp34)) / _1sinVal;
    //     _3sinVal = sinf(arg2 * sp34);

    //     phi_f2 = _2sinVal;
    //     phi_f14 = _3sinVal / _1sinVal;
    // }
    // if (toInvert) {
    //     phi_f14 = -phi_f14;
    // }
    // this->x = (phi_f2 * this->s.x) + (phi_f14 * q.s.x);
    // this->y = (phi_f2 * this->s.y) + (phi_f14 * q.s.y);
    // this->z = (phi_f2 * this->s.z) + (phi_f14 * q.s.z);
    // this->w = (phi_f2 * this->s.w) + (phi_f14 * q.s.w);
}

void Quat::MulTo(Quat &q1, Quat &q2) {
    q2.s.x = ((this->s.w * q1.s.x) + (this->s.x * q1.s.w) + (this->s.y * q1.s.z)) - (this->s.z * q1.s.y);
    q2.s.y = ((this->s.w * q1.s.y) + (this->s.y * q1.s.w) + (this->s.z * q1.s.x)) - (this->s.x * q1.s.z);
    q2.s.w = ((this->s.w * q1.s.w) - (this->s.x * q1.s.x) - (this->s.y * q1.s.y)) - (this->s.z * q1.s.z);
    q2.s.z = ((this->s.w * q1.s.z) + (this->s.z * q1.s.w) + (this->s.x * q1.s.y)) - (this->s.y * q1.s.x);
}

void Quat::Rotate(float arg1, float arg2, int axis0) {
    s32 axis1;
    s32 axis2;

    axis1 = axis0 + 1;
    if (axis1 >= 4) {
        axis1 = 1;
    }

    axis2 = axis1 + 1;
    if (axis2 >= 4) {
        axis2 = 1;
    }

    this->q[axis0] = (this->q[axis0] * arg1) + ((1.0f * arg2) * this->s.x);
    this->s.x = (this->s.x * arg1) - ((1.0f * arg2) * this->q[axis0]);
    this->q[axis1] = (this->q[axis1] * arg1) + (arg2 * this->q[axis2]);
    this->q[axis2] = (this->q[axis2] * arg1) - (arg2 * this->q[axis1]);
}

void Quat::GenMtx3(matrix4 *) {

}

void Quat::Init(float xarg, float yarg, float zarg) {
    Quat q;

    this->s.x = 0.0f;
    this->s.y = 0.0f;
    this->s.z = 0.0f;
    this->s.w = 1.0f;

    // ?
    xarg /= 114.591552734375f;
    yarg /= 114.591552734375f;
    zarg /= 114.591552734375f;

    q.s.x = sinf(xarg);
    q.s.y = 0.0f;
    q.s.z = 0.0f;
    q.s.w = cosf(xarg);
    q.MulTo(*this, *this);

    q.s.x = 0.0f;
    q.s.y = sinf(yarg);
    q.s.z = 0.0f;
    q.s.w = cosf(yarg);
    q.MulTo(*this, *this);

    q.s.x = 0.0f;
    q.s.y = 0.0f;
    q.s.z = sinf(zarg);
    q.s.w = cosf(zarg);
    q.MulTo(*this, *this);
}

void Quat::Rotate(float arg1, float arg2, float arg3) {
    rotate2d(arg1, &this->s.z, &this->s.y);
    rotate2d(arg2, &this->s.x, &this->s.z);
    rotate2d(arg3, &this->s.x, &this->s.y);
}

void Quat::Rotate(const Vector3<float> &vec, f32 arg2) {
    f32 sinVal;
    Quat sp3C;

    sinVal = sinf(arg2 * 0.5f);
    sp3C.s.w = cosf(arg2 * 0.5f);
    sp3C.s.x = vec.x * sinVal;
    sp3C.s.y = vec.y * sinVal;
    sp3C.s.z = vec.z * sinVal;
    sp3C.MulTo(*this, *this);
}

void Quat::Normalise() {
    f32 normVal;

    normVal = 1.0f / sqrtf(
                        (this->s.x * this->s.x)
                      + (this->s.y * this->s.y)
                      + (this->s.z * this->s.z)
                      + (this->s.w * this->s.w)
    );

    this->s.x *= normVal;
    this->s.y *= normVal;
    this->s.z *= normVal;
    this->s.w *= normVal;
}


void Quat::FromBallPoints(Vector3<float> &v1, Vector3<float> &v2) {
    this->s.x = (v1.y * v2.z) - (v1.z * v2.y);
    this->s.y = (v1.z * v2.x) - (v1.x * v2.z);
    this->s.z = (v1.x * v2.y) - (v1.y * v2.x);
    this->s.w = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

void Quat::ToBallPoints(Vector3<float> &v1, Vector3<float> &v2) {
    f32 xyMag = sqrtf((this->s.x * this->s.x) + (this->s.y * this->s.y));

    if (xyMag == 0.0f) {
        v1.x = 0.0f;
        v1.z = 0.0f;
        v1.y = 1.0f;
    } else {
        v1.z = 0.0f;
        v1.y = this->s.x / xyMag;
        v1.x = -this->s.y / xyMag;
    }

    v2.x = (this->s.w * v1.x) - (this->s.z * v1.y);
    v2.y = (this->s.w * v1.y) + (this->s.z * v1.x);
    v2.z = (this->s.x * v1.y) - (this->s.y * v1.x);

    if (this->s.w < 0.0f) {
        v1.z = 0.0f;
        v1.x = -v1.x;
        v1.y = -v1.y;
    }
}

void VQS::GenMtx(matrix4 &) {

}

void VQS::MulTo(VQS &, VQS &) {

}

void matrix4::_InitSCRot(Vector3<float>*,float,float) {

}

void matrix4::_Align(Vector3<float>*,float) {

}

void matrix4::_Align(Vector3<float>*,Vector3<float>*) {

}

void matrix4::ConvertTo(Quat&) {

}


void matrix4::ConvertFrom(Quat&) {

}

void matrix4::CopyTo(matrix4*) {

}

void matrix4::Copy3x3To(matrix4*) {

}

void matrix4::AddTo(matrix4*,matrix4*) {

}

void matrix4::SubTo(matrix4*,matrix4*) {

}

void matrix4::TransposeTo(matrix4*) {

}

void matrix4::Inverse(matrix4*) {

}

void matrix4::ReOrthogonalize(int) {

}

void matrix4::ConstMulTo(float,matrix4*) {

}

void matrix4::Mul3x3To(matrix4*,matrix4*) {

}

void matrix4::Ident(void) {
    this->m[0][0] = 1.0f;
    this->m[0][1] = 0.0f;
    this->m[0][2] = 0.0f;
    this->m[0][3] = 0.0f;
    this->m[1][0] = 0.0f;
    this->m[1][1] = 1.0f;
    this->m[1][2] = 0.0f;
    this->m[1][3] = 0.0f;
    this->m[2][0] = 0.0f;
    this->m[2][1] = 0.0f;
    this->m[2][2] = 1.0f;
    this->m[2][3] = 0.0f;
    this->m[3][0] = 0.0f;
    this->m[3][1] = 0.0f;
    this->m[3][2] = 0.0f;
    this->m[3][3] = 1.0f;
}

void matrix4::Ident3x3(void) {
    this->m[0][1] = 0.0f;
    this->m[0][2] = 0.0f;
    this->m[0][3] = 0.0f;
    this->m[1][0] = 0.0f;
    this->m[1][2] = 0.0f;
    this->m[1][3] = 0.0f;
    this->m[2][0] = 0.0f;
    this->m[2][1] = 0.0f;
    this->m[2][3] = 0.0f;
    this->m[0][0] = 1.0f;
    this->m[1][1] = 1.0f;
    this->m[2][2] = 1.0f;
}

void matrix4::Trans(Vector3<float> *tv) {
    this->m[3][0] += tv->x;
    this->m[3][1] += tv->y;
    this->m[3][2] += tv->z;
}

void matrix4::Scale(Vector3<float> *sv) {
    this->m[0][0] *= sv->x;
    this->m[0][1] *= sv->x;
    this->m[0][2] *= sv->x;
    this->m[1][0] *= sv->y;
    this->m[1][1] *= sv->y;
    this->m[1][2] *= sv->y;
    this->m[2][0] *= sv->z;
    this->m[2][1] *= sv->z;
    this->m[2][2] *= sv->z;
}

void matrix4::Rotate(Vector3<float>*,float) {

}

void matrix4::Rotate(Vector3<float>*) {

}

void matrix4::AbsRot(int,float,int) {

}

void matrix4::RelRot(int,float,int) {

}

void matrix4::Align(const Vector3<float>&,float) {

}

void matrix4::GenRotate(Vector3<float>&,float) {

}

void matrix4::GenShadow(Vector3<float>*,Plane*) {

}

void matrix4::GenOrtho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far, f32 scale) {
    int row;
    int col;
    this->Ident();
    this->m[0][0] = 2 / (right - left);
    this->m[1][1] = 2 / (top - bottom);
    this->m[2][2] = -2 / (far - near);
    this->m[3][0] = -(right + left) / (right - left);
    this->m[3][1] = -(top + bottom) / (top - bottom);
    this->m[3][2] = -(far + near) / (far - near);
    this->m[3][3] = 1;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            this->m[row][col] *= scale;
        }
    }
}

void matrix4::GenPerspective(float,float,float,float) {

}

void matrix4::GenLookAt(float,float,float,float,float,float,float,float,float) {

}

void matrix4::GenBallRotate(matrix4*,float,float,float,int) {

}

matrix4 *matrix4::operator = (float *eq) {

    float *mt = (float *)this->m;

    for (int i = 0; i < 16; i++) {
        *mt++ = *eq++;
    }

    return this;
}

MtxStack::MtxStack() {
    // void *temp_a0;
    // void *temp_v0;
    // void *temp_v0_2;
    // void *phi_a1;
    // void *phi_a1_2;
    // void *v0;

    // phi_a1 = this;
    // phi_a1_2 = this;
    // if ((this != NULL) || (temp_v0 = __nw__FUi(0xC), phi_a1 = temp_v0, phi_a1_2 = temp_v0, (temp_v0 != NULL))) {
    //     this = phi_a1;
    //     temp_v0_2 = new matrix4[32];
    //     temp_a0 = temp_v0_2;
    //     this->unk0 = temp_v0_2;
    //     this->unk4 = temp_v0_2;
    //     Ident__7matrix4Fv(temp_a0, this);
    //     this->unk8 = 0;
    // }
    // v0 = phi_a1_2;
    // return v0;
}


void Box::Print() {
    printf("Min X = %f, Max X = %f", this->minX, this->maxX);
    printf("Min Y = %f, Max Y = %f", this->minY, this->maxY);
    printf("Min Z = %f, Max Z = %f", this->minZ, this->maxZ);
}


