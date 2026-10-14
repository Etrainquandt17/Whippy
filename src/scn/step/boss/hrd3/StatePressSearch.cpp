#include "scn/step/boss/hrd3/StatePressSearch.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/StatePressFall.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StatePressSearch::StatePressSearch(Boss* boss, u32 frame, u32 boundCount)
    : StateBase(boss), mCount(0), mFrame(frame), mBoundCount(boundCount), mStartX(boss->location().pos().x),
      mGoalPos(boss->location().pos()) {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = Utility::GetHatedHeroPos(obj()).x;
    mGoalPos.x = custom.landCtrl().getAdjustX(mGoalPos.x, param._C);
    mGoalPos.y = param._A0 + custom.landCtrl().getFloorY();
    mGoalPos.z = 0.0f;
    obj().model().reqScript(0x12);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(2));
}

StatePressSearch::~StatePressSearch() {}

void StatePressSearch::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StatePressFall, Boss*, unsigned long>(objPtr(), mBoundCount);
    }
}

void StatePressSearch::procMove() {
    const Param& param = obj().param().hrd3();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
    Vector3 pos = obj().location().pos();
    pos.x = Math::LinearInterpolation(mStartX, mGoalPos.x, rate);
    pos.y = Math::LinearInterpolation(pos.y, mGoalPos.y, param._B4);
    pos.z = mGoalPos.z;
    obj().location().setPos(pos);
}

void StatePressSearch::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
