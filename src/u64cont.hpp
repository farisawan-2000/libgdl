#ifndef U64CONT_HPP
#define U64CONT_HPP

typedef u32 CONT_PAK_TYPE;

class ControllerMgr {
    public:
        void Init();
        void InitMotors();
        void Update();
        void Shake(int, int);
        void Reset();
        void Stop();
        void RawRead();
        void ShakeController(u32, int);
        void VibrateController(u32, int, int);
        void JoltController(u32, int, int, int, int, int);
        void ForceFeedback(u32);
        void ReadControllers();
        void WaitControllers();
        void MotorCheck();
        CONT_PAK_TYPE GetInfo(u32);
        u32 Connected();
        static void CallUpdate(ControllerMgr *);
};

extern ControllerMgr contMgr;

#endif
