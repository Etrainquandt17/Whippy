#include "scn/step/boss/landia/StateMoveTwinBreathContinuity.h"

#include "gobj/Anim.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateMoveTwinBreathContinuity::StateMoveTwinBreathContinuity(Boss* boss, Config config)
    : StateBase(boss), mCount(0), mStartPos(), mGoalPos(), mConfig(config), mIsWaitAnim(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mConfig._C) {
        obj().model().reqScript(23);
        mIsWaitAnim = true;
    } else {
        obj().model().reqScript(24);
        obj().model().anim().setFrameRate(mConfig._0);
    }
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_4);
    obj().move().resetVelocity();
    mStartPos = custom.waftCtrl().getRefPos().getXY();
    mGoalPos = obj().comp().mainCamera().getCenter() + mConfig._4;
}

StateMoveTwinBreathContinuity::~StateMoveTwinBreathContinuity() {}

void StateMoveTwinBreathContinuity::procAnim() {
    if (mIsWaitAnim && obj().model().anim().currentG3DAnimIndex() != 1) {
        mIsWaitAnim = false;
        obj().model().anim().setFrameRate(mConfig._0);
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateMoveTwinBreathContinuity::procMove() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().anim().currentG3DAnimIndex() != 1) {
        f32 t = obj().model().anim().frame() / static_cast<f32>(obj().model().anim().totalFrame());
        f32 rate = hel::math::Math::SinDegF(90.0f * t);
        hel::math::Vector2 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate);
        pos.y += param.mTwinBreathMoveSwing * hel::math::Math::SinDegF(180.0f * rate);
        custom.waftCtrl().setRefPos(pos.toVector3());
    }
}

void StateMoveTwinBreathContinuity::procFixPos() {}

}
}
}
}
