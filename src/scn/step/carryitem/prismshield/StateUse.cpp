#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/carryitem/prismshield/StateUse.h"

#include "gobj/Location.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/carryitem/prismshield/StateFall.h"
#include "scn/step/carryitem/prismshield/Utility.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/Model.h"

using hel::math::Vector2;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace carryitem {
namespace prismshield {

StateUse::StateUse(CarryItem* carryItem)
    : StateBase(carryItem)
    , mUseAlgorithm(*carryItem)
    , mFlashAngle(0.0f)
    , mIsRightDir(true)
    , mIsRightDirPrev(true)
    , mIsStart(true)
    , mIsReleased(false)
    , mIsGuard(false)
    , mIsGuardPrev(false) {
    Utility::StartFlash(obj());
    obj().model().reqScript(1);
    obj().effect().requestN(static_cast<effect::Kind>(0x351), 0);
    obj().effect().requestN(static_cast<effect::Kind>(0x5AA), 0);
    obj().model().rotCtrl().setRotDTarget(7.0f);
    obj().soundSE().start(0xF3);
    chkAnim();
    setAttack();
}

StateUse::~StateUse() {
    if (!mIsReleased) {
        obj().soundSE().stop();
    }
    obj().objColl().clearAttack();
}

void StateUse::procAnim() {
    obj().incUseCount();
    if (mIsStart && obj().model().isAllEnd()) {
        mIsStart = false;
        obj().model().reqScript(2);
        obj().effect().requestN(static_cast<effect::Kind>(0x350), 0);
    }
    if (obj().useCount() >= obj().param().prismShield()._8) {
        reqReleaseEffect();
        obj().deadWithEffect();
        return;
    }
    if (obj().getUser().wasSet()) {
        mIsRightDir = obj().getUser()->isRightDir();
        if (mIsRightDir) {
            obj().model().rotCtrl().setRotHTarget(80.0f);
        } else {
            obj().model().rotCtrl().setRotHTarget(-80.0f);
        }
        obj().model().rotCtrl().setRotHIntpRate(0.3f);
    }
    mFlashAngle = Utility::UpdateFlash(obj(), mFlashAngle);
    Utility::UpdateFlash(obj());
    chkAnim();
    if (isUpdateAttack()) {
        setAttack();
    }
    mIsRightDirPrev = mIsRightDir;
    mIsGuardPrev = mIsGuard;
}

void StateUse::procMove() {
    mUseAlgorithm.procMove();
}

void StateUse::procConstraint() {
    if (mUseAlgorithm.procConstraint()) {
        obj().soundSE().stop();
        mIsReleased = true;
        // TODO: the original tests the pointer in place here and calls wasSet() elsewhere in the unit.
        if (obj().getUser().operator->() == 0) {
            if (obj().getReleaseType() == RELEASE_TYPE_THROW) {
                obj().soundSE().start(0xFE);
            }
        }
        reqReleaseEffect();
        obj().stateChanger().setNextState<StateFall, CarryItem*>(objPtr());
    }
}

bool StateUse::isUpdateAttack() {
    if (!isSameDir()) {
        return true;
    }
    if (mIsGuard) {
        return true;
    }
    return mIsGuardPrev;
}

bool StateUse::isSameDir() {
    return mIsRightDir == mIsRightDirPrev;
}

void StateUse::chkAnim() {
    if (obj().getUser().wasSet()) {
        ObjRefHandle<hero::Hero> hero =
            obj().comp().heroManager().searchHeroFromObjCollOwnerID(obj().getUser()->getOCOwner().uid());
        if (!hero.isNull()) {
            int index = hero->model().anim().currentG3DAnimIndex();
            bool isGuard = false;
            if (index == 7 && hero->model().anim().frame() > 0.0f) {
                isGuard = true;
            }
            mIsGuard = isGuard;
            return;
        }
    }
    mIsGuard = false;
}

void StateUse::setAttack() {
    const Param& param = obj().param().prismShield();
    f32 sign = mIsRightDir ? 1.0f : -1.0f;
    obj().objColl().clearAttack();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x256));
    obj().objColl().setAttackCenter(0, Vector2::ZERO);
    f32 up = mIsGuard ? 0.5f : 0.0f;
    obj().objColl().addAttack(
        0, param._2C, Vector2(sign * param._30, param._34 + up),
        Vector2(sign * param._38, param._3C + up));
}

void StateUse::reqReleaseEffect() {
    obj().effect().releaseAndVanish();
    Vector2 pos = obj().location().pos().getXY();
    f32 sign = mIsRightDir ? 1.0f : -1.0f;
    const Param& param = obj().param().prismShield();
    pos += Vector2(sign * param._18, param._1C);
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x354), pos.toVector3());
}

}}}}  // namespace scn::step::carryitem::prismshield
