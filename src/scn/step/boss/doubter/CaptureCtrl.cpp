#define MEM_EXPLICITAUTODELETEARRAY_INLINE

#include "scn/step/boss/doubter/CaptureCtrl.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/CameraTarget.h"
#include "scn/step/hero/Hero.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

namespace {

const hero::CaptureHeroStateKind T_SHOT_HERO_STATE_KIND_TABLE[3] = {
    static_cast<hero::CaptureHeroStateKind>(0x1C),
    static_cast<hero::CaptureHeroStateKind>(0x1D),
    static_cast<hero::CaptureHeroStateKind>(0x1E),
};

}

// TODO: the original keeps the search hit in r31 and the component in r30; this gives the two swapped.
CaptureCtrl::CaptureCtrl(Boss& boss) : mBoss(boss), mAttackers(boss.allocator()), mState(STATE_0), mDamageIndex(0) {
    while (mAttackers.count() != 3) {
        mAttackers.add<Component&, ::ocoll::SearchHit&>(mBoss.comp(), mBoss.objColl().searchHit());
    }
    hel::math::Vector3 pos = mBoss.location().pos();
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].setConstraintPos(pos);
    }
}

void CaptureCtrl::update() {
    switch (mState) {
    case STATE_HOLD:
        updateConstraintPosAtHold();
        break;
    case STATE_HIDE:
        updateConstraintPosAtHide();
        break;
    case STATE_JUGGLING:
        updateConstraintPosAtJuggling();
        checkRelease();
        break;
    case STATE_SHOT_PREPARE:
        updateConstraintPosAtShotprepare();
        checkRelease();
        break;
    }
}

void CaptureCtrl::updateConstraintPosAtHold() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    if (custom.punchCtrlR().isValid()) {
        hel::math::Vector3 pos = custom.punchCtrlR().getPos();
        pos.x += 0.6f * mBoss.target().getSign();
        pos.z += mBoss.target().isRightDir() ? -0.5f : 0.0f;
        for (u32 i = 0; i < mAttackers.count(); i++) {
            mAttackers[i].setConstraintPos(pos);
        }
    }
}

void CaptureCtrl::updateConstraintPosAtHide() {
    hel::math::Vector3 pos = mBoss.location().centerPos();
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].setConstraintPos(pos);
    }
}

void CaptureCtrl::updateConstraintPosAtJuggling() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].setConstraintPos(custom.jugglingCtrl().getFollowNode(i).worldTrans());
    }
}

void CaptureCtrl::updateConstraintPosAtShotprepare() {
    hel::math::Vector3 pos = mBoss.location().pos();
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].setConstraintPos(pos);
    }
}

void CaptureCtrl::checkRelease() {
    const Param& param = mBoss.param().doubter();
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            if (mAttackers[i].getResistPower() >= param._14C) {
                mAttackers[i].setSuccess();
                mAttackers[i].reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x20));
                mAttackers[i].clearCapture();
            }
        }
    }
}

bool CaptureCtrl::checkCapture() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (!mAttackers[i].isCapture()) {
            if (mAttackers[i].chkCaptureHero()) {
                mState = STATE_HOLD;
                const Param& param = mBoss.param().doubter();
                mAttackers[i].reqDamageCritical(param._144);
                mBoss.soundSE().normal().start(0x2A9);
                mBoss.effect().normal().requestP(static_cast<effect::Kind>(0xD8), mAttackers[i].heroObj()->location().centerPos());
                mAttackers[i].reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x1A));
                return true;
            }
        }
    }
    return false;
}

bool CaptureCtrl::isCapture() const {
    if (mState == STATE_0) {
        return false;
    }
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            return true;
        }
    }
    return false;
}

bool CaptureCtrl::isCaptureJuggling() const {
    switch (mState) {
    case STATE_HIDE:
    case STATE_JUGGLING:
    case STATE_SHOT_PREPARE:
        return isCapture();
    }
    return false;
}

u32 CaptureCtrl::getCaptureNum() const {
    u32 num = 0;
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            num++;
        }
    }
    return num;
}

void CaptureCtrl::clearCapture() {
    mState = STATE_0;
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].clearCapture();
    }
}

void CaptureCtrl::juggling() {
    if (isCapture()) {
        mState = STATE_JUGGLING;
        mDamageIndex = 0;
        mBoss.soundSE().normal().start(0x330);
        setIsRightDir();
        for (u32 i = 0; i < mAttackers.count(); i++) {
            if (mAttackers[i].isCapture()) {
                mAttackers[i].reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x1B));
            }
        }
    }
}

void CaptureCtrl::shotPrepare() {
    if (isCapture()) {
        mState = STATE_SHOT_PREPARE;
        for (u32 i = 0; i < mAttackers.count(); i++) {
            if (mAttackers[i].isCapture()) {
                mAttackers[i].reqChangeState(T_SHOT_HERO_STATE_KIND_TABLE[i]);
            }
        }
    }
}

void CaptureCtrl::shot() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            mAttackers[i].reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x1F));
            mAttackers[i].clearCapture();
            break;
        }
    }
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            return;
        }
    }
    mState = STATE_0;
}

void CaptureCtrl::release() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            mAttackers[i].reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x20));
        }
    }
    clearCapture();
}

void CaptureCtrl::setDamage(u32 damage) {
    if (mAttackers[mDamageIndex].isCapture()) {
        mAttackers[mDamageIndex].reqDamageSerious(damage);
        mBoss.soundSE().normal().start(0x2A9);
    }
    if (++mDamageIndex >= 3) {
        mDamageIndex = 0;
    }
}

void CaptureCtrl::hide() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            mState = STATE_HIDE;
            mAttackers[i].heroObj()->setVisibility(false);
            mBoss.effect().normal().requestPD(static_cast<effect::Kind>(0x121), mAttackers[i].heroObj()->location().centerPos(),
                                              mBoss.target().getDirection3());
            mAttackers[i].heroObj()->cameraTarget().setZeroIntpRate();
        }
    }
}

void CaptureCtrl::setIsRightDir() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            mAttackers[i].heroObj()->target().setIsRightDir(mBoss.target().isRightDir());
        }
    }
}

}}}}  // namespace scn::step::boss::doubter
