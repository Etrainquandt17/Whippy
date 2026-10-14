#include "scn/step/boss/kingsdoo/StateJumpCenterAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/kingsdoo/Param.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

StateJumpCenterAttack::StateJumpCenterAttack(Boss* boss) : StateBase(boss), mIsJump(false), mIsFall(false), mStartPos(), mCenter() {
    obj().footState().setAir();
    obj().model().reqScript(14);
    obj().move().resetVelocity();
    Utility::ControlHateOnAction(obj());
    mStartPos = obj().location().pos().getXY();
    mCenter = obj().comp().mainCamera().getCenter();
    bool isRight = mCenter.x - mStartPos.x > 0.0f;
    obj().target().setIsRightDir(isRight);
}

StateJumpCenterAttack::~StateJumpCenterAttack() {}

void StateJumpCenterAttack::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsJump = !mIsJump;
        if (!mIsJump) {
            mIsFall = true;
        } else {
            Utility::TurnHatedHero(obj());
        }
    }
}

void StateJumpCenterAttack::procMove() {
    const Param& param = obj().param().kingsdoo();
    if (mIsFall) {
        obj().move().airDecelFall(param._28, param._2C);
        return;
    }
    if (obj().model().anim().currentG3DAnimIndex() == 12) {
        f32 rate = Math::SinDegF(90.0f * (obj().model().anim().frame() / obj().model().anim().totalFrame()));
        Vector2 pos = Math::LinearInterpolation(mStartPos, mCenter, rate);
        pos.y += param.mJumpCenterHeight * Math::SinDegF(180.0f * rate);
        obj().location().setPos(pos.toVector3());
    } else {
        obj().move().resetVelocity();
    }
}

void StateJumpCenterAttack::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateLanding, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::kingsdoo
