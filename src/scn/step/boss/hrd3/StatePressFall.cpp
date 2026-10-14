#include "scn/step/boss/hrd3/StatePressFall.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/StatePressBound.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StatePressFall::StatePressFall(Boss* boss, u32 boundCount)
    : StateBase(boss), mCount(0), mFrame(boss->param().hrd3()._A8), mBoundCount(boundCount),
      mStartPos(boss->location().pos()), mGoalY(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mStartPos.z = 0.0f;
    mGoalY = custom.landCtrl().getFloorY();
    obj().model().reqScript(0x13);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(2));
}

StatePressFall::~StatePressFall() {}

void StatePressFall::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StatePressBound, Boss*, unsigned long>(objPtr(), mBoundCount);
    }
}

void StatePressFall::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = 1.0f - Math::CosDegF(90.0f * t);
    Vector3 pos = mStartPos;
    pos.y = Math::LinearInterpolation(mStartPos.y, mGoalY, rate);
    obj().location().setPos(pos);
}

void StatePressFall::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
