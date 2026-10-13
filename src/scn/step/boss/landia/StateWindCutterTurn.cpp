#include "scn/step/boss/landia/StateWindCutterTurn.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/StateWindCutter.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateWindCutterTurn::StateWindCutterTurn(Boss* boss) : StateBase(boss), mCount(0), mTurnCount(0), mStartPos(), mGoalPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(10);
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetVelocity();
    mStartPos = custom.waftCtrl().getRefPos();
    mGoalPos = mStartPos;
    mGoalPos.x -= 2.0f * (mStartPos.x - obj().comp().mainCamera().getCenter().x);
}

StateWindCutterTurn::~StateWindCutterTurn() {}

void StateWindCutterTurn::procAnim() {
    const Param& param = obj().param().landia();
    if (mCount < param.mWindCutterTurnWaitFrame) {
        mCount++;
    } else if (mTurnCount < param.mWindCutterTurnFrame) {
        mTurnCount++;
    } else {
        StateWindCutter::Config config;
        config._0 = 4;
        obj().stateChanger().setNextState<StateWindCutter, Boss*, StateWindCutter::Config>(objPtr(), config);
        return;
    }
    if (mTurnCount == static_cast<u32>(0.7f * static_cast<f32>(param.mWindCutterTurnFrame))) {
        obj().target().invert();
    }
}

void StateWindCutterTurn::procMove() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mTurnCount) / static_cast<f32>(param.mWindCutterTurnFrame);
    hel::math::Vector3 pos = hel::math::Vector3::ZERO;
    pos.x = hel::math::Math::LinearInterpolation(mStartPos.x, mGoalPos.x, hel::math::Math::SinDegF(90.0f * t));
    pos.y = hel::math::Math::LinearInterpolation(mStartPos.y, mGoalPos.y, t);
    pos.y += param.mWindCutterTurnSwingY * hel::math::Math::SinDegF(180.0f * t);
    pos.z = hel::math::Math::LinearInterpolation(mStartPos.z, mGoalPos.z, t);
    f32 swing = hel::math::Math::SinDegF(180.0f * (1.5f * t + t * (-0.5f * t * t)));
    pos.z += swing * param.mWindCutterTurnSwingZ;
    f32 sin = hel::math::Math::SinDegF(90.0f * t);
    f32 rot = (1.0f - sin) * (360.0f * obj().target().getSign());
    obj().model().rotCtrl().initRotD(rot);
    custom.waftCtrl().setRefPos(pos);
}

void StateWindCutterTurn::procFixPos() {}

}
}
}
}
