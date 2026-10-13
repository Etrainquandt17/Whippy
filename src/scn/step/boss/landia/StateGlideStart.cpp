#include "scn/step/boss/landia/StateGlideStart.h"

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
#include "scn/step/boss/landia/StateGlide.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateGlideStart::StateGlideStart(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(13);
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetVelocity();
    mStartPos = custom.waftCtrl().getRefPos().getXY();
    mGoalPos = obj().comp().mainCamera().getCenter();
    mGoalPos.x += param.mGlideStartOffsetX * obj().target().getSign();
    mGoalPos.y += param.mGlideStartOffsetY;
}

StateGlideStart::~StateGlideStart() {
    obj().model().rotCtrl().initRotD(0.0f);
}

void StateGlideStart::procAnim() {
    const Param& param = obj().param().landia();
    if (mCount < param.mGlideStartFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateGlide, Boss*>(objPtr());
        return;
    }
    f32 sin = hel::math::Math::SinDegF(90.0f * (static_cast<f32>(mCount) / static_cast<f32>(param.mGlideStartFrame)));
    f32 rot = 360.0f * sin * obj().target().getSign();
    obj().model().rotCtrl().initRotD(rot);
}

void StateGlideStart::procMove() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mGlideStartFrame);
    f32 rate = hel::math::Math::SinDegF(90.0f * t);
    hel::math::Vector2 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    pos.y += param.mGlideStartSwing * hel::math::Math::SinDegF(180.0f * rate);
    custom.waftCtrl().setRefPos(pos.toVector3());
}

void StateGlideStart::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
