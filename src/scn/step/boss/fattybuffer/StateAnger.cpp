#include "scn/step/boss/fattybuffer/StateAnger.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateSwellWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/info/BossPanel.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateAnger::StateAnger(Boss* boss) : StateBase(boss), mScale(1.0f), mIsScaling(false), mCount(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().invincible().setPermNoFlash();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().model().reqScript(0x22);
    obj().infoBossPanel().transformStart();
    custom.mapCollCtrl().setDefault();
    obj().location().setToCenter(Vector3(0.0f, 3.0f, 0.0f));
}

StateAnger::~StateAnger() {
    obj().infoBossPanel().transformEnd();
}

void StateAnger::procAnim() {
    const Param& param = obj().param().fattybuffer();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        mIsScaling = true;
        custom.setSubAnimEyeAngry();
    }
    if (obj().scriptTrigger().get(1)) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_11);
    }
    if (mIsScaling) {
        if (mCount < param.mAngerScaleTime) {
            mCount++;
        }
        f32 rate = static_cast<f32>(mCount) / static_cast<f32>(param.mAngerScaleTime);
        mScale = Math::LinearInterpolation(param.mScaleDefault, param.mScaleAnger, rate);
        obj().model().setScale(Vector3::ALL_ONE * mScale);
        obj().worldCage().changePadding(1.75f * mScale, 0.0f);
        obj().shadow().changeDiameter(3.0f * mScale);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateSwellWait, Boss*>(objPtr());
    }
}

void StateAnger::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateAnger::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
