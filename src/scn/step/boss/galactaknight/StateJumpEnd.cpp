#include "scn/step/boss/galactaknight/StateJumpEnd.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateJumpEnd::StateJumpEnd(Boss* boss, ScriptKind kind, f32 distance, u32 frame)
    : StateBase(boss), mFrame(frame), mCount(0), mStartPos(boss->location().pos()), mGoalPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    mGoalPos.x = distance * obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    if (mStartPos.z < -4.0f) {
        obj().worldCage().setIsValid(false);
    }
    obj().model().reqScript(kind);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateJumpEnd::~StateJumpEnd() {
    obj().worldCage().setIsValid(true);
}

void StateJumpEnd::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().soundSE().normal().start(0x114);
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x9F), obj().location().pos());
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateJumpEnd::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 sin = Math::SinDegF(90.0f * t + 90.0f);
    f32 ease = 1.0f - (1.0f - sin) * (1.0f - sin);
    f32 rate = Math::LinearInterpolation(sin, ease, 0.5f);
    Vector3 pos;
    pos.x = Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t);
    pos.y = Math::LinearInterpolation(mGoalPos.y, mStartPos.y, rate);
    pos.z = 0.0f;
    obj().location().setPos(pos);
}

void StateJumpEnd::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
