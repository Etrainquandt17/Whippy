#include "scn/step/boss/landia/StateTailStart.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/StateWait.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateTailStart::StateTailStart(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(21);
    custom.waftCtrl().setWaveWidthZero();
    obj().move().resetVelocity();
    hel::math::Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    if (obj().location().pos().x < heroPos.x) {
        obj().target().setIsRightDir(true);
    } else {
        obj().target().setIsRightDir(false);
    }
    mStartPos = custom.waftCtrl().getRefPos().getXY();
    mGoalPos.x = heroPos.x - param.mTailStartDistance * obj().target().getSign();
    mGoalPos.y = param.mTailStartHeight + obj().basePos().y;
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateTailStart::~StateTailStart() {}

void StateTailStart::procAnim() {
    const Param& param = obj().param().landia();
    if (mCount < param.mTailStartFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateTailStart::procMove() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mTailStartFrame);
    f32 rate = hel::math::Math::SinDegF(90.0f * t);
    custom.waftCtrl().setRefPos(hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateTailStart::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
