
class Wind {
    public:
        void Init();
        void Change();
        void Update();
};

class HairStrand {
    public:
        void Init(Vector3<float> &, Vector3<float> &, int);
        void Update(void *, Wind &);
};

typedef int BasePolyShape;
typedef int MorphPolyShape;

class Hair {
    public:
        Hair();
        Hair(BasePolyShape *, int);
        void Init();
        void Update();
            //static wank; // no type symbol
        void ProcStrands();
        void GenShape();

        // inherited from MNode?
        void Display();

        // _060 is a short_vector3*
        u32 pad[0xB0 / 4];
        u32 _0B0;
        MorphPolyShape *_0B4;
        HairStrand *_0B8;
        Wind *_0BC;
};

