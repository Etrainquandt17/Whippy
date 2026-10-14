#include "scn/step/boss/metalgeneral/StatePatriotZJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "pow.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StatePatriotZJump::StatePatriotZJump(Boss* boss, StatePatriotGenerate::Config config)
    : StateBase(boss), mCount(0), mConfig(config) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0xC);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().mapColl().setValid(false);
    obj().move().resetVelocity();
    mStartPos = obj().location().pos();
    mGoalPos = obj().basePos().toVector3();
    mGoalPos.x += param._30;
    mGoalPos.y += param._1D4;
    mGoalPos.z += param._1D8;
    bool isRight = mGoalPos.x - mStartPos.x > 0.0f;
    obj().target().setIsRightDir(isRight);
    obj().model().rotCtrl().setRotHTarget(param._1E0);
}

StatePatriotZJump::~StatePatriotZJump() {}

void StatePatriotZJump::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (mCount < param._1CC) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StatePatriotGenerate, Boss*, StatePatriotGenerate::Config>(objPtr(), mConfig);
    }
}

void StatePatriotZJump::procMove() {
    const Param& param = obj().param().metalgeneral();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._1CC);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    f32 height = 1.0f - POW2(1.0f - Math::SinDegF(180.0f * t));
    pos.y += param._1DC * height;
    obj().location().setPos(pos);
}

void StatePatriotZJump::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
