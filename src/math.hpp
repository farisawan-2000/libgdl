
template <class T> class Vector3 {
    public:
        T x;
        T y;
        T z;
};

typedef float quat[4];
class matrix4;

void conv_matrix__FP7matrix4();

float mysqrtf(float);

float limitf(float, float);

void limitvec(Vector3<float> *,float);

extern "C" void rotate2d();

float CalcLength(Vector3<float>*);

void InvertMatrix3d(float [4][4], float [4][4]);

void adjoint__FP7matrix4T1();

float det4x4__FP7matrix4();

float det3x3(float, float, float,
             float, float, float,
             float, float, float
);

float det2x2__FfN31();

void set_obs_position__FP4quatP16Vector3__pt__2_ffN23();

void translate_quaternion__FP4quatP16Vector3__pt__2_ffiT4();

void print_vector3__FPcP16Vector3__pt__2_f();

void print_matrix4__FPcP7matrix4();

void print_quat__FPcP4quat();

template class Vector3<float> {

};
void GenHostIO__16Vector3__pt__2_fFfN51();
void MulByRotMtxT(matrix4 *);
void CrossProd(const Vector3<float> *,Vector3<float> *);
int Normalise();

int InBox__7LongBoxFP7LongBox();

void Init__5PlaneFP16Vector3__pt__2_fN21();

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
}

class VQS {
    public:
        void GenMtx(matrix4 &);
        void MulTo(VQS &, VQS &);
};

void _InitSCRot__7matrix4FP16Vector3__pt__2_ffT2();
void _Align__7matrix4FP16Vector3__pt__2_ff();
void _Align__7matrix4FP16Vector3__pt__2_fT1();
void ConvertTo__7matrix4FR4Quat();
void ConvertFrom__7matrix4FR4Quat();
void CopyTo__7matrix4FP7matrix4();
void Copy3x3To__7matrix4FP7matrix4();
void AddTo__7matrix4FP7matrix4T1();
void SubTo__7matrix4FP7matrix4T1();
void TransposeTo__7matrix4FP7matrix4();
void Inverse__7matrix4FP7matrix4();
void ReOrthogonalize__7matrix4Fi();
void ConstMulTo__7matrix4FfP7matrix4();
void Mul3x3To__7matrix4FP7matrix4T1();
void Ident__7matrix4Fv();
void Ident3x3__7matrix4Fv();
void Trans__7matrix4FP16Vector3__pt__2_f();
void Scale__7matrix4FP16Vector3__pt__2_f();
void Rotate__7matrix4FP16Vector3__pt__2_ff();
void Rotate__7matrix4FP16Vector3__pt__2_f();
void AbsRot__7matrix4FifT1();
void RelRot__7matrix4FifT1();
void Align__7matrix4FRC16Vector3__pt__2_ff();
void GenRotate__7matrix4FR16Vector3__pt__2_ff();
void GenShadow__7matrix4FP16Vector3__pt__2_fP5Plane();
void GenOrtho__7matrix4FfN61();
void GenPerspective__7matrix4FfN31();
void GenLookAt__7matrix4FfN81();
void GenBallRotate__7matrix4FP7matrix4fN22i();
matrix4* __as__7matrix4FPf();


MtxStack* __ct__8MtxStackFv();

void Print__3BoxFv();