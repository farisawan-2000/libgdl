#ifndef MATH_HPP
#define MATH_HPP

class Quat;
template <class T> class Vector3;
class Plane;

class matrix4 {
    public:
        void ConvertFrom(Quat&);
        void CopyTo(matrix4*);
        void Copy3x3To(matrix4*);
        void AddTo(matrix4*,matrix4*);
        void SubTo(matrix4*,matrix4*);
        void TransposeTo(matrix4*);
        void Inverse(matrix4*);
        void ReOrthogonalize(int);
        void ConstMulTo(float,matrix4*);
        void Mul3x3To(matrix4*,matrix4*);
        void Ident(void);
        void Ident3x3(void);
        void Trans(Vector3<float>*);
        void Scale(Vector3<float>*);
        void Rotate(Vector3<float>*,float);
        void Rotate(Vector3<float>*);
        void AbsRot(int,float,int);
        void RelRot(int,float,int);
        void Align(const Vector3<float>&,float);
        void GenRotate(Vector3<float>&,float);
        void GenShadow(Vector3<float>*,Plane*);
        void GenOrtho(float,float,float,float,float,float,float);
        void GenPerspective(float,float,float,float);
        void GenLookAt(float,float,float,float,float,float,float,float,float);
        void GenBallRotate(matrix4*,float,float,float,int);
        matrix4 *operator = (float);

        float m[4][4];
};

template <class T> class Vector3 {
    public:
        void GenHostIO(T t1,T t2,T t3,T t4,T t5,T t6);
        void MulByRotMtxT(matrix4 *m);
        void CrossProd(const Vector3<T> *v1, Vector3<T> *v2);
        int Normalise();

        T x;
        T y;
        T z;
};

typedef float quat[4];

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

class LongBox {
    public:
        int InBox(LongBox *);
};

class Plane {
    public:
        void Init(Vector3<float>*,Vector3<float>*,Vector3<float>*);
};

class Quat {
    public:
        void Conjugate(Quat &);
        void MulVector(Vector3<float> &, Vector3<float> &);
        void SLERP(Quat &, float, int);
        void MulTo(Quat &, Quat &);
        void Rotate(float, float, int);
        void GenMtx3(matrix4 *);
        void Init(float, float, float);
        void Rotate(float, float, float);
        void Rotate(const Vector3<float> &, f32);
        void Normalise();
        void FromBallPoints(Vector3<float> &, Vector3<float> &);
        void ToBallPoints(Vector3<float> &, Vector3<float> &);
};

class VQS {
    public:
        void GenMtx(matrix4 &);
        void MulTo(VQS &, VQS &);
};

class MtxStack {
    public:
        MtxStack();
};

class Box {
    public:
        void Print();
};

#endif
