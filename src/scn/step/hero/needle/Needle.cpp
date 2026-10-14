#include "scn/step/hero/needle/Needle.h"

#include "g3d/ModelAccessor.h"
#include "g3d/ResFileRepository.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "scn/step/hero/needle/StateAttack.h"
#include "scn/step/hero/needle/StateAttackUp.h"
#include "scn/step/hero/needle/StateDash.h"

using g3d::ModelAccessor;
using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace needle {

namespace {

// TODO: the part of hero::Model at 0xC, of which only this virtual function is known.
class ModelHolder {
public:
    virtual void _8();
    virtual ModelAccessor model();
};

inline ModelHolder& t_modelHolder(Model& model) {
    return *reinterpret_cast<ModelHolder*>(reinterpret_cast<u8*>(&model) + 0xC);
}

}

Needle::Needle(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Needle::~Needle() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(6);
    }
}

void Needle::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/needle/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(6, motion);
    mHero.model().hat().set(modeldesc::Needle::HatPath(), modeldesc::Needle::HatModel());
    mHero.model().hat().setAnim(modeldesc::Needle::HatPath(), modeldesc::Needle::HatAnim());
    resetHatVisibility();
    mHero.model().body().set(modeldesc::Needle::NeedleBodyPath(), modeldesc::Needle::NeedleBodyModel());
    resetNeedleBodyVisibility();
    mIsSetup = true;
}

#define MF_FUNCTION tryToChangeState__Q53scn4step4hero6needle6NeedleFv
bool Needle::tryToChangeState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 mfBase;
    u32 size;
    u32 i;
    u32 base;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x454865F8
    after1:
        mflr    r24
        lwz     r30, 0x0(r24)
        stw     r30, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0x40383681
        opword  0xE4260180
        opword  MF_WORD(0x48)
        opword  0x5EF09C09
        opword  0x28970080
    after2:
        mflr    r15
        lwz     r23, 0x0(r15)
        lwz     r22, 0xc(r15)
        add     r23, r23, r15
        add     r22, r22, r23
        stw     r23, start
        stw     r22, end
    }
    base = start;
    size = end - base;
    hash = 0xC5;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash = (hash & ~expected) | (expected & ~hash);
    hash = __cntlzw(hash);
    base = hash >> 5;
    hash = base >> 7;
    hash = base - hash;
    if (hash == 0) {
        asm {
            bl      after3
            opword  0x54C62A80
            opword  0xF491950A
            opword  0xE3868207
            opword  MF_WORD(0x104)
        after3:
            mflr    r20
            lwz     r15, 0xc(r20)
            stw     r15, -0x4(r1)
            stw     r20, 0x0(r1)
            stw     r15, -0x4(r1)
            stw     r20, -0x8(r1)
            mtlr    r15
            bl      after4
            opword  MF_WORD(0x128)
            opword  MF_WORD(0x12C)
        after4:
            mflr    r18
            lwz     r22, 0x4(r18)
            stw     r22, key
            lwz     r22, 0x0(r18)
            stw     r18, mfBase
            stw     r22, offset
        }
        offset = offset + 0x45;
        response = offset + key;
        response = response + mfBase;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    } else {
        if (mHero.water().isInWater()) {
            return false;
        }
        if (mHero.stateChecker().isFloat()) {
            return false;
        }
        if (StateAttackUp::TryToChangeState(&mHero) || StateDash::TryToChangeState(&mHero) || StateAttack::TryToChangeState(&mHero)) {
            return true;
        }
        return false;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION onStateEndCleanUp__Q53scn4step4hero6needle6NeedleFv
void Needle::onStateEndCleanUp() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 response;
    volatile u32 mfBase;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x73D3E542
    after1:
        mflr    r24
        lwz     r29, 0x0(r24)
        stw     r29, expected
        bl      after2
        opword  MF_WORD(0x40)
        opword  0x20A75580
        opword  MF_WORD(0x48)
    after2:
        mflr    r25
        lwz     r27, 0x8(r25)
        lwz     r29, 0x0(r25)
        stw     r29, end
        stw     r27, start
    }
    t_modelHolder(mHero.model()).model().setVisibility(true);
    last = end;
    word = start;
    for (;;) {
        if (word == last) {
            break;
        }
        hash *= 107;
        hash += *(u16*)word;
        word += 2;
    }
    hash += hash << 3;
    resetHatVisibility();
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash == expected) {
        resetNeedleBodyVisibility();
    } else {
        asm {
            bl      after3
            opword  0x014ECA06
            opword  0x14AA5780
            opword  MF_WORD(0x100)
        after3:
            mflr    r26
            lwz     r29, 0x8(r26)
            stw     r29, -0x4(r1)
            stw     r26, 0x0(r1)
            stw     r29, -0x4(r1)
            stw     r26, -0x8(r1)
            mtlr    r29
            bl      after4
            opword  MF_WORD(0x124)
            opword  0x50A9C991
            opword  MF_WORD(0x12C)
        after4:
            mflr    r24
            lwz     r21, 0x8(r24)
            stw     r21, key
            lwz     r21, 0x0(r24)
            stw     r24, mfBase
            stw     r21, offset
        }
        offset = offset ^ 0x62;
        response = offset ^ key;
        response = response + mfBase;
        asm {
            lwz     r20, response
            mtlr    r20
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION resetHatVisibility__Q53scn4step4hero6needle6NeedleFv
void Needle::resetHatVisibility() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 mfBase;
    volatile u32 response;
    u32 t;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xD058DD92
        opword  MF_WORD(0x2C)
        opword  0xE85A3A91
    after1:
        mflr    r22
        lwz     r19, 0x8(r22)
        lwz     r15, 0x0(r22)
        add     r19, r15, r19
        stw     r19, end
        stw     r15, start
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    hash = 0;
    while (i != limit) {
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x98)
        opword  0x83EC1826
    after2:
        mflr    r19
        lwz     r30, 0x0(r19)
        stw     r30, expected
    }
    hash = expected ^ hash;
    t = hash >> 3;
    hash = hash - t;
    if (hash == 0) {
        if (mHero.model().hat().isValid()) {
            mHero.model().hat().setVisibility(true);
            mHero.model().hat().setNodeVisibility(2, true);
            mHero.model().hat().setNodeVisibility(3, false);
            mHero.model().hat().anim().start(0, false);
        }
    } else {
        asm {
            bl      after3
            opword  0xD8265B80
            opword  0x901C8180
            opword  0xD08B380A
            opword  MF_WORD(0x150)
        after3:
            mflr    r15
            lwz     r24, 0xc(r15)
            stw     r24, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r15, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0x174)
            opword  0xD035A780
            opword  MF_WORD(0x17C)
        after4:
            mflr    r14
            lwz     r22, 0x0(r14)
            stw     r14, mfBase
            lwz     r25, 0x8(r14)
            stw     r22, offset
            stw     r25, key
        }
        offset = offset ^ 0x13;
        response = offset + key;
        response = response + mfBase;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION resetNeedleBodyVisibility__Q53scn4step4hero6needle6NeedleFv
void Needle::resetNeedleBodyVisibility() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 tail;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x8D2BE50C
        opword  0xF810B293
    after1:
        mflr    r16
        lwz     r25, 0x0(r16)
        stw     r25, end
        bl      after2
        opword  MF_WORD(0x44)
    after2:
        mflr    r16
        lwz     r25, 0x0(r16)
        stw     r25, start
    }
    word = start;
    tail = end;
    for (;;) {
        if (word == tail) {
            break;
        }
        hash *= 107;
        hash += *(u16*)word;
        word += 2;
    }
    asm {
        bl      after3
        opword  MF_WORD(0x7C)
        opword  0xA2B210BD
    after3:
        mflr    r30
        lwz     r20, 0x0(r30)
        stw     r20, expected
    }
    if (hash - expected == 0) {
        if (!mHero.model()._1668.isValid()) {
            asm {
                b       done
            }
        }
        mHero.model()._1668.setNodeVisibility(2, expected != hash);
    }
done:;
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::hero::needle
