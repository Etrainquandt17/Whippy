#include "scn/subgame/gunshoot/enemy/DamageAnimator.h"

#include "metafortress.h"
#include "scn/subgame/gunshoot/chara/StageConstant.h"
#include "scn/subgame/gunshoot/enemy/PlayListSetController.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

namespace {

const char* tParamName(int stage) {
    const char* names[3] = {
        "subgame/gunshoot/robot03/Robot03",
        "subgame/gunshoot/robot02/Robot02",
        "subgame/gunshoot/robot01/Robot01",
    };
    return names[stage];
}

}

#define MF_FUNCTION __ct__Q53scn7subgame8gunshoot5enemy14DamageAnimatorFRCQ53scn7subgame8gunshoot5chara13StageConstantQ53scn7subgame8gunshoot5enemy14AnimatorTarget
DamageAnimator::DamageAnimator(const chara::StageConstant& stageConstant, AnimatorTarget target)
    : _0(4)
    , mAnimParam(tParamName(stageConstant._34), 0)
    , mTarget(target)
    , mHitAttribute(static_cast<HitAttribute>(15))
    , _D30()
    , mIsStun(false)
    , mIsClimaxEx(false)
    , mCounter(6)
    , mPlayListSet(0) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    u32 i;
    u32 limit;
    u32 hash;
    u32 last;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0xC4)
        opword  MF_WORD(0xC8)
        opword  0x10A3B090
        opword  0xB40C2393
    after1:
        mflr    r17
        lwz     r26, 0x0(r17)
        lwz     r21, 0x4(r17)
        add     r26, r26, r17
        add     r21, r21, r26
        stw     r26, start
        stw     r21, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x10C)
        opword  0xEE6F3EE4
    after2:
        mflr    r23
        lwz     r26, 0x0(r23)
        stw     r26, expected
    }
    for (; i != limit; i += 2) {
        hash *= 37;
        hash += *(u16*)(last - 1 - i);
    }
    limit = hash >> 10;
    hash ^= limit;
    limit = hash << 20;
    hash ^= limit;
    limit = expected;
    if (hash == limit) {
        mCounter.setEnd();
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x170)
        after3:
            mflr    r14
            lwz     r28, 0x0(r14)
            stw     r28, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r28, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0x194)
            opword  MF_WORD(0x198)
        after4:
            mflr    r18
            stw     r18, base
            lwz     r30, 0x0(r18)
            stw     r30, key
            lwz     r28, 0x4(r18)
            stw     r28, offset
        }
        key = key ^ 0x82;
        response = key + offset;
        response = response + base;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    }
}
#undef MF_FUNCTION

DamageAnimator::~DamageAnimator() {
}

#define MF_FUNCTION initialize__Q53scn7subgame8gunshoot5enemy14DamageAnimatorFQ53scn7subgame8gunshoot5enemy12HitAttribute
void DamageAnimator::initialize(HitAttribute attribute) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 key;
    volatile u32 response;
    volatile u32 offset;
    common::view::ModelAccessor* model;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    hash = 0x811C9E53;
    _0 = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
        opword  0x8877D700
    after1:
        mflr    r23
        lwz     r24, 0x0(r23)
        lwz     r16, 0x4(r23)
        add     r24, r24, r23
        add     r16, r16, r24
        stw     r24, start
        stw     r16, end
    }
    limit = end - start + 1;
    first = start;
    mHitAttribute = attribute;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001D1;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0x31073E54
    after2:
        mflr    r22
        lwz     r30, 0x0(r22)
        stw     r30, expected
    }
    model = mTarget._0;
    _D30 = model->setAnim(0, mAnimParam.getDamageAnimName(mHitAttribute));
    hash += hash << 13;
    hash ^= hash >> 7;
    _D30.setFrameToHead();
    hash += hash << 3;
    hash ^= hash >> 17;
    model = &mTarget._4.ref();
    g3d::ModelAnimAccessor anim = model->setAnim(0, mAnimParam.getDamageAnimName(mHitAttribute));
    hash += hash << 5;
    limit = expected & ~hash;
    hash = limit | (hash & ~expected);
    hash |= hash << 1;
    if (hash == 0) {
        anim.setFrameToHead();
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x188)
        after3:
            mflr    r17
            lwz     r30, 0x0(r17)
            stw     r30, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r30, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r30
            bl      after4
            opword  MF_WORD(0x1AC)
            opword  MF_WORD(0x1B0)
        after4:
            mflr    r22
            lwz     r28, 0x4(r22)
            stw     r28, key
            lwz     r28, 0x0(r22)
            stw     r22, base
            stw     r28, offset
        }
        offset = offset + 0x1D;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    }
}
#undef MF_FUNCTION

void DamageAnimator::initializeForStun() {
    _0 = 0;
    common::view::ModelAccessor* model = mTarget._0;
    _D30 = model->setAnim(0, mAnimParam.getStunDamageModelAnimName());
    _D30.setFrameToHead();
    model = &mTarget._4.ref();
    g3d::ModelAnimAccessor anim = model->setAnim(0, mAnimParam.getStunDamageModelAnimName());
    anim.setFrameToHead();
    model = &mTarget._8.ref();
    g3d::ModelAnimAccessor motion = model->setAnim(mAnimParam.getStunDamageMotionAnimName());
    motion.setFrameToHead();
}

void DamageAnimator::initializeForClimaxEx() {
    _0 = 0;
    common::view::ModelAccessor* model = mTarget._0;
    _D30 = model->setAnim(0, mAnimParam.getClimaxExDamageModelAnimName());
    _D30.setFrameToHead();
    model = &mTarget._4.ref();
    g3d::ModelAnimAccessor anim = model->setAnim(0, mAnimParam.getClimaxExDamageModelAnimName());
    anim.setFrameToHead();
}

void DamageAnimator::initPlayListSet(PlayListSetController& playListSet) {
    mPlayListSet = &playListSet;
}

void DamageAnimator::resume(bool damage) {
    if (damage) {
        startDamage();
    } else {
        _0 = 1;
        mCounter.reset();
    }
}

void DamageAnimator::resumeForStun() {
    mIsStun = true;
    startDamageForStun();
}

void DamageAnimator::resumeForClimaxEx() {
    mIsClimaxEx = true;
    startDamageForClimaxEx();
}

void DamageAnimator::updateMain() {
    if (_0 == 4) {
        return;
    }
    switch (_0) {
    case 1:
        if (mCounter.isEnd()) {
            if (mIsStun) {
                startDamageForStun();
            } else if (mIsClimaxEx) {
                startDamageForClimaxEx();
            } else {
                startDamage();
            }
        } else {
            mCounter.advance();
        }
        break;
    case 2:
        if (_D30.isAnimEnd()) {
            _0 = 3;
        }
        break;
    }
}

bool DamageAnimator::isEnd() const {
    return _0 == 3;
}

#define MF_FUNCTION startDamage__Q53scn7subgame8gunshoot5enemy14DamageAnimatorFv
void DamageAnimator::startDamage() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 base;
    common::view::ModelAccessor* model;
    u32 i;
    u32 last;
    u32 limit;

    hash = 0;
    _0 = 2;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
    after1:
        mflr    r26
        lwz     r19, 0x0(r26)
        lwz     r30, 0x4(r26)
        add     r30, r19, r30
        stw     r19, start
        stw     r30, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    model = mTarget._0;
    _D30 = model->setAnim(0, mAnimParam.getDamageAnimName(mHitAttribute));
    base = last - 1;
    for (; i != limit; i += 2) {
        hash *= 107;
        hash += *(u16*)(base - i);
    }
    _D30.start(false);
    model = &mTarget._4.ref();
    g3d::ModelAnimAccessor anim = model->setAnim(0, mAnimParam.getDamageAnimName(mHitAttribute));
    asm {
        bl      after2
        opword  MF_WORD(0xFC)
        opword  0x39A95A0A
    after2:
        mflr    r22
        lwz     r18, 0x0(r22)
        stw     r18, expected
    }
    anim.start(expected != hash);
    startPlayListIfNecessary(mAnimParam.getDamagePlayListIndex());
}
#undef MF_FUNCTION

void DamageAnimator::startDamageForStun() {
    _0 = 2;
    common::view::ModelAccessor* model = mTarget._0;
    _D30 = model->setAnim(0, mAnimParam.getStunDamageModelAnimName());
    _D30.start(false);
    model = &mTarget._4.ref();
    g3d::ModelAnimAccessor anim = model->setAnim(0, mAnimParam.getStunDamageModelAnimName());
    anim.start(false);
    model = &mTarget._8.ref();
    g3d::ModelAnimAccessor motion = model->setAnim(mAnimParam.getStunDamageMotionAnimName());
    motion.start(false);
}

void DamageAnimator::startDamageForClimaxEx() {
    _0 = 2;
    common::view::ModelAccessor* model = mTarget._0;
    _D30 = model->setAnim(0, mAnimParam.getClimaxExDamageModelAnimName());
    _D30.start(false);
    model = &mTarget._4.ref();
    g3d::ModelAnimAccessor anim = model->setAnim(0, mAnimParam.getClimaxExDamageModelAnimName());
    anim.start(false);
}

void DamageAnimator::startPlayListIfNecessary(int index) {
    if (mPlayListSet != 0) {
        if (mPlayListSet->isStarting()) {
            mPlayListSet->end();
        }
        if (index != -1) {
            mPlayListSet->start(index);
        }
    }
}

}
}
}
}
