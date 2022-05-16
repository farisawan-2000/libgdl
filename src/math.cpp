#define volatile

#include <ultra64.h>

#include "math.hpp"

void conv_matrix(matrix4 *);

float mysqrtf(float);

float limitf(float, float);

void limitvec(Vector3<float> *,float);

extern "C" void rotate2d();

float CalcLength(Vector3<float>*);

void InvertMatrix3d(float [4][4], float [4][4]);

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

int LongBox::InBox(LongBox *) {
    return 0;
}

void Plane::Init(Vector3<float>*,Vector3<float>*,Vector3<float>*) {

}

void Quat::Conjugate(Quat &) {

}

void Quat::MulVector(Vector3<float> &, Vector3<float> &) {

}

void Quat::SLERP(Quat &, float, int) {

}

void Quat::MulTo(Quat &, Quat &) {

}

void Quat::Rotate(float, float, int) {

}

void Quat::GenMtx3(matrix4 *) {

}

void Quat::Init(float, float, float) {

}

void Quat::Rotate(float, float, float) {

}

void Quat::Rotate(const Vector3<float> &, f32) {

}

void Quat::Normalise() {

}

void Quat::FromBallPoints(Vector3<float> &, Vector3<float> &) {

}

void Quat::ToBallPoints(Vector3<float> &, Vector3<float> &) {

}

void VQS::GenMtx(matrix4 &) {

}

void VQS::MulTo(VQS &, VQS &) {

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

}

void matrix4::Ident3x3(void) {

}

void matrix4::Trans(Vector3<float>*) {

}

void matrix4::Scale(Vector3<float>*) {

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

void matrix4::GenOrtho(float,float,float,float,float,float,float) {

}

void matrix4::GenPerspective(float,float,float,float) {

}

void matrix4::GenLookAt(float,float,float,float,float,float,float,float,float) {

}

void matrix4::GenBallRotate(matrix4*,float,float,float,int) {

}

matrix4 *matrix4::operator = (float) {
    return this;
}

MtxStack::MtxStack() {

}

void Box::Print() {

}


