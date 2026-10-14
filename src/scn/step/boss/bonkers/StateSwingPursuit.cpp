#include "scn/step/boss/bonkers/StateSwingPursuit.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/bonkers/Custom.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/bonkers/StateSwingEnd.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

namespace {

struct t_Words {
    u32 words[3];
};

// TODO: a stand-in. The original copies the difference word by word, as a vector without a declared copy
// constructor is copied into a named local or a value parameter of an inline function.
inline f32 t_SquareDistance(const Vector3& a, const Vector3& b) {
    t_Words copy = *reinterpret_cast<const t_Words*>(&(a - b));
    return reinterpret_cast<const Vector3&>(copy).squareLength();
}

}

StateSwingPursuit::StateSwingPursuit(Boss* boss) : StateBase(boss), mIsMove(false), mTurnWait(0), mCount(0), mIsRight(false) {
    obj().footState().setGround();
    obj().model().reqScript(11);
    obj().move().resetVelocity();
    Utility::ControlHateOnAction(obj());
}

StateSwingPursuit::~StateSwingPursuit() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollDefault();
}

void StateSwingPursuit::procAnim() {
    const Param& param = obj().param().bonkers();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount < param.mSwingPursuitTime) {
        if (mIsMove) {
            mCount++;
        }
    } else {
        obj().stateChanger().setNextState<StateSwingEnd, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        mIsMove = true;
    }
    if (obj().scriptTrigger().get(1)) {
        obj().guard().setType(GUARD_TYPE_6);
        custom.setBodyCollSwing();
    }
}

void StateSwingPursuit::procMove() {
    const Param& param = obj().param().bonkers();
    if (mTurnWait != 0) {
        mTurnWait--;
    }
    if (mIsMove) {
        if (mTurnWait == 0) {
            Vector3 heroPos = Utility::GetHatedHeroPos(obj());
            if (t_SquareDistance(obj().location().pos(), heroPos) > param.mSwingPursuitTurnDistance) {
                mIsRight = heroPos.x > obj().location().pos().x;
            }
            obj().move().groundAccel(mIsRight, param.mSwingPursuitAccel);
        } else {
            obj().move().groundDecel(param.mSwingPursuitDecel);
        }
    } else {
        obj().move().groundDecel(param._24);
    }
}

void StateSwingPursuit::procFixPos() {
    if (common::StateFall::TryToChangeState(objPtr())) {
        return;
    }
    if (!mIsMove) {
        return;
    }
    const Param& param = obj().param().bonkers();
    chara::MapCollResult result = obj().mapColl().result();
    if (mCount <= 20) {
        return;
    }
    if (result._2 || obj().worldCage().isCorrected()) {
        mTurnWait = param.mSwingPursuitTurnWait;
        f32 sign = obj().move().velocity().x > 0.0f ? 1.0f : -1.0f;
        Vector2 offset(param.mSwingPursuitEffectOffset.x * sign, param.mSwingPursuitEffectOffset.y);
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xD8), obj().location().pos() + offset.toVector3());
        Vector3 velocity = obj().move().velocity();
        velocity.x *= -param.mSwingPursuitReboundRate;
        obj().move().setVelocity(velocity);
    }
}

}}}}  // namespace scn::step::boss::bonkers
