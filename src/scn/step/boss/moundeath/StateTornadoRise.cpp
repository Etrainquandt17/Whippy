#include "scn/step/boss/moundeath/StateTornadoRise.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/StateTornadoChase.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StateTornadoRise::StateTornadoRise(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    const Param& param = obj().param().moundeath();
    obj().footState().setAir();
    obj().model().reqScript(0x1A);
    Utility::ControlHateOnAction(obj());
    obj().move().resetVelocity();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AC));
    obj().soundSE().normal().start(0x58F);
    mStartPos = obj().location().pos().getXY();
    mGoalPos = mStartPos;
    mGoalPos.y += param._144;
}

StateTornadoRise::~StateTornadoRise() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StateTornadoRise::procAnim() {
    const Param& param = obj().param().moundeath();
    if (mCount < param._140) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateTornadoChase, Boss*>(objPtr());
    }
}

void StateTornadoRise::procMove() {
    const Param& param = obj().param().moundeath();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._140);
    f32 rate = 1.0f - Math::CosDegF(90.0f * t);
    obj().location().setPos(Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateTornadoRise::procFixPos() {}

}}}}  // namespace scn::step::boss::moundeath
