#include "scn/subgame/setsuna/chara/GameResultChara.h"

#include "metafortress.h"

// TODO: remove once the unit's other callers of these inline functions exist.
#pragma dont_inline on

namespace scn {
namespace subgame {
namespace setsuna {
namespace chara {

#define MF_FUNCTION startWait__Q53scn7subgame7setsuna5chara15GameResultCharaFv
void GameResultChara::startWait() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash = 0x811C9E29;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0x14B0E093
    after1:
        mflr    r24
        lwz     r23, 0x4(r24)
        lwz     r18, 0x0(r24)
        add     r23, r18, r23
        stw     r23, end
        stw     r18, start
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0x235BB93F
    after2:
        mflr    r24
        lwz     r15, 0x0(r24)
        stw     r15, expected
    }
    u32 i = 1;
    u32 base = start;
    u32 limit = end - base + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001AB;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0 || _50) {
        _4C = 0;
        _388 = _358.setAnim(0, "InA");
        _388.setFrame(0.0f);
        _388.start(expected == hash);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION reset__Q53scn7subgame7setsuna5chara15GameResultCharaFv
void GameResultChara::reset() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 limit;
    u32 hash;
    u32 i;

    _350->releaseAndVanish();
    asm {
        bl      after1
        opword  0xC064F880
        opword  0xB4CE0F80
        opword  MF_WORD(0x38)
    after1:
        mflr    r28
        lwz     r23, 0x8(r28)
        stw     r23, start
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0x543C4291
        opword  0x2056B980
    after2:
        mflr    r28
        lwz     r25, 0x0(r28)
        add     r25, r25, r23
        stw     r25, end
    }
    _4C = 9;
    base = start;
    limit = end - base + 1;
    _50 = false;
    hash = 0x811C9E29;
    for (u32 n = 0; n < _8; n++) {
        _8C[n].setVisibility(false);
        _1F8[n] = g3d::ModelAnimAccessor();
        _274[n] = g3d::ModelAnimAccessor();
        _334[n] = false;
    }
    _348 = 0;
    asm {
        bl      after3
        opword  MF_WORD(0x118)
        opword  0x6FF3A678
    after3:
        mflr    r17
        lwz     r25, 0x0(r17)
        stw     r25, expected
    }
    _358.clearAnim(0);
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001AB;
    }
    _388 = g3d::ModelAnimAccessor();
    hash += hash << 13;
    setMyCharaVisibility(false);
    _390.setVisibility(false);
    _390.clearAnim(1);
    hash ^= hash >> 7;
    _3A8.setVisibility(false);
    hash += hash << 3;
    _3A8.clearAnim();
    hash ^= hash >> 17;
    _3D8 = hel::math::Vector3();
    hash += hash << 5;
    _330 = hash - expected != 0;
}
#undef MF_FUNCTION

}
}
}
}
