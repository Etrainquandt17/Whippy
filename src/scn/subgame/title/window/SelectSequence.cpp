#include "scn/subgame/title/window/SelectSequence.h"

#include "metafortress.h"

namespace scn {
namespace subgame {
namespace title {
namespace window {

#define MF_FUNCTION nextSeq__Q53scn7subgame5title6window14SelectSequenceCFv
int SelectSequence::nextSeq() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x3E39B5D9
    after1:
        mflr    r17
        lwz     r29, 0x0(r17)
        stw     r29, expected
        bl      after2
        opword  MF_WORD(0x34)
        opword  MF_WORD(0x38)
        opword  0xBC4E3181
    after2:
        mflr    r14
        lwz     r20, 0x0(r14)
        add     r20, r20, r14
        stw     r20, start
        lwz     r21, 0x4(r14)
        add     r20, r20, r21
        stw     r20, end
    }
    u32 p;
    u32 last;
    u32 hash;

    last = end;
    p = start;
    hash = 0x811C9E07;
    while (true) {
        if (p == last) {
            break;
        }
        hash ^= *(u16*)p;
        hash *= 0x010001A7;
        p += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    while (hash - expected != 0) {
    }
    return _C[mSelectUnit.selectedIndex()];
}
#undef MF_FUNCTION

}
}
}
}
