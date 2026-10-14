#include "scn/step/boss/bonkers/StateJumpBig.h"

#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

StateJumpBig::StateJumpBig(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mDistance(0.0f) {
    const Param& param = obj().param().bonkers();
    obj().footState().setAir();
    obj().model().reqScript(10);
    Utility::ControlHateOnAction(obj());
    mStartPos = obj().location().pos().getXY();
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    mDistance = heroPos.x - mStartPos.x;
    if (Math::Abs(mDistance) > param.mJumpBigDistanceMax) {
        mDistance = param.mJumpBigDistanceMax * (mDistance < 0.0f ? -1 : 1);
    }
    obj().target().setIsRightDir(mDistance > 0.0f);
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AC));
}

StateJumpBig::~StateJumpBig() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StateJumpBig::procAnim() {
    const Param& param = obj().param().bonkers();
    if (mCount < param.mJumpBigTime) {
        mCount++;
        return;
    }
    Vector2 pos = param.mJumpBigStarPos;
    Vector2 speed = param.mJumpBigStarSpeed;
    Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
    obj().stateChanger().setNextState<common::StateLanding, Boss*>(objPtr());
}

void StateJumpBig::procMove() {
    const Param& param = obj().param().bonkers();
    Vector2 pos = mStartPos;
    f32 rate = static_cast<f32>(mCount) / static_cast<f32>(param.mJumpBigTime);
    pos.x += mDistance * rate;
    pos.y += param.mJumpBigHeight * Math::SinDegF(180.0f * rate);
    obj().location().setPos(pos.toVector3());
}

void StateJumpBig::procFixPos() {}

}}}}  // namespace scn::step::boss::bonkers
