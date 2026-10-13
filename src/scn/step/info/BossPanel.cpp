#include "scn/step/info/BossPanel.h"

#include "metafortress.h"

namespace scn {
namespace step {
namespace info {

#define MF_FUNCTION damage__Q43scn4step4info9BossPanelFf
void BossPanel::damage(f32 rate) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 tail;
    u32 hash = 0x811C9E29;

    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x57EF9B4D
    after1:
        mflr    r21
        lwz     r26, 0x0(r21)
        stw     r26, expected
        bl      after2
        opword  MF_WORD(0x48)
        opword  0x401B8D93
        opword  MF_WORD(0x50)
        opword  0x34581C81
        opword  0x73558505
    after2:
        mflr    r25
        lwz     r24, 0x0(r25)
        add     r24, r24, r25
        lwz     r27, 0x8(r25)
        stw     r24, start
        add     r27, r27, r24
        stw     r27, end
    }
    word = start;
    tail = end;
    _B0C = rate;
    for (; word != tail; word += 2) {
        hash ^= *(u16*)word;
        hash *= 0x010001AB;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected == 0 && 0.0f == rate) {
        set(0.0f);
    } else if (hash - expected != 0 || !_B18) {
        if (hash - expected == 0 && _B19) {
            mLayout.play("Damage", "TransformWait");
        } else {
            mLayout.play("Damage", "Wait");
        }
        setLifeBarRate(rate);
        if (hash - expected != 0 || _B90 == 0) {
            _B94.reset(20);
            _B14 = 0.0f;
            _B90 = 3;
        }
    }
}
#undef MF_FUNCTION

}
}
}
