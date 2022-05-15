
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

class Hair {
    public:
        Hair();
        Hair(BasePolyShape *, int);
        void Init();
        void Update();
            //static wank; // no type symbol
        void ProcStrands();
        void GenShape();
};

