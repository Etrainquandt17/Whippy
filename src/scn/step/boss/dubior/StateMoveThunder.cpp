#include "scn/step/boss/dubior/StateMoveThunder.h"

#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/dubior/Custom.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateMoveThunder::StateMoveThunder(Boss* boss) : StateBase(boss), mCount(0), mTime(0), mStartPos(), mTargetPos(), mPhase(0) {
    const Param& param = obj().param().dubior();
    obj().footState().setAir();
    obj().model().reqScript(11);
    mStartPos = obj().location().pos().getXY();
    f32 sign = obj().location().pos().x > obj().comp().mainCamera().getCenter().x ? 1.0f : -1.0f;
    mTargetPos.x = mStartPos.x + sign * param.mMoveThunderDistance;
    mTargetPos.y = mStartPos.y;
    obj().target().setIsRightDir(sign < 0.0f);
    obj().worldCage().setIsValid(false);
    mTime = param.mMoveThunderTime;
}

StateMoveThunder::~StateMoveThunder() {
    obj().worldCage().setIsValid(true);
}

void StateMoveThunder::procAnim() {
    const Param& param = obj().param().dubior();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    switch (mPhase) {
    case 0:
        if (mCount < mTime) {
            mCount++;
        } else {
            mCount = 0;
            mPhase = 1;
            mStartPos = obj().location().pos().getXY();
            Rect rect = obj().comp().mainCamera().getViewRect();
            if (mStartPos.x > obj().comp().mainCamera().getCenter().x) {
                mTargetPos.x = rect._8;
            } else {
                mTargetPos.x = rect._C;
            }
            mTargetPos.y = mStartPos.y;
            mTime = param.mMoveThunderAcrossTime;
        }
        break;
    case 1:
        if (mCount < mTime) {
            mCount++;
        } else {
            mCount = 0;
            mPhase = 2;
            mStartPos = obj().location().pos().getXY();
            f32 sign = obj().location().pos().x > obj().comp().mainCamera().getCenter().x ? 1.0f : -1.0f;
            mTargetPos.x = mStartPos.x - sign * param.mMoveThunderDistance;
            mTargetPos.y = mStartPos.y;
            obj().target().invert();
            mTime = param.mMoveThunderTime;
            obj().model().reqScript(0);
            obj().objColl().clearAttack();
            obj().effect().state().release();
            obj().soundSE().state().stop();
        }
        break;
    case 2:
        if (mCount < mTime) {
            mCount++;
        } else {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            return;
        }
        break;
    }
    if (obj().scriptTrigger().get(0)) {
        custom.reqThunderGroundEffect();
    }
}

void StateMoveThunder::procMove() {
    const Param& param = obj().param().dubior();
    f32 rate = static_cast<f32>(mCount) / static_cast<f32>(mTime);
    Vector2 pos;
    f32 rateX = rate;
    if (mPhase == 1) {
        f32 square = rate * rate;
        f32 curve = 1.5f * square - 0.5f * rate * square;
        rateX = 1.0f - Math::CosDegF(90.0f * (param.mMoveThunderWave * Math::SinDegF(360.0f * curve) + rate));
    }
    pos.x = Math::LinearInterpolation(mStartPos.x, mTargetPos.x, rateX);
    pos.y = Math::LinearInterpolation(mStartPos.y, mTargetPos.y, rate);
    obj().location().setPos(pos.toVector3());
}

void StateMoveThunder::procFixPos() {}

}}}}  // namespace scn::step::boss::dubior
