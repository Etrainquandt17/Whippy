#include "scn/step/boss/metalgeneral/StatePatriotJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StatePatriotJump::StatePatriotJump(Boss* boss, StatePatriotGenerate::Config config, bool isFar)
    : StateBase(boss), mCount(0), mConfig(config) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0xB);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().resetVelocity();
    mStartPos = obj().location().pos();
    f32 sign = isFar ? 1.0f : -1.0f;
    mGoalPos = obj().basePos().toVector3();
    mGoalPos.x += param._30;
    if (mStartPos.x < param._30 + obj().basePos().x) {
        mGoalPos.x -= param._1BC * sign;
    } else {
        mGoalPos.x += param._1BC * sign;
    }
    mGoalPos.y += param._1C0;
    mGoalPos.z += param._1C4;
    bool isRight = mGoalPos.x - mStartPos.x > 0.0f;
    obj().target().setIsRightDir(isRight);
}

StatePatriotJump::~StatePatriotJump() {}

void StatePatriotJump::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (mCount < param._1B8) {
        mCount++;
    } else if (obj().model().anim().currentG3DAnimIndex() != 9) {
        obj().model().reqScript(2);
        obj().model().anim().setFrameRate(2.0f);
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StatePatriotGenerate, Boss*, StatePatriotGenerate::Config>(objPtr(), mConfig);
    }
}

void StatePatriotJump::procMove() {
    const Param& param = obj().param().metalgeneral();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._1B8);
    f32 rate = Math::SinDegF(90.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    pos.y += Math::SinDegF(180.0f * t) * param._1C8;
    obj().location().setPos(pos);
}

void StatePatriotJump::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
