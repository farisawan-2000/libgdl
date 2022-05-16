typedef int *DrawMode;
typedef u64 *DisplayList;

class RcpTask {
    public:
        RcpTask();
        // ~RcpTask();
        void Init(DrawMode*, int);
        void UseDL(Gfx *, u32, u64 *);
        void UseLine3D();
        void UseFast3D();
        void UseSuper3D_Fifo(u8 *fifoBuffer, u32 len);
        void UseFast3D_Fifo(u8 *fifoBuffer, u32 len);
        void UseFast3D_Dram(u8 *dramBuffer);
        void UseFast3DQ_Fifo(u8 *fifoBuffer, u32 len);
        void UseF3DEX_Fifo(u8 *fifoBuffer, u32 len);
        void UseF3DEX_NoN_Fifo(u8 *fifoBuffer, u32 len);
        void UseF3DLP_NoC_Fifo(u8 *fifoBuffer, u32 len);
        void UseF3DLP_Rej_Fifo(u8 *fifoBuffer, u32 len);
        void UseF3DLX_Rej_Fifo(u8 *fifoBuffer, u32 len);
        void UseTurbo3D();
        void Start();
        void AddTo(RcpTask &);
        void RemoveFrom(RcpTask &);

        RcpTask *_000;
        u32 _004;
        u32 _008;
        u32 _00C;
        OSTask task; // 0x10
        RcpTask *_050; // linkedlist entries?
        RcpTask *_054;
        u32 _058;
        u32 _05C;
        u32 _060;
        u32 _064;
        u32 _068;
        DrawMode *_06C;
        u32 _070;
        u32 _074;
        u32 _078;
        u32 _07C;
};

static OSThread rcpMgrThread;
static u64 rcpMgrStack[0x2000 / sizeof(u64)];
static u8 rspBootBuf[0x100];

enum GDL_RCPTASK_TYPE {
    GDL_TYPE_0 = 0,
    GDL_TYPE_1,
    GDL_TYPE_2,
};

class RcpMgr {
    public:
        RcpMgr();
        static void CallUpdate(RcpMgr *);
        void Update();
        int CheckPendingTasks();
        int AddLine3DTask(DrawMode *, RcpTask *, DisplayList *);
        void SetupTask(RcpTask*, DrawMode *, Gfx *, u32, enum GDL_RCPTASK_TYPE);
        void AddTask(RcpTask *);
        RcpTask* AllocTask(int);
        void RemoveCurrTask();


        static u64 *yieldBuffer;
        static u64 *FifoBuffer;
        static u32 FifoBufferLen;
};