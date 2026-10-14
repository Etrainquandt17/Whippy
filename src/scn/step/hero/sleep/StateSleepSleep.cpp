#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE
#include "scn/step/hero/sleep/StateSleepSleep.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Model.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "nw4r/math/math_triangular.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/AdditionalMove.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ShakeCharge.h"
#include "scn/step/hero/SleepParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace sleep {

namespace {

const SleepParam& param(Hero& hero) {
    return hero.param().sleep();
}

}

StateSleepSleep::StateSleepSleep(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mShakeAngle(-0.7853982f)
    , mShrinkSpeed(0.0f)
    , mScale(1.0f)
    , mSubState(0)
    , mWeapon() {
    initShakeCharge();
    obj().model().script().start(0xE3);
    obj().piggyback().setEnableReceive(true);
    obj().additionalMove().setForbidChangeState(true);
}

StateSleepSleep::~StateSleepSleep() {
    obj().effect()._80.release();
    if (mWeapon.isAlive()) {
        mWeapon->dead();
    }
}

void StateSleepSleep::procAnim() {
    if (Utility::ChkLogoutForce(obj())) {
        return;
    }
    mFrame++;
    if (obj().water().isInWater()) {
        obj().abilityManager().discardAbility(false);
        Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    switch (mSubState) {
    case 0:
        procAnimNormal();
        break;
    case 1:
        procAnimSnotBubble();
        break;
    case 2:
        procAnimWaitShrink();
        break;
    case 3:
        procAnimWakeUp();
        break;
    }
}

void StateSleepSleep::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateSleepSleep::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

void StateSleepSleep::clearAbility() {
    obj().abilityManager().clearAbility();
    Utility::ChangeStateWaitOrFall(obj());
}

void StateSleepSleep::procAnimNormal() {
    if (isStartSnotBubble()) {
        changeSubStateSnotBubble();
    } else {
        chkWakeUp();
    }
}

void StateSleepSleep::procAnimSnotBubble() {
    decideWeaponScale();
    updateWeapon(1.3f * shakeScale());
    if (obj().shakeCharge().power() >= param(obj())._1C) {
        wakeUpWithBubbleBurst();
    } else if (mFrame >= param(obj())._2C - 10) {
        changeSubStateWaitShrink();
    }
}

void StateSleepSleep::procAnimWaitShrink() {
    mScale -= mShrinkSpeed;
    if (mScale < 0.01f) {
        mScale = 0.01f;
    }
    updateWeapon(1.3f * mScale);
    chkWakeUp();
}

void StateSleepSleep::procAnimWakeUp() {
    if (obj().model().isAllEnd()) {
        clearAbility();
    }
}

void StateSleepSleep::changeSubStateSnotBubble() {
    mSubState = 1;
    obj().effect()._58.release();
    obj().shakeCharge().reset();
    createWeapon();
}

void StateSleepSleep::changeSubStateWaitShrink() {
    mShrinkSpeed = mScale / 15.0f;
    mSubState = 2;
}

void StateSleepSleep::wakeUp() {
    mSubState = 3;
    if (mWeapon.isAlive()) {
        mWeapon->dead();
    }
    obj().effect()._58.release();
    obj().effect()._80.release();
    obj().model().script().start(0xE5);
}

void StateSleepSleep::wakeUpWithBubbleBurst() {
    mSubState = 3;
    if (mWeapon.isAlive()) {
        mWeapon->dead();
    }
    obj().model().script().start(0xE4);
}

void StateSleepSleep::decideWeaponScale() {
    mScale = static_cast<f32>(obj().shakeCharge().power()) / 500.0f;
    mScale = Math::LimitMinMax(mScale, param(obj())._4, param(obj())._0);
}

f32 StateSleepSleep::shakeScale() {
    const SleepParam& p = obj().param().sleep();
    f32 speed = mScale / 3.0f;
    speed = speed * (speed * speed);
    speed = Math::Max(speed, p._8);
    mShakeAngle += speed;
    if (mShakeAngle > 3.1415927f) {
        mShakeAngle -= 6.2831855f;
    }
    mScale += (p._C - mScale) / p._10 * nw4r::math::SinRad(mShakeAngle);
    return mScale;
}

void StateSleepSleep::updateWeapon(f32 scale) {
    if (mWeapon.isAlive()) {
        Vector3 s(scale, scale, scale);
        mWeapon->model().model().nodes().at(0).localMtx().setScale(s);
        Vector3 pos = static_cast<const Hero&>(obj()).location().pos();
        mWeapon->location().setPos(pos);
    }
}

void StateSleepSleep::createWeapon() {
    Vector3 heroPos = static_cast<const Hero&>(obj()).location().pos();
    Vector2 dir(heroPos.x, heroPos.y);
    Vector2 pos = dir;
    pos.y += obj().param().sleep()._30;
    Vector2 zero(0.0f, 0.0f);
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0x12);
    desc.mVariation = 0;
    desc.mFlag = static_cast<ostop::Flag>(1);
    desc.mPos = pos;
    desc._14 = dir;
    desc._1c = zero;
    desc.mOwner = &obj().objColl().objColl().owner();
    mWeapon = obj().comp().weaponManager().request(desc);
    if (mWeapon.isAlive()) {
        mWeapon->target().setIsRightDir(obj().target().isRightDir());
    }
}

bool StateSleepSleep::isStartSnotBubble() {
    bool result = false;
    if (mFrame > param(obj())._24 && obj().shakeCharge().power() >= param(obj())._28) {
        result = true;
    }
    return result;
}

void StateSleepSleep::chkWakeUp() {
    if (mFrame > param(obj())._2C) {
        wakeUp();
    }
}

void StateSleepSleep::initShakeCharge() {
    obj().shakeCharge().setEnv(param(obj())._14, param(obj())._18, param(obj())._1C, param(obj())._20);
    obj().shakeCharge().reset();
}

}}}}  // namespace scn::step::hero::sleep
