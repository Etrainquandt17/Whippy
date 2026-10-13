#include "scn/step/StageKindUtil.h"

#include "metafortress.h"
#include "types.h"

namespace scn {
namespace step {

namespace {

struct Info {
    LevelKind level;
    u32 sphereNum;
    bool isBoss;
};

const Info T_INFOS[] = {
    { LEVEL_KIND_0, 3, false }, { LEVEL_KIND_0, 3, false }, { LEVEL_KIND_0, 3, false }, { LEVEL_KIND_0, 4, false },
    { LEVEL_KIND_0, 0, true },

    { LEVEL_KIND_1, 3, false }, { LEVEL_KIND_1, 4, false }, { LEVEL_KIND_1, 4, false }, { LEVEL_KIND_1, 5, false },
    { LEVEL_KIND_1, 0, true },

    { LEVEL_KIND_2, 3, false }, { LEVEL_KIND_2, 4, false }, { LEVEL_KIND_2, 4, false }, { LEVEL_KIND_2, 5, false },
    { LEVEL_KIND_2, 0, true },

    { LEVEL_KIND_3, 3, false }, { LEVEL_KIND_3, 4, false }, { LEVEL_KIND_3, 4, false }, { LEVEL_KIND_3, 4, false },
    { LEVEL_KIND_3, 4, false }, { LEVEL_KIND_3, 0, true },

    { LEVEL_KIND_4, 4, false }, { LEVEL_KIND_4, 4, false }, { LEVEL_KIND_4, 4, false }, { LEVEL_KIND_4, 4, false },
    { LEVEL_KIND_4, 4, false }, { LEVEL_KIND_4, 0, true },

    { LEVEL_KIND_5, 3, false }, { LEVEL_KIND_5, 4, false }, { LEVEL_KIND_5, 4, false }, { LEVEL_KIND_5, 5, false },
    { LEVEL_KIND_5, 5, false }, { LEVEL_KIND_5, 0, true },

    { LEVEL_KIND_6, 5, false }, { LEVEL_KIND_6, 5, false }, { LEVEL_KIND_6, 5, false }, { LEVEL_KIND_6, 0, true },
    { LEVEL_KIND_6, 0, true },  { LEVEL_KIND_6, 0, true },
};

Info t_info(StageKind stage) {
    return T_INFOS[stage];
}

}

u32 StageKindUtil::SphereTotalNum() {
    u32 total = 0;
    for (u32 stage = 0; stage <= STAGE_KIND_38; stage++) {
        total += SphereTotalNum(static_cast<StageKind>(stage));
    }
    return total;
}

u32 StageKindUtil::SphereTotalNum(StageKind stage) {
    return t_info(stage).sphereNum;
}

#define MF_FUNCTION SphereTotalNum__Q33scn4step13StageKindUtilFQ33scn4step9LevelKind
u32 StageKindUtil::SphereTotalNum(LevelKind level) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 key;
    u32 p;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;
    u32 total;

    total = 0;
    p = 0x811D0000;
    hash = p - 0x61AD;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0xE0C7AA92
        opword  0xB56C8D08
    after1:
        mflr    r15
        lwz     r16, 0x0(r15)
        add     r16, r16, r15
        stw     r16, start
        bl      after2
        opword  0xACD37981
        opword  0x29698002
        opword  MF_WORD(0x58)
    after2:
        mflr    r15
        lwz     r18, 0x8(r15)
        add     r16, r16, r18
        stw     r16, end
        bl      after3
        opword  MF_WORD(0x70)
        opword  0x84DEDC69
    after3:
        mflr    r15
        lwz     r20, 0x0(r15)
        stw     r20, expected
    }
    for (p = 0; p <= STAGE_KIND_38; p++) {
        if (level == BelongLevelKind(static_cast<StageKind>(p))) {
            total += SphereTotalNum(static_cast<StageKind>(p));
        }
    }
    i = 1;
    last = end;
    p = start;
    p = last - p;
    limit = p + 1;
    p = last - 1;
    while (i != limit) {
        hash ^= *(u16*)(p - i);
        hash *= 0x010001D1;
        i += 2;
    }
    hash = (hash & ~expected) | (expected & ~hash);
    hash = __cntlzw(hash);
    limit = hash >> 5;
    hash = limit >> 6;
    hash = limit - hash;
    if (hash == 0) {
        asm {
            bl      after4
            opword  0xC4C5E780
            opword  MF_WORD(0x124)
        after4:
            mflr    r17
            lwz     r23, 0x4(r17)
            stw     r23, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r23
            bl      after5
            opword  MF_WORD(0x148)
            opword  0x45CCCE0E
            opword  0xE9E35806
            opword  MF_WORD(0x154)
        after5:
            mflr    r19
            lwz     r21, 0xc(r19)
            stw     r21, key
            lwz     r21, 0x0(r19)
            stw     r19, base
            stw     r21, offset
        }
        offset = offset ^ 0xBF;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    } else {
        return total;
    }
}
#undef MF_FUNCTION

bool StageKindUtil::IsBossStage(StageKind stage) {
    return t_info(stage).isBoss;
}

#define MF_FUNCTION IsFinalStage__Q33scn4step13StageKindUtilFQ33scn4step9StageKind
bool StageKindUtil::IsFinalStage(StageKind stage) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 size;
    u32 tail;
    u32 i;

    hash = 0;
    asm {
        bl      after1
        opword  0x90D16508
        opword  MF_WORD(0x2C)
        opword  0xA8110890
        opword  0xB4397A92
        opword  MF_WORD(0x38)
        opword  0xA0FD4281
        opword  0x9C07B080
    after1:
        mflr    r14
        lwz     r22, 0x4(r14)
        lwz     r20, 0x10(r14)
        add     r20, r22, r20
        stw     r22, start
        stw     r20, end
    }
    size = end - start;
    tail = end;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash += *(u16*)(tail - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    asm {
        bl      after2
        opword  MF_WORD(0xB0)
        opword  0x28710C05
    after2:
        mflr    r29
        lwz     r15, 0x0(r29)
        stw     r15, expected
    }
    hash ^= hash << 20;
    switch (stage) {
    case STAGE_KIND_37:
    case STAGE_KIND_38:
        return expected == hash;
    default:
        return expected != hash;
    }
}
#undef MF_FUNCTION

LevelKind StageKindUtil::BelongLevelKind(StageKind stage) {
    return t_info(stage).level;
}

u32 StageKindUtil::StageCount(LevelKind level) {
    u32 count = 0;
    for (u32 stage = 0; stage < STAGE_KIND_38 + 1; stage++) {
        if (level == t_info(static_cast<StageKind>(stage)).level) {
            count++;
        }
    }
    return count;
}

}
}
