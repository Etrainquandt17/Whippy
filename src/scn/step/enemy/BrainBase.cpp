#include "scn/step/enemy/BrainBase.h"

#include "metafortress.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

BrainBase::BrainBase(Enemy& enemy)
    : mEnemy(enemy) {
}

Enemy& BrainBase::obj() const {
    return mEnemy;
}

bool BrainBase::onStart() {
    return false;
}

bool BrainBase::onRecover() {
    return false;
}

#define MF_FUNCTION onLanding__Q43scn4step5enemy9BrainBaseFv
bool BrainBase::onLanding() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x0C640290
        opword  MF_WORD(0x30)
        opword  0xD8EC4A80
    after1:
        mflr    r17
        lwz     r23, 0x0(r17)
        add     r23, r23, r17
        lwz     r14, 0x8(r17)
        stw     r23, start
        add     r14, r14, r23
        stw     r14, end
    }
    base = start;
    limit = end - base + 1;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001A7;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x94)
        opword  0x5C8C42C9
    after2:
        mflr    r14
        lwz     r27, 0x0(r14)
        stw     r27, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    return expected != hash;
}
#undef MF_FUNCTION

void BrainBase::update() {
}

BrainBase::~BrainBase() {
}

}}}  // namespace scn::step::enemy
