#include "scn/step/boss/galactaknight/StateStep.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateStep::StateStep(Boss* boss, ScriptKind kind, f32 distance, f32 height, u32 frame)
    : StateBase(boss), mFrame(frame), mCount(0), mStartPos(boss->location().pos()), mGoalPos(), mHeight(height) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = distance * obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    obj().model().reqScript(kind);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateStep::~StateStep() {}

void StateStep::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        if (mHeight > 0.8f) {
            obj().soundSE().normal().start(0x114);
            obj().effect().normal().requestP(static_cast<effect::Kind>(0x9F), obj().location().pos());
        }
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateStep::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.y += Math::SinDegF(180.0f * t) * mHeight;
    obj().location().setPos(pos);
}

void StateStep::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
