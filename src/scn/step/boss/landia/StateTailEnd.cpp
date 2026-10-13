#include "scn/step/boss/landia/StateTailEnd.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/StateWait.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateTailEnd::StateTailEnd(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(10);
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetVelocity();
    obj().model().rotCtrl().setRotHTarget(0.0f);
    mStartPos = custom.waftCtrl().getRefPos();
    mGoalPos = obj().comp().mainCamera().getCenter().toVector3();
}

StateTailEnd::~StateTailEnd() {
    hel::math::Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    if (obj().location().pos().x < heroPos.x) {
        obj().target().setIsRightDir(true);
    } else {
        obj().target().setIsRightDir(false);
    }
}

void StateTailEnd::procAnim() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount < param._22C) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (mCount == param._22C / 2) {
        custom.collisionCtrl().setState(CollisionCtrl::STATE_4);
    }
}

void StateTailEnd::procMove() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._22C);
    hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.y += param._234 * hel::math::Math::SinDegF(180.0f * t);
    f32 swing = hel::math::Math::SinDegF(180.0f * (1.5f * t + t * (-0.5f * t * t)));
    pos.z += swing * param._238;
    f32 rate = 1.0f - (1.0f - hel::math::Math::SinDegF(90.0f * t)) * (1.0f - hel::math::Math::SinDegF(90.0f * t));
    obj().model().rotCtrl().initRotD((1.0f - rate) * (360.0f * obj().target().getSign()));
    custom.waftCtrl().setRefPos(pos);
}

void StateTailEnd::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
