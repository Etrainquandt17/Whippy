#include "scn/step/hero/FinalBattleShadow.h"

#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Vector2.h"
#include "metafortress.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/chara/GroundChecker.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/hero/CaptureHeroReceiver.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/sfx/SuperFade.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandleInline.h"

namespace scn {
namespace step {
namespace hero {

namespace {

inline f32 t_min(const f32& a, const f32& b) {
    return a > b ? b : a;
}

}

#define MF_FUNCTION __ct__Q43scn4step4hero17FinalBattleShadowFRQ43scn4step4hero4Hero
FinalBattleShadow::FinalBattleShadow(Hero& hero)
    : mHero(hero), _4(true), _5(true), mEffectLocator(), mEffect(hero.comp(), effect::DRAW_PRIORITY_4), _40(false), _41(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x70)
        opword  0x90325C80
        opword  0x324C780F
        opword  MF_WORD(0x7C)
        opword  0xC88C2980
    after1:
        mflr    r27
        lwz     r23, 0x0(r27)
        lwz     r18, 0xc(r27)
        add     r23, r23, r27
        add     r18, r18, r23
        stw     r23, start
        stw     r18, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    hash = 0xC5;
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    asm {
        bl      after2
        opword  MF_WORD(0xF8)
        opword  0x31C0A3FD
    after2:
        mflr    r29
        lwz     r20, 0x0(r29)
        stw     r20, expected
    }
    if (hash - expected != 0 || Utility::IsFinalBattle(mHero)) {
        createEffectLocator();
    }
}
#undef MF_FUNCTION

FinalBattleShadow::~FinalBattleShadow() {
    killEffectLocator();
}

void FinalBattleShadow::update() {
    if (Utility::IsFinalBattle(mHero)) {
        updateIsValid();
        if (_4) {
            if (mHero.comp().objStopManager().isStopped(static_cast<ostop::Flag>(1))) {
                pause();
            } else {
                unpause();
            }
            if (!mHero.groundChecker().isFloorValid()) {
                killEffectLocator();
                releaseEffect();
            } else {
                if (mEffectLocator.isNull()) {
                    createEffectLocator();
                }
                if (!mEffectLocator.isNull()) {
                    if (mHero.footState().isGround()) {
                        requestEffect();
                    } else {
                        releaseEffect();
                    }
                    const CommonParam& param = mHero.param().common();
                    f32 floorY = mHero.groundChecker().getFloorPos().y;
                    f32 height = mHero.location().pos().y - floorY;
                    f32 range = param._4DC;
                    if (range > 0.0f) {
                        f32 rate = 1.0f - t_min(height / range, 1.0f);
                        f32 scale = rate * (param._4E0 - param._4E4) + param._4E4;
                        mEffectLocator->model().setScale(hel::math::Vector3::ALL_ONE * scale);
                    }
                    mEffectLocator->location().setPos(mHero.groundChecker().getFloorPosVector3());
                    mEffectLocator->model().updateMtx();
                }
            }
        }
    }
}

#define MF_FUNCTION setVisibility__Q43scn4step4hero17FinalBattleShadowFb
void FinalBattleShadow::setVisibility(bool isVisible) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 subtrahend;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 offset;
    FinalBattleShadow* self = this;
    bool visible = isVisible;
    u32 p;
    u32 stop;
    u32 hash;

    asm {
        bl      after1
        opword  0x0CA24B91
        opword  MF_WORD(0x2C)
        opword  0xC8615993
        opword  MF_WORD(0x34)
        opword  0x7E8E750F
    after1:
        mflr    r15
        lwz     r14, 0x4(r15)
        lwz     r29, 0xc(r15)
        stw     r14, start
        stw     r29, end
        bl      after2
        opword  MF_WORD(0x54)
        opword  0x9306810C
    after2:
        mflr    r21
        lwz     r28, 0x0(r21)
        stw     r28, expected
    }
    hash = 0;
    p = start;
    stop = end;
    for (;;) {
        if (p == stop) {
            break;
        }
        hash += *(u16*)p;
        hash += hash << 10;
        hash ^= hash >> 6;
        p += 2;
    }
    if (hash != expected) {
        asm {
            bl      after3
            opword  0x803C5080
            opword  MF_WORD(0xB0)
        after3:
            mflr    r27
            lwz     r23, 0x4(r27)
            stw     r23, -0x4(r1)
            stw     r27, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r27, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0xD4)
            opword  0xE46B1992
            opword  0x30BC3880
            opword  MF_WORD(0xE0)
        after4:
            mflr    r18
            lwz     r15, 0x0(r18)
            lwz     r30, 0xc(r18)
            stw     r30, subtrahend
            stw     r15, offset
            stw     r18, mfBase
        }
        offset = offset - 0xD9;
        response = offset - subtrahend;
        response = response + mfBase;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    } else {
        self->_5 = visible;
    }
}
#undef MF_FUNCTION

void FinalBattleShadow::createEffectLocator() {
    if (!mEffectLocator.isAlive()) {
        mEffectLocator = Utility::CreateEffectLocator(mHero);
        if (mEffectLocator.isAlive()) {
            mEffectLocator->effect().normal().requestN(static_cast<effect::Kind>(8), node());
        }
    }
}

void FinalBattleShadow::killEffectLocator() {
    if (mEffectLocator.isAlive()) {
        mEffectLocator->dead();
        releaseEffect();
    }
}

g3d::NodeAccessor FinalBattleShadow::node() {
    return mEffectLocator->model().model().nodes().at(0);
}

void FinalBattleShadow::requestEffect() {
    if (!mEffectLocator.isNull() && !_40) {
        mEffect.requestN(static_cast<effect::Kind>(9), node());
        mEffect.requestN(static_cast<effect::Kind>(10), node());
        _40 = true;
    }
}

void FinalBattleShadow::releaseEffect() {
    if (_40) {
        mEffect.release();
        _40 = false;
    }
}

void FinalBattleShadow::onObjStopStarted() {
    pause();
}

void FinalBattleShadow::onObjStopFinished() {
    unpause();
}

void FinalBattleShadow::pause() {
    if (!_41) {
        _41 = true;
        mEffect.requestPause();
    }
}

void FinalBattleShadow::unpause() {
    if (_41) {
        _41 = false;
        mEffect.requestUnpause();
    }
}

void FinalBattleShadow::updateIsValid() {
    bool isValid = true;
    if (!_5) {
        isValid = false;
    }
    if (mHero.captureHeroReceiver().isCapture()) {
        isValid = false;
    }
    if (!mHero.isVisible()) {
        isValid = false;
    }
    if (mHero.comp().heroManager().isSuperActionTime() && mHero.comp().superFade().isBack()) {
        isValid = false;
    }
    setIsValid(isValid);
}

void FinalBattleShadow::setIsValid(bool isValid) {
    if (_4 != isValid) {
        _4 = isValid;
        if (!_4) {
            killEffectLocator();
            releaseEffect();
        }
    }
}

}}}  // namespace scn::step::hero
