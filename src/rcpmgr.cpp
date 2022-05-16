#define volatile
#include <ultra64.h>
#include <PR/gt.h>
#include "stdlib.hpp"
#include "rcpmgr.hpp"

void RcpTask::Init(DrawMode * dm, int ini) {
    this->_058 = ini;
    this->_06C = dm;
    this->_05C = 0;
    this->_070 = 0;
    this->_074 = 0;
    // all values set at func start
    this->task.t.type = M_GFXTASK;
    this->task.t.flags = 0;
    this->task.t.ucode_boot = (u64 *) rspBootBuf;
    this->task.t.ucode_boot_size = 0x100;
    this->task.t.ucode_size = 0x1000;
    this->task.t.ucode_data_size = 0x800;

    this->task.t.output_buff = 0;
    this->task.t.output_buff_size = 0;

    this->task.t.yield_data_ptr = RcpMgr::yieldBuffer;
    this->task.t.yield_data_size = 0xC00;
    this->_064 = 1;
}

void RcpTask::UseDL(Gfx *displaylist, u32 len, u64 *dramStack) {
    this->task.t.data_ptr = (u64 *) displaylist;
    this->task.t.data_size = len * sizeof(Gfx);
    this->task.t.dram_stack = dramStack;
    this->task.t.dram_stack_size = 0x400;
}

void RcpTask::UseLine3D() {
    this->task.t.ucode = (u64 *) gspLine3DTextStart;
    this->task.t.ucode_data = (u64 *) gspLine3DDataStart;
}

void RcpTask::UseFast3D() {
    this->task.t.ucode = (u64 *) gspFast3DTextStart;
    this->task.t.ucode_data = (u64 *) gspFast3DDataStart;
}

void RcpTask::UseSuper3D_Fifo(u8 *fifoBuffer, u32 len) {
    this->task.t.output_buff = (u64 *) fifoBuffer;
    this->task.t.output_buff_size = (u64 *)(fifoBuffer + len);
    this->task.t.data_size = 0;
    this->_068 = 2;
}

void RcpTask::UseFast3D_Fifo(u8 *fifoBuffer, u32 len) {
    this->task.t.ucode = (u64 *) gspFast3D_fifoTextStart;
    this->task.t.ucode_data = (u64 *) gspFast3D_fifoDataStart;
    this->task.t.output_buff = (u64 *) fifoBuffer;
    this->task.t.output_buff_size = (u64 *)(fifoBuffer + len);
    this->task.t.data_size = 0;
    this->_068 = 2;
}

void RcpTask::UseFast3D_Dram(u8 *dramBuffer) {
    this->task.t.ucode = (u64 *) gspFast3D_dramTextStart;
    this->task.t.ucode_data = (u64 *) gspFast3D_dramDataStart;
    this->task.t.output_buff = (u64 *) dramBuffer;
    this->task.t.output_buff_size = (u64 *)(&this->_008);
    this->task.t.data_size = 0;
    this->_068 = 1;
}

void RcpTask::UseFast3DQ_Fifo(u8 *fifoBuffer, u32 len) {
    error("fastQ");
}

void RcpTask::UseF3DEX_Fifo(u8 *fifoBuffer, u32 len) {
    this->task.t.ucode = (u64 *) gspF3DEX_fifoTextStart;
    this->task.t.ucode_data = (u64 *) gspF3DEX_fifoDataStart;
    this->task.t.output_buff = (u64 *) fifoBuffer;
    this->task.t.output_buff_size = (u64 *)(fifoBuffer + len);
    this->task.t.data_size = 0;
    this->_068 = 2;
}

void RcpTask::UseF3DEX_NoN_Fifo(u8 *fifoBuffer, u32 len) {
    this->task.t.output_buff = (u64 *) fifoBuffer;
    this->task.t.output_buff_size = (u64 *)(fifoBuffer + len);
    this->task.t.data_size = 0;
    this->_068 = 2;
}

void RcpTask::UseF3DLP_NoC_Fifo(u8 *fifoBuffer, u32 len) {
    error("NoC");
}

void RcpTask::UseF3DLP_Rej_Fifo(u8 *fifoBuffer, u32 len) {
    this->task.t.ucode = (u64 *) gspF3DLP_Rej_fifoTextStart;
    this->task.t.ucode_data = (u64 *) gspF3DLP_Rej_fifoDataStart;
    this->task.t.output_buff = (u64 *) fifoBuffer;
    this->task.t.output_buff_size = (u64 *)(fifoBuffer + len);
    this->task.t.data_size = 0;
    this->_068 = 2;
}

void RcpTask::UseF3DLX_Rej_Fifo(u8 *fifoBuffer, u32 len) {
    this->task.t.ucode = (u64 *) gspF3DLX_Rej_fifoTextStart;
    this->task.t.ucode_data = (u64 *) gspF3DLX_Rej_fifoDataStart;
    this->task.t.output_buff = (u64 *) fifoBuffer;
    this->task.t.output_buff_size = (u64 *)(fifoBuffer + len);
    this->task.t.data_size = 0;
    this->_068 = 2;
}

void RcpTask::UseTurbo3D() {
    this->task.t.ucode = (u64 *) gspTurbo3DTextStart;
    this->task.t.ucode_data = (u64 *) gspTurbo3DDataStart;
}

class SysLib {
    public:
        static void WritebackDCacheAll();
};


void RcpTask::Start() {
    SysLib::WritebackDCacheAll();
    osSpTaskStart(&this->task);

    this->_060 = 1;
    this->_064 = 0;
}

void RcpTask::AddTo(RcpTask &r) {
    if (r._000 != NULL) {
        this->_050 = r._000;
        this->_054 = r._000->_054;
        r._000->_054->_050 = this;
        r._000->_054 = this;
    } else {
        this->_050 = this;
        this->_054 = this;
        r._000 = this;
    }
}


void RcpTask::RemoveFrom(RcpTask &r) {    
    if (r._000 == NULL) {
        error("RcpTask remove");
    }
    if ((this->_050 == this->_054) && (this == this->_054)) {
        r._000 = NULL;
    } else {
        r._000 = r._000->_050;
        this->_054->_050 = this->_050;
        this->_050->_054 = this->_054;
    }
}

RcpMgr::RcpMgr() {
    // int phi_s0;
    // Start__10MemTrackerSFPci("RcpMgr", 0);
    // SyncReadDMA(&rspBootBuf, 0xB0000B70, 0x100);
    // this->unk4C = 0;
    // this->unk0 = 0;
    // this->unk4 = 0;
    // this->unk8 = 0;
    // this->unkC = 0;
    // for (phi_s0 = 0; phi_s0 < 10; phi_s0++) {
    //     RcpTask task = new(16) RcpTask;

    //     task->AddTo(this);
    // }
    
    // temp_v0_3 = __nw__FUiT1(0x78, 0x10);
    // if (temp_v0_3 != 0) {
    //     phi_a3_2 = temp_v0_3;
    // } else {
    //     phi_a3_2 = 0;
    // }
    // this->unk14 = phi_a3_2;
    // yieldBuffer__6RcpMgr = __nw__FUiT1(0xC00, 0x10);
    // FifoBufferLen__6RcpMgr = 0x19000;
    // temp_v0_4 = __nw__FUiT1(0x19004, 0x40);
    // FifoBuffer__6RcpMgr = temp_v0_4;
    // *(temp_v0_4 + ((FifoBufferLen__6RcpMgr >> 2) * 4)) = 0x12345678;
    // this->unk30 = __nw__FUiT1(0x400, 0x10);
    // osCreateThread(&rcpMgrThread, 4, RcpMgr::CallUpdate, this, rcpMgrStack + (0x2000 / sizeof(u64)), 0xB);
    // rcpMgrStack[0] = 0x1234567812345678; // canary
    // osSetEventMesg(OS_EVENT_DP, sys.unk1C, 0x66);
    // osSetEventMesg(OS_EVENT_SP, sys.unk1C, 0x65);
    // osSetEventMesg(OS_EVENT_PRENMI, sys.unk1C, 0x6C);
    // osStartThread(&rcpMgrThread);
    // this->unk20 = 0;
    // this->unk1C = 0;
    // this->unk24 = 0;
    // this->unk28 = 0;
    // Stop__10MemTrackerSFv();
    // this->unk20 = 0;
    // this->unk1C = 0;
    // return this;
}

