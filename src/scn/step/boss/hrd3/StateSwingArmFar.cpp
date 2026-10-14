#include "scn/step/boss/hrd3/StateSwingArmFar.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/StateWaitFar.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateSwingArmFar::StateSwingArmFar(Boss* boss, u32 frame)
    : StateBase(boss), mCount(0), mFrame(frame), mStartPos(boss->location().pos()), mGoalPos(), mIsMove(false) {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mStartPos.x = param._128 + (custom.landCtrl().getCenterX() + 0.5f * -custom.landCtrl().getWidth());
    mStartPos.y = param._130 + custom.landCtrl().getFloorY();
    mStartPos.z = param._134;
    mGoalPos = mStartPos;
    mGoalPos.x = param._12C + (custom.landCtrl().getCenterX() + 0.5f * custom.landCtrl().getWidth());
    obj().model().reqScript(0x22);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateSwingArmFar::~StateSwingArmFar() {}

void StateSwingArmFar::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsMove = true;
    }
    if (mIsMove && mCount < mFrame) {
        mCount++;
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWaitFar, Boss*>(objPtr());
    }
}

void StateSwingArmFar::procMove() {
    const Param& param = obj().param().hrd3();
    if (mIsMove) {
        f32 depthRate;
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
        f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
        f32 sin = Math::SinDegF(180.0f * t);
        depthRate = 1.0f - (1.0f - sin) * (1.0f - sin);
        Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
        pos.z = Math::LinearInterpolation(mGoalPos.z, param._138, depthRate);
        obj().location().setPos(pos);
    } else {
        obj().location().setPos(Math::LinearInterpolation(obj().location().pos(), mStartPos, 0.05f));
    }
}

void StateSwingArmFar::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
