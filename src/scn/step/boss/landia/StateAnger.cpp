#include "scn/step/boss/landia/StateAnger.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/HeadAngleCtrl.h"
#include "scn/step/boss/landia/HowlCtrl.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/StateWait.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/info/BossPanel.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateAnger::StateAnger(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(31);
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().invincible().setPermNoFlash();
    obj().guard().setType(GUARD_TYPE_6);
    obj().infoBossPanel().transformStart();
    custom.headAngleCtrl().toInvalid();
    mStartPos = custom.waftCtrl().getRefPos().getXY();
    mGoalPos = obj().comp().mainCamera().getCenter();
}

StateAnger::~StateAnger() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).headAngleCtrl().toValid();
    obj().infoBossPanel().transformEnd();
}

void StateAnger::procAnim() {
    const Param& param = obj().param().landia();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount < param.mAngerFrame) {
        mCount++;
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        custom.setSubAnimEyeAngry();
        Utility::TurnHatedHero(obj());
    }
    if (obj().scriptTrigger().get(1)) {
        custom.howlCtrl().reqStop();
    }
}

void StateAnger::procMove() {
    const Param& param = obj().param().landia();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mAngerFrame);
    f32 rate = Math::SinDegF(90.0f * t);
    custom.waftCtrl().setRefPos(Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateAnger::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
