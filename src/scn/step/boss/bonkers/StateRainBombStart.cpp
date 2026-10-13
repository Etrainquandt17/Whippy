#include "scn/step/boss/bonkers/StateRainBombStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

StateRainBombStart::StateRainBombStart(Boss* boss, StateRainBomb::Config config)
    : StateBase(boss), mIsJump(false), mCount(0), mStartPos(), mEndPos(), mConfig(config) {
    const Param& param = obj().param().bonkers();
    obj().footState().setAir();
    obj().model().reqScript(16);
    obj().move().resetVelocity();
    mStartPos = obj().location().pos().getXY();
    mEndPos = obj().comp().mainCamera().getCenter();
    mEndPos.y += param.mRainBombOffsetY;
    bool isRight = mEndPos.x - mStartPos.x > 0.0f;
    obj().target().setIsRightDir(isRight);
}

StateRainBombStart::~StateRainBombStart() {}

void StateRainBombStart::procAnim() {
    const Param& param = obj().param().bonkers();
    if (mCount < param.mRainBombJumpTime) {
        if (mIsJump) {
            mCount++;
        }
    } else {
        obj().stateChanger().setNextState<StateRainBomb, Boss*, StateRainBomb::Config>(objPtr(), mConfig);
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        mIsJump = true;
    }
}

void StateRainBombStart::procMove() {
    const Param& param = obj().param().bonkers();
    if (mIsJump) {
        f32 rate = hel::math::Math::SinDegF(90.0f * (static_cast<f32>(mCount) / static_cast<f32>(param.mRainBombJumpTime)));
        hel::math::Vector2 pos;
        pos.x = hel::math::Math::LinearInterpolation(mStartPos.x, mEndPos.x, rate);
        pos.y = hel::math::Math::LinearInterpolation(mStartPos.y, mEndPos.y, hel::math::Math::SinDegF(90.0f * rate));
        pos.y += param.mRainBombJumpHeight * hel::math::Math::SinDegF(180.0f * rate);
        obj().location().setPos(pos.toVector3());
    }
}

void StateRainBombStart::procFixPos() {}

}}}}  // namespace scn::step::boss::bonkers
