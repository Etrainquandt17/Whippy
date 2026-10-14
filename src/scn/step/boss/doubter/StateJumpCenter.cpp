#include "scn/step/boss/doubter/StateJumpCenter.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/StateLanding.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateJumpCenter::StateJumpCenter(Boss* boss, f32 height, u32 frame)
    : StateBase(boss), mHeight(height), mFrame(frame), mCount(0), mStartPos(), mGoalPos() {
    obj().footState().setAir();
    obj().model().reqScript(10);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().move().resetVelocity();
    mStartPos = obj().location().pos();
    mGoalPos = obj().basePos().toVector3();
    mGoalPos.x -= 5.0f;
}

StateJumpCenter::~StateJumpCenter() {}

void StateJumpCenter::procAnim() {
    mCount++;
    Utility::TurnHatedHero(obj());
    if (mCount == mFrame) {
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
        obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
    }
}

void StateJumpCenter::procMove() {
    f32 t = static_cast<f32>(mCount + 1) / static_cast<f32>(mFrame);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    f32 fall = 1.0f - Math::SinDegF(180.0f * t);
    fall *= fall;
    f32 rate = 1.0f - fall;
    pos.y += rate * mHeight;
    obj().location().setPos(pos);
}

void StateJumpCenter::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
