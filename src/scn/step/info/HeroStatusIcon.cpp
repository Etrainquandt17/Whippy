#include "scn/step/info/HeroStatusIcon.h"

#include "info/Util.h"
#include "lyt/LayoutContext.h"
#include "mem/HeapExp.h"
#include "metafortress.h"
#include "scn/step/info/HeroStatusIconSyncer.h"
#include "util/ObjRefHandleInline.h"

namespace scn {
namespace step {
namespace info {

namespace {

const char* T_ARC_PATH = "step/game/Main";

const char* T_ABILITY_KIND_TO_PATH[] = {
    0,
    "step/game/ability_icon/Sword",
    "step/game/ability_icon/Cutter",
    "step/game/ability_icon/Leaf",
    "step/game/ability_icon/Whip",
    "step/game/ability_icon/Fire",
    "step/game/ability_icon/Needle",
    "step/game/ability_icon/Beam",
    "step/game/ability_icon/Spark",
    "step/game/ability_icon/Stone",
    "step/game/ability_icon/Sleep",
    "step/game/ability_icon/Parasol",
    "step/game/ability_icon/Water",
    "step/game/ability_icon/Highjump",
    "step/game/ability_icon/Tornado",
    "step/game/ability_icon/Bomb",
    "step/game/ability_icon/Spear",
    "step/game/ability_icon/Hammer",
    "step/game/ability_icon/Ice",
    "step/game/ability_icon/Wing",
    "step/game/ability_icon/Ninja",
    "step/game/ability_icon/Fighter",
    "step/game/ability_icon/Crash",
    "step/game/ability_icon/Mike",
    "step/game/ability_icon/Landia",
    "step/game/ability_icon/SuperSword",
    "step/game/ability_icon/SuperFire",
    "step/game/ability_icon/SuperBeam",
    "step/game/ability_icon/SuperHammer",
    "step/game/ability_icon/SuperIce",
    "step/game/ability_icon/Mike",
    "step/game/ability_icon/Mike",
    0,
    0,
    0,
};

}

#define MF_FUNCTION __ct__Q43scn4step4info14HeroStatusIconFRQ23mem10IAllocatorRCQ23lyt12PaneAccessorQ43scn4step4hero4Kind
HeroStatusIcon::HeroStatusIcon(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, hero::Kind kind)
    : mHeap(allocator, 0x6000, "IfHrStIcon")
    , _60(lyt::LayoutContext(T_ARC_PATH, "HeroStatusIcon", allocator))
    , _518(lyt::LayoutContext(T_ARC_PATH, "HeroPEffect", allocator))
    , _6A8(&_60)
    , _6AC(parent)
    , _6C0(kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 mfBase;
    volatile u32 response;
    volatile u32 addend;
    volatile u32 offset;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;

    hash = 0xB5;
    ::info::selectHeroPane(_60, kind);
    asm {
        bl      after1
        opword  MF_WORD(0xE4)
        opword  0xABADDE71
    after1:
        mflr    r17
        lwz     r22, 0x0(r17)
        stw     r22, expected
    }
    _60.setParent(parent);
    asm {
        bl      after2
        opword  MF_WORD(0x108)
        opword  0x80ADB091
        opword  MF_WORD(0x110)
        opword  0x4C864D80
        opword  0x0CC58593
    after2:
        mflr    r27
        lwz     r19, 0x8(r27)
        lwz     r24, 0x0(r27)
        add     r24, r24, r27
        stw     r24, start
        add     r19, r19, r24
        stw     r19, end
    }
    _518.setParent(_60.paneByName("HeroPEffectN"));
    i = 1;
    last = end;
    limit = last - start + 1;
    _518.setAnimByName("Pinch");
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
    }
    hash += hash << 3;
    _518.rootPane().setVisibility(false);
    hash ^= hash >> 11;
    createIcon(hero::ABILITY_KIND_NORMAL);
    last = hash << 15;
    hash += last;
    last = expected;
    last = hash - last;
    if (last != 0) {
        asm {
            bl      after3
            opword  0xE4B3F191
            opword  MF_WORD(0x20C)
        after3:
            mflr    r29
            lwz     r18, 0x4(r29)
            stw     r18, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r18, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r18
            bl      after4
            opword  MF_WORD(0x230)
            opword  0x248AD092
            opword  MF_WORD(0x238)
        after4:
            mflr    r26
            lwz     r28, 0x8(r26)
            stw     r28, addend
            lwz     r28, 0x0(r26)
            stw     r26, mfBase
            stw     r28, offset
        }
        response = offset + addend;
        response = response + mfBase;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    } else {
        startWaitAnim();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION __dt__Q43scn4step4info14HeroStatusIconFv
HeroStatusIcon::~HeroStatusIcon() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 mfBase;
    volatile u32 offset;
    volatile u32 response;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0x19B61F01
        opword  MF_WORD(0x34)
        opword  0xEC3AEA90
        opword  MF_WORD(0x3C)
        opword  0x34661A81
        opword  0x28398B80
    after1:
        mflr    r14
        lwz     r16, 0xc(r14)
        lwz     r20, 0x4(r14)
        stw     r20, end
        stw     r16, start
    }
    last = end;
    limit = last - start + 1;
    hash = 0;
    i = -1;
    last--;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0xAB6A85EA
    after2:
        mflr    r26
        lwz     r21, 0x0(r26)
        stw     r21, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash == expected) {
        if (HeroStatusIconSyncer::IsExist()) {
            HeroStatusIconSyncer::Object().notifyStopPinchAnim(this);
        }
        return;
    }
    asm {
        bl      after3
        opword  0xF1044201
        opword  0x40049A91
        opword  MF_WORD(0x118)
    after3:
        mflr    r19
        lwz     r29, 0x8(r19)
        stw     r29, -0x4(r1)
        stw     r19, 0x0(r1)
        stw     r29, -0x4(r1)
        stw     r19, -0x8(r1)
        mtlr    r29
        bl      after4
        opword  MF_WORD(0x13C)
        opword  0xD7063D03
        opword  0xECA47F92
        opword  MF_WORD(0x148)
    after4:
        mflr    r27
        lwz     r21, 0x0(r27)
        lwz     r14, 0xc(r27)
        stw     r14, key
        stw     r21, offset
        stw     r27, mfBase
    }
    offset = offset - 0x93;
    response = offset ^ key;
    response = response + mfBase;
    asm {
        lwz     r27, response
        mtlr    r27
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setParent__Q43scn4step4info14HeroStatusIconFRCQ23lyt12PaneAccessor
void HeroStatusIcon::setParent(const lyt::PaneAccessor& parent) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 mfBase;
    volatile u32 response;
    volatile u32 offset;
    u32 hash;
    u32 t2;
    u32 t1;
    u32 p;
    u32 stop;

    hash = 0xB3;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x2FBF300A
        opword  0xC2E8DE0C
        opword  MF_WORD(0x38)
        opword  0xACC2EC80
    after1:
        mflr    r29
        lwz     r20, 0x0(r29)
        lwz     r16, 0xc(r29)
        add     r20, r20, r29
        add     r16, r16, r20
        stw     r20, start
        stw     r16, end
    }
    _6AC = parent;
    p = start;
    stop = end;
    p -= 2;
    for (;;) {
        p += 2;
        if (p == stop) {
            break;
        }
        hash = *(u16*)p ^ ((hash << 4) ^ (hash >> 28));
    }
    _6A8->unsetParent();
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0xF8BB43A4
    after2:
        mflr    r16
        lwz     r30, 0x0(r16)
        stw     r30, expected
    }
    t1 = expected;
    t1 = t1 & ~hash;
    t2 = expected;
    t2 = hash & ~t2;
    hash = t1 | t2;
    t2 = hash << 4;
    hash += t2;
    if (hash == 0) {
        _6A8->setParent(parent);
        return;
    }
    asm {
        bl      after3
        opword  0x7C7CE080
        opword  0x98B4A593
        opword  0xC4360293
        opword  MF_WORD(0x104)
    after3:
        mflr    r21
        lwz     r24, 0xc(r21)
        stw     r24, -0x4(r1)
        stw     r21, 0x0(r1)
        stw     r24, -0x4(r1)
        stw     r21, -0x8(r1)
        mtlr    r24
        bl      after4
        opword  MF_WORD(0x128)
        opword  0xDF71D304
        opword  0xEC575380
        opword  MF_WORD(0x134)
    after4:
        mflr    r27
        stw     r27, mfBase
        lwz     r30, 0x0(r27)
        stw     r30, offset
        lwz     r28, 0xc(r27)
        stw     r28, key
    }
    key = 0;
    response = offset;
    response = response + mfBase;
    asm {
        lwz     r20, response
        mtlr    r20
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION changeIcon__Q43scn4step4info14HeroStatusIconFQ43scn4step4hero11AbilityKind
void HeroStatusIcon::changeIcon(hero::AbilityKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 addend;
    volatile u32 response;
    volatile u32 mfBase;
    u32 hash;
    hero::AbilityKind k;
    HeroStatusIcon* self;
    u32 last;
    u32 i;
    u32 limit;
    u32 tail;

    self = this;
    k = kind;
    hash = 0x811C9E53;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x64762293
    after1:
        mflr    r22
        lwz     r29, 0x0(r22)
        add     r29, r29, r22
        stw     r29, start
        bl      after2
        opword  0x4E75160B
        opword  MF_WORD(0x50)
    after2:
        mflr    r22
        lwz     r24, 0x4(r22)
        add     r29, r29, r24
        stw     r29, end
        bl      after3
        opword  MF_WORD(0x68)
        opword  0xCCF1A117
    after3:
        mflr    r25
        lwz     r30, 0x0(r25)
        stw     r30, expected
    }
    self->disposeIcon();
    i = 1;
    tail = end;
    limit = tail - start + 1;
    last = tail - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x010001D1;
        i += 2;
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    limit = hash - limit;
    if (limit != 0) {
        asm {
            bl      after4
            opword  MF_WORD(0xF0)
        after4:
            mflr    r14
            lwz     r17, 0x0(r14)
            stw     r17, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r17, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r17
            bl      after5
            opword  MF_WORD(0x114)
            opword  MF_WORD(0x118)
        after5:
            mflr    r26
            lwz     r20, 0x4(r26)
            stw     r20, addend
            lwz     r20, 0x0(r26)
            stw     r26, mfBase
            stw     r20, offset
        }
        offset = offset - 0xD;
        response = offset + addend;
        response = response + mfBase;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        self->createIcon(k);
    }
}
#undef MF_FUNCTION

void HeroStatusIcon::updateFrame() {
    _6A8->updateFrame();
    _518.updateFrame();
}

#define MF_FUNCTION startWaitAnim__Q43scn4step4info14HeroStatusIconFv
void HeroStatusIcon::startWaitAnim() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 mfBase;
    volatile u32 addend;
    volatile u32 response;
    u32 hash;
    u32 last;
    u32 i;
    u32 limit;
    u32 tail;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x54A040E9
    after1:
        mflr    r16
        lwz     r24, 0x0(r16)
        stw     r24, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0x1C078090
    after2:
        mflr    r18
        lwz     r16, 0x0(r18)
        add     r16, r16, r18
        stw     r16, start
        bl      after3
        opword  MF_WORD(0x58)
        opword  0xB02BC080
        opword  0x30E67F01
    after3:
        mflr    r18
        lwz     r29, 0x0(r18)
        add     r16, r16, r29
        stw     r16, end
    }
    _6A8->setAnimByName("Wait");
    hash = 0x811C9DC5;
    limit = end - start + 1;
    tail = end;
    i = -1;
    last = tail - 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x01000181;
    }
    hash += hash << 13;
    _6A8->start(true);
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash ^= expected;
    if (hash == 0) {
        stopPinchAnim();
        return;
    }
    asm {
        bl      after4
        opword  0x80921A02
        opword  MF_WORD(0x124)
    after4:
        mflr    r25
        lwz     r20, 0x4(r25)
        stw     r20, -0x4(r1)
        stw     r25, 0x0(r1)
        stw     r20, -0x4(r1)
        stw     r25, -0x8(r1)
        mtlr    r20
        bl      after5
        opword  MF_WORD(0x148)
        opword  0xF8D7F080
        opword  0xEDD17C03
        opword  MF_WORD(0x154)
    after5:
        mflr    r29
        lwz     r19, 0x0(r29)
        lwz     r18, 0xc(r29)
        stw     r18, addend
        stw     r19, offset
        stw     r29, mfBase
    }
    response = offset + addend;
    response = response + mfBase;
    asm {
        lwz     r21, response
        mtlr    r21
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION startDamageAnim__Q43scn4step4info14HeroStatusIconFv
void HeroStatusIcon::startDamageAnim() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 mfBase;
    volatile u32 key;
    volatile u32 response;
    volatile u32 offset;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x234062EC
    after1:
        mflr    r19
        lwz     r26, 0x0(r19)
        stw     r26, expected
    }
    _6A8->setAnimByName("Damage");
    asm {
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0x848F3891
        opword  MF_WORD(0x54)
    after2:
        mflr    r26
        lwz     r29, 0x0(r26)
        lwz     r19, 0x8(r26)
        stw     r19, start
        stw     r29, end
    }
    base = start;
    limit = end - base + 1;
    _6A8->start(false);
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 61;
        hash += *(u16*)(base + i - 1);
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash -= expected;
    hash -= hash >> 7;
    if (hash == 0) {
        stopPinchAnim();
        return;
    }
    asm {
        bl      after3
        opword  MF_WORD(0xE4)
    after3:
        mflr    r29
        lwz     r20, 0x0(r29)
        stw     r20, -0x4(r1)
        stw     r29, 0x0(r1)
        stw     r20, -0x4(r1)
        stw     r29, -0x8(r1)
        mtlr    r20
        bl      after4
        opword  MF_WORD(0x108)
        opword  MF_WORD(0x10C)
    after4:
        mflr    r16
        stw     r16, mfBase
        lwz     r23, 0x0(r16)
        stw     r23, offset
        lwz     r21, 0x4(r16)
        stw     r21, key
    }
    offset = offset + 0x21;
    response = offset ^ key;
    response = response + mfBase;
    asm {
        lwz     r24, response
        mtlr    r24
        blr
    }
}
#undef MF_FUNCTION

void HeroStatusIcon::startCureAnim() {
    _6A8->setAnimByName("Flash");
    _6A8->start(false);
    stopPinchAnim();
}

#define MF_FUNCTION startDeadAnim__Q43scn4step4info14HeroStatusIconFv
#define MF_FUNCTION startDeadAnim__Q43scn4step4info14HeroStatusIconFv
void HeroStatusIcon::startDeadAnim() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x9CA71C80
        opword  0x7CDB0581
    after1:
        mflr    r22
        lwz     r30, 0x0(r22)
        stw     r30, start
        bl      after2
        opword  MF_WORD(0x38)
        opword  0x4CA71A80
        opword  0xCCD58C92
    after2:
        mflr    r22
        lwz     r30, 0x0(r22)
        stw     r30, end
        bl      after3
        opword  MF_WORD(0x54)
        opword  0xCD71B922
    after3:
        mflr    r17
        lwz     r23, 0x0(r17)
        stw     r23, expected
    }
    _6A8->setAnimByName("Dead");
    base = start;
    limit = end - base + 1;
    hash = 0;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    _6A8->start(expected == hash);
    stopPinchAnim();
}
#undef MF_FUNCTION

void HeroStatusIcon::startPinchAnim() {
    _6A8->play("Pinch");
    if (HeroStatusIconSyncer::IsExist()) {
        HeroStatusIconSyncer::Object().notifyStartPinchAnim(this);
    }
    _518.start(true);
    _518.rootPane().setVisibility(true);
}

void HeroStatusIcon::stopPinchAnim() {
    if (HeroStatusIconSyncer::IsExist()) {
        HeroStatusIconSyncer::Object().notifyStopPinchAnim(this);
    }
    _518.rootPane().setVisibility(false);
    _518.stop();
}

#define MF_FUNCTION startGetAbilityAnim__Q43scn4step4info14HeroStatusIconFv
void HeroStatusIcon::startGetAbilityAnim() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 mfBase;
    volatile u32 response;
    volatile u32 key;
    u32 p;
    u32 stop;
    u32 hash;

    asm {
        bl      after1
        opword  0xC93A160D
        opword  MF_WORD(0x28)
        opword  0xF7C14704
        opword  0x2093C593
        opword  MF_WORD(0x34)
    after1:
        mflr    r24
        lwz     r21, 0x4(r24)
        lwz     r15, 0x10(r24)
        stw     r15, end
        stw     r21, start
    }
    p = start;
    stop = end;
    _6A8->setAnimByName("Flash");
    asm {
        bl      after2
        opword  MF_WORD(0x64)
        opword  0x5B3C7C37
    after2:
        mflr    r16
        lwz     r15, 0x0(r16)
        stw     r15, expected
    }
    hash = 0xC1;
    for (; p != stop; p += 2) {
        hash = *(u16*)p ^ ((hash << 4) ^ (hash >> 28));
    }
    hash += hash << 13;
    _6A8->start(false);
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash -= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xE8)
        after3:
            mflr    r16
            lwz     r26, 0x0(r16)
            stw     r26, -0x4(r1)
            stw     r16, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r16, -0x8(r1)
            mtlr    r26
            bl      after4
            opword  MF_WORD(0x10C)
            opword  MF_WORD(0x110)
        after4:
            mflr    r24
            lwz     r29, 0x0(r24)
            stw     r24, mfBase
            lwz     r19, 0x4(r24)
            stw     r29, offset
            stw     r19, key
        }
        offset = offset + 0xE1;
        response = offset ^ key;
        response = response + mfBase;
        asm {
            lwz     r20, response
            mtlr    r20
            blr
        }
    } else {
        stopPinchAnim();
    }
}
#undef MF_FUNCTION

bool HeroStatusIcon::isAnimEnd() const {
    return _6A8->isAnimEnd();
}

f32 HeroStatusIcon::animFrame() const {
    return _6A8->frame();
}

void HeroStatusIcon::setAnimFrame(f32 frame) {
    _6A8->setFrame(frame);
}

#define MF_FUNCTION disposeIcon__Q43scn4step4info14HeroStatusIconFv
void HeroStatusIcon::disposeIcon() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 mfBase;
    volatile u32 key;
    u32 i;
    u32 base;
    u32 hash;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x8AFFF902
        opword  0xCC569580
        opword  MF_WORD(0x30)
    after1:
        mflr    r25
        lwz     r30, 0xc(r25)
        lwz     r28, 0x0(r25)
        add     r28, r28, r25
        stw     r28, start
        add     r30, r30, r28
        stw     r30, end
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    if (_518.wasSetParent()) {
        _518.unsetParent();
    }
    hash = 0x811C9DDB;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
    }
    hash += hash << 3;
    if (_1F0.isConstruct()) {
        _1F0.destruct();
    }
    hash ^= hash >> 11;
    hash += hash << 15;
    asm {
        bl      after2
        opword  MF_WORD(0xE4)
        opword  0xEC3879CB
    after2:
        mflr    r27
        lwz     r25, 0x0(r27)
        stw     r25, expected
    }
    hash -= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0x10C)
        after3:
            mflr    r30
            lwz     r22, 0x0(r30)
            stw     r22, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r22, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0x130)
            opword  0x98E17580
            opword  MF_WORD(0x138)
        after4:
            mflr    r22
            lwz     r30, 0x0(r22)
            lwz     r20, 0x8(r22)
            stw     r20, key
            stw     r30, offset
            stw     r22, mfBase
        }
        offset = offset + 0x22;
        key = 0;
        response = offset;
        response = response + mfBase;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        if (_384.isConstruct()) {
            _384.destruct();
        }
    }
}
#undef MF_FUNCTION

void HeroStatusIcon::createIcon(hero::AbilityKind kind) {
    if (kind == hero::ABILITY_KIND_LANDIA) {
        _60.rootPane().setVisibility(false);
        _384.construct(lyt::LayoutContext(T_ABILITY_KIND_TO_PATH[kind], "HeroIcon", mHeap.obj().allocFromHeadAllocator()));
        _384->setParent(_6AC);
        ::info::selectHeroPane(*_384, _6C0);
        _6A8 = &*_384;
    } else {
        _60.rootPane().setVisibility(true);
        const char* path = T_ABILITY_KIND_TO_PATH[kind];
        if (path != 0) {
            _1F0.construct(lyt::LayoutContext(path, "HeroIcon", mHeap.obj().allocFromHeadAllocator()));
            _1F0->setParent(_60.paneByName("HeroIconN"));
        }
        _6A8 = &_60;
    }
    if (_518.wasSetParent()) {
        _518.unsetParent();
    }
    _518.setParent(_6A8->paneByName("HeroPEffectN"));
}

}
}
}
