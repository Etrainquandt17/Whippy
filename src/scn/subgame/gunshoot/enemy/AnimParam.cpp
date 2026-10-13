#include "scn/subgame/gunshoot/enemy/AnimParam.h"

#include "metafortress.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

int AnimParam::getStepNum() const {
    return mStepNum;
}

#define MF_FUNCTION getStepData__Q53scn7subgame8gunshoot5enemy9AnimParamCFi
const AnimParam::StepData& AnimParam::getStepData(int index) const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 p;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0x74023E93
        opword  MF_WORD(0x24)
    after1:
        mflr    r21
        lwz     r16, 0x4(r21)
        stw     r16, start
        bl      after2
        opword  0xD02BB901
        opword  0xDC630680
        opword  MF_WORD(0x40)
        opword  0xB8FF6293
        opword  0xC4BF6580
    after2:
        mflr    r21
        lwz     r16, 0x8(r21)
        stw     r16, end
    }
    hash = 0x811C9E29;
    asm {
        bl      after3
        opword  MF_WORD(0x64)
        opword  0xF2DD9BF7
    after3:
        mflr    r30
        lwz     r24, 0x0(r30)
        stw     r24, expected
    }
    p = start;
    last = end;
    while (true) {
        if (p == last) {
            break;
        }
        hash ^= *(u16*)p;
        hash *= 0x010001AB;
        p += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    while (hash - expected != 0) {
    }
    return mStepData[index];
}
#undef MF_FUNCTION

#define MF_FUNCTION getDamageAnimName__Q53scn7subgame8gunshoot5enemy9AnimParamCFQ53scn7subgame8gunshoot5enemy12HitAttribute
const char* AnimParam::getDamageAnimName(HitAttribute attribute) const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x11A0D61E
    after1:
        mflr    r17
        lwz     r14, 0x0(r17)
        stw     r14, expected
        bl      after2
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
    after2:
        mflr    r29
        lwz     r19, 0x0(r29)
        add     r19, r19, r29
        stw     r19, start
        lwz     r24, 0x4(r29)
        add     r19, r19, r24
        stw     r19, end
    }
    hash = 0x811C9E29;
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    while (true) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x010001AB;
        i += 2;
    }
    bool none = hash - expected != 0 || attribute == HIT_ATTRIBUTE_NONE;
    if (none) {
        return 0;
    }
    u32 reference = mDamageAnimList.anim().name[attribute - 1];
    return mDamageAnimList.str(reference) + 4;
}
#undef MF_FUNCTION

int AnimParam::getDamagePlayListIndex() const {
    return mDamageAnimList.anim().playListIndex;
}

}}}}  // namespace scn::subgame::gunshoot::enemy
