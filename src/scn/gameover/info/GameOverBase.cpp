#include "scn/gameover/info/GameOverBase.h"

#include "metafortress.h"

namespace scn {
namespace gameover {
namespace info {

#define MF_FUNCTION cursorPos__Q43scn8gameover4info12GameOverBaseCFv
f32 GameOverBase::cursorPos() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;
    f32 pos;

    hash = 0xB3;
    asm {
        bl      after1
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
        opword  0x94E96C91
    after1:
        mflr    r21
        lwz     r29, 0x0(r21)
        lwz     r23, 0x4(r21)
        add     r29, r29, r21
        add     r23, r23, r29
        stw     r29, start
        stw     r23, end
    }
    word = start;
    last = end;
    if (mState == 2) {
        pos = 1.0f - _7DC.normalizedFrame();
        pos *= pos;
        pos = 1.0f - pos;
    } else {
        pos = 1.0f;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x98)
        opword  0x47760750
    after2:
        mflr    r24
        lwz     r14, 0x0(r24)
        stw     r14, expected
    }
    for (;;) {
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
        word += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0 || _7E8 == 0) {
        pos = 1.0f - pos;
    }
    return pos;
}
#undef MF_FUNCTION

}
}
}
