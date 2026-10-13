#include "scn/step/enemy/Signal.h"

#include "metafortress.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

Signal::Signal() : mSignal(0xFFFFFFFF) {
}

#define MF_FUNCTION clear__Q43scn4step5enemy6SignalFv
void Signal::clear() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x747B4790
        opword  0x9C576F80
        opword  MF_WORD(0x30)
        opword  0x3478DC80
    after1:
        mflr    r14
        lwz     r16, 0x0(r14)
        add     r16, r16, r14
        stw     r16, start
        lwz     r23, 0xc(r14)
        add     r16, r16, r23
        stw     r16, end
    }
    hash = 0x811C9DDB;
    asm {
        bl      after2
        opword  MF_WORD(0x60)
        opword  0xD219329D
    after2:
        mflr    r18
        lwz     r20, 0x0(r18)
        stw     r20, expected
    }
    limit = end - start;
    base = start;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash = (hash & ~expected) | (expected & ~hash);
    hash = __cntlzw(hash);
    hash = (hash >> 5) + ((hash >> 5) * 56);
    if (hash == 0) {
        volatile u32 key;
        volatile u32 base2;
        volatile u32 response;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0xF8264A06
            opword  MF_WORD(0xF8)
        after3:
            mflr    r28
            lwz     r23, 0x4(r28)
            stw     r23, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r28, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0x11C)
            opword  MF_WORD(0x120)
        after4:
            mflr    r24
            lwz     r29, 0x0(r24)
            stw     r24, base2
            lwz     r22, 0x4(r24)
            stw     r29, offset
            stw     r22, key
        }
        offset = offset - 0x5B;
        response = offset ^ key;
        response = response + base2;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    } else {
        mSignal = 0xFFFFFFFF;
    }
}
#undef MF_FUNCTION

bool Signal::isValid() const {
    return mSignal != 0xFFFFFFFF;
}

void Signal::set(u32 signal) {
    mSignal = signal;
}

u32 Signal::get() const {
    return mSignal;
}

}
}
}
