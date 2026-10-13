#include "scn/subgame/gunshoot/enemy/CollisionItem.h"

#include "metafortress.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

bool CollisionItem::isActive() const {
    return !_F9 && _F8;
}

void CollisionItem::deactivate() {
    _F8 = false;
    mShieldValue = 0;
    _104 = 0;
}

int CollisionItem::shieldValue() const {
    return mShieldValue;
}

#define MF_FUNCTION addDamage__Q53scn7subgame8gunshoot5enemy13CollisionItemFi
void CollisionItem::addDamage(int damage) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash = 0xC5;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x7D964073
    after1:
        mflr    r26
        lwz     r23, 0x0(r26)
        stw     r23, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  MF_WORD(0x40)
        opword  0x24482B93
    after2:
        mflr    r25
        lwz     r15, 0x4(r25)
        stw     r15, end
        lwz     r24, 0x0(r25)
        stw     r24, start
    }
    u32 last = end;
    u32 p = start;
    _104 -= damage;
    p -= 2;
    while (p != last - 2) {
        p += 2;
        hash = *(u16*)p ^ ((hash << 4) ^ (hash >> 28));
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0 || _104 < 0) {
        _104 = 0;
        mShieldValue = 0;
    }
}
#undef MF_FUNCTION

bool CollisionItem::isBroken() const {
    return _104 <= 0;
}

#define MF_FUNCTION recover__Q53scn7subgame8gunshoot5enemy13CollisionItemFv
void CollisionItem::recover() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash = 0x811C9E53;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0x669DEF07
        opword  0xCB139F09
    after1:
        mflr    r16
        lwz     r15, 0x4(r16)
        stw     r15, start
        lwz     r25, 0x0(r16)
        stw     r25, end
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0xF5CC6715
    after2:
        mflr    r18
        lwz     r16, 0x0(r18)
        stw     r16, expected
    }
    u32 last;
    u32 i;
    u32 limit;

    limit = end - start + 1;
    i = 1;
    last = end - 1;
    while (true) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x010001D1;
        i += 2;
    }
    _F8 = expected == hash;
    _104 = _100;
}
#undef MF_FUNCTION

}
}
}
}
