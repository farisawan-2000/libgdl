// lib/system/funcptr.cpp

template <class T> class FuncPtrBase {
    public:
        virtual T something();
};

class voidFuncPtr : public FuncPtrBase<void> {
    public:
        virtual void something () = 0;
        void operator () ();
        void (*_000)();
};

void voidFuncPtr::operator ()() {
    this->_000();
}

