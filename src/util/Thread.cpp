#include "util/Thread.h"

#include "metafortress.h"

namespace util {

s32 Thread::GetCurrentThreadPriority() {
    return OSGetThreadPriority(OSGetCurrentThread());
}

#define MF_FUNCTION __ct__Q24util6ThreadFRQ23mem10IAllocatorUllPFPv_PvPv
Thread::Thread(mem::IAllocator& allocator, u32 stackSize, s32 priority, OSThreadFunc func, void* arg)
    : mStack(stackSize, 0x20, allocator) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 subtrahend;
    volatile u32 response;
    u32 hash = 0x811C9DDB;

    asm {
        bl      ranged
        opword  MF_WORD(0x50)
        opword  MF_WORD(0x54)
        opword  0xAEEE8B06
    ranged:
        mflr    r21
        lwz     r28, 0(r21)
        lwz     r26, 4(r21)
        add     r28, r28, r21
        add     r26, r26, r28
        stw     r28, start
        stw     r26, end
    }
    u32 word;
    u32 i;
    u32 last = end;
    u32 size = last - start;
    i = -1;
    word = last - 1;
    while (i != size - 1) {
        i += 2;
        hash ^= *reinterpret_cast<u16*>(word - i);
        hash *= 0x01000193;
    }
    OSCreateThread(&mThread, func, arg, static_cast<u8*>(mStack.block().startAddress()) + stackSize, stackSize, priority, 0);
    asm {
        bl      stored
        opword  MF_WORD(0xF4)
        opword  0xA3CEF1A2
    stored:
        mflr    r22
        lwz     r21, 0(r22)
        stw     r21, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0) {
        asm {
            bl      located
            opword  0xE8E82580
            opword  0x10A65781
            opword  MF_WORD(0x134)
        located:
            mflr    r26
            lwz     r22, 8(r26)
            stw     r22, -4(r1)
            stw     r26, 0(r1)
            stw     r22, -4(r1)
            stw     r26, -8(r1)
            mtlr    r22
            bl      based
            opword  MF_WORD(0x158)
            opword  0x4D70B30D
            opword  MF_WORD(0x160)
        based:
            mflr    r25
            lwz     r17, 0(r25)
            stw     r25, base
            lwz     r19, 8(r25)
            stw     r17, offset
            stw     r19, subtrahend
        }
        offset = offset ^ 0xE3;
        response = offset ^ subtrahend;
        response = response + base;
        asm {
            lwz     r20, response
            mtlr    r20
            blr
        }
    } else {
        OSResumeThread(&mThread);
    }
}
#undef MF_FUNCTION

Thread::~Thread() {
    OSCancelThread(&mThread);
}

}  // namespace util
