#include "scn/goalgame/GGame.h"

#include "metafortress.h"

namespace scn {
namespace goalgame {

#define MF_FUNCTION __dt__Q33scn8goalgame5GGameFv
GGame::~GGame() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 i;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x5D020E1E
    after1:
        mflr    r24
        lwz     r29, 0x0(r24)
        stw     r29, expected
    }
    hash = 0x811C9E07;
    asm {
        bl      after2
        opword  MF_WORD(0x50)
        opword  0x5F5C870F
        opword  0x7DA92C0D
        opword  MF_WORD(0x5C)
    after2:
        mflr    r24
        lwz     r25, 0xc(r24)
        stw     r25, start
        lwz     r21, 0x0(r24)
        stw     r21, end
    }
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(last - i);
        hash *= 0x010001A7;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    mBGM.setIsPlayEnable(hash - expected != 0);
}
#undef MF_FUNCTION

#define MF_FUNCTION checkAllUfoState__Q33scn8goalgame5GGameFQ33scn8goalgame10GGUfoState
u32 GGame::checkAllUfoState(GGUfoState state) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 base;
    u32 size;
    u32 flags;
    int player;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  0x14BCD990
        opword  0xB865E290
        opword  MF_WORD(0x38)
        opword  0x64119680
        opword  MF_WORD(0x40)
        opword  0x90C29090
        opword  0x0C028F04
    after1:
        mflr    r19
        lwz     r25, 0x8(r19)
        lwz     r18, 0x10(r19)
        stw     r25, start
        add     r18, r25, r18
        stw     r18, end
    }
    size = end - start;
    base = start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0x8B49940B
    after2:
        mflr    r28
        lwz     r20, 0x0(r28)
        stw     r20, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    while (hash - expected != 0) {
    }
    flags = 0;
    for (player = 0; player <= _35A24; player++) {
        if (mUfo[player].isConstruct() && state == mUfo[player]->getState()) {
            flags |= FLAG_VAL_TBL[player];
        }
    }
    return flags;
}
#undef MF_FUNCTION

}
}
