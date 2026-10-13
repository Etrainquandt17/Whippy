#include "scn/subgame/setsuna/chara/Aim.h"

#include "lyt/LayoutContext.h"
#include "lyt/Utility.h"
#include "metafortress.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace chara {

Aim::Aim()
    : _0(0)
    , _4(new lyt::Layout(lyt::LayoutContext("subgame/setsuna/battle/Main", "AimScene", lyt::LayoutContext::DefaultAllocator())))
    , _8(new lyt::Layout(lyt::LayoutContext("subgame/setsuna/battle/Main", "Aim", lyt::LayoutContext::DefaultAllocator()))) {
    initialize();
}

Aim::~Aim() {
}

void Aim::updateMain() {
    _4->updateFrame();
    _8->updateFrame();
    _4->updateMatrix();
}

void Aim::drawLayout() const {
    lyt::Utility::SetupGX();
    _4->draw();
}

#define MF_FUNCTION initialize__Q53scn7subgame7setsuna5chara3AimFv
void Aim::initialize() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0xF7F15B05
    after1:
        mflr    r30
        lwz     r28, 0x0(r30)
        add     r28, r28, r30
        stw     r28, start
        lwz     r18, 0x4(r30)
        add     r28, r28, r18
        stw     r28, end
        bl      after2
        opword  MF_WORD(0x50)
        opword  0xBA216A53
    after2:
        mflr    r24
        lwz     r20, 0x0(r24)
        stw     r20, expected
    }
    _8->setParent(_4->pane("Loc_Aim"));
    hash = 0x811C9DDB;
    i = 1;
    first = start;
    limit = end - first + 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x01000193;
    }
    limit = expected;
    hash -= limit;
    if (hash == 0) {
        _8->rootPane().setVisibility(false);
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x120)
            opword  0xF095FE91
        after3:
            mflr    r21
            addi    r22, r21, 0x14
            mtlr    r22
            lwz     r30, 0x0(r21)
            stw     r30, -0x4(r1)
            stw     r22, 0x0(r1)
            stw     r21, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x14C)
            opword  0x10F48780
            opword  0x648B6080
            opword  MF_WORD(0x158)
        after4:
            mflr    r16
            stw     r16, base
            lwz     r30, 0x0(r16)
            stw     r30, offset
            lwz     r14, 0xC(r16)
            stw     r14, key
        }
        offset = offset ^ 0xE4;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION start__Q53scn7subgame7setsuna5chara3AimFv
void Aim::start() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 base;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x7FF88DE2
    after1:
        mflr    r27
        lwz     r18, 0x0(r27)
        stw     r18, expected
    }
    _0 = 1;
    asm {
        bl      after2
        opword  0x2E45FF0A
        opword  MF_WORD(0x4C)
        opword  0xD4333093
        opword  0xB4EDEF80
        opword  MF_WORD(0x58)
    after2:
        mflr    r25
        lwz     r21, 0x4(r25)
        lwz     r28, 0x10(r25)
        stw     r28, end
        stw     r21, start
    }
    last = end;
    word = start;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    _8->rootPane().setVisibility(true);
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0x100)
        after3:
            mflr    r16
            lwz     r24, 0x0(r16)
            stw     r24, -0x4(r1)
            stw     r16, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r16, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0x124)
            opword  MF_WORD(0x128)
        after4:
            mflr    r18
            lwz     r20, 0x4(r18)
            stw     r20, key
            lwz     r20, 0x0(r18)
            stw     r18, base
            stw     r20, offset
        }
        offset = offset - 0x19;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        _8->play("Set", "Set_Stay");
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setResult__Q53scn7subgame7setsuna5chara3AimFv
void Aim::setResult() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 p;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  MF_WORD(0x20)
        opword  0x4D13CE0E
    after1:
        mflr    r28
        lwz     r14, 0x4(r28)
        lwz     r24, 0x0(r28)
        add     r14, r24, r14
        stw     r14, end
        stw     r24, start
        bl      after2
        opword  MF_WORD(0x44)
        opword  0x95FB2943
    after2:
        mflr    r28
        lwz     r21, 0x0(r28)
        stw     r21, expected
    }
    _0 = 3;
    hash = 0xC5;
    p = start;
    last = end;
    while (true) {
        if (p == last) {
            break;
        }
        hash = *(u16*)p ^ ((hash << 4) ^ (hash >> 28));
        p += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    _8->rootPane().setVisibility(expected != hash);
}
#undef MF_FUNCTION

#define MF_FUNCTION reset__Q53scn7subgame7setsuna5chara3AimFv
void Aim::reset() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 key;
    u32 hash;
    u32 i;
    u32 first;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x8564B602
        opword  0xBCD92101
    after1:
        mflr    r15
        lwz     r29, 0x0(r15)
        stw     r29, start
        bl      after2
        opword  0xCC2F5C80
        opword  MF_WORD(0x44)
        opword  0x345D8A90
        opword  0xA4DE3F80
    after2:
        mflr    r15
        lwz     r28, 0x4(r15)
        add     r28, r28, r29
        stw     r28, end
        bl      after3
        opword  MF_WORD(0x64)
        opword  0x36F7D942
    after3:
        mflr    r14
        lwz     r25, 0x0(r14)
        stw     r25, expected
    }
    limit = end - start + 1;
    first = start;
    hash = 0;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash += *(u16*)(first + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash != expected) {
        asm {
            bl      after4
            opword  MF_WORD(0xF8)
        after4:
            mflr    r19
            lwz     r26, 0x0(r19)
            stw     r26, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r26
            bl      after5
            opword  MF_WORD(0x11C)
            opword  0x35D4BC0E
            opword  0x5F48CB0C
            opword  MF_WORD(0x128)
        after5:
            mflr    r29
            lwz     r26, 0xC(r29)
            stw     r26, key
            lwz     r26, 0x0(r29)
            stw     r29, base
            stw     r26, offset
        }
        offset = offset ^ 0x32;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    } else {
        _0 = 0;
    }
}
#undef MF_FUNCTION

lyt::PaneAccessor Aim::hitEffectLoc() {
    return _4->pane("Loc_Aim");
}

}
}
}
}
