#include "scn/step/boss/dubior/StateMoveThunderStart.h"

#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateMoveThunder.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateMoveThunderStart::StateMoveThunderStart(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mTargetPos() {
    const Param& param = obj().param().dubior();
    obj().footState().setAir();
    obj().model().reqScript(0);
    mStartPos = obj().location().pos().getXY();
    f32 sign = obj().location().pos().x > obj().comp().mainCamera().getCenter().x ? 1.0f : -1.0f;
    mTargetPos = obj().comp().mainCamera().getCenter();
    mTargetPos.x += sign * param.mMoveThunderOffsetX;
    mTargetPos.y += param.mMoveThunderHeight - obj().camOffs().y;
    obj().target().setIsRightDir(sign < 0.0f);
}

StateMoveThunderStart::~StateMoveThunderStart() {}

void StateMoveThunderStart::procAnim() {
    const Param& param = obj().param().dubior();
    if (mCount < param.mMoveThunderStartTime) {
        mCount++;
        return;
    }
    obj().stateChanger().setNextState<StateMoveThunder, Boss*>(objPtr());
}

void StateMoveThunderStart::procMove() {
    const Param& param = obj().param().dubior();
    f32 rate = static_cast<f32>(mCount) / static_cast<f32>(param.mMoveThunderStartTime);
    hel::math::Vector2 pos = hel::math::Math::LinearInterpolation(mStartPos, mTargetPos, rate);
    obj().location().setPos(pos.toVector3());
}

void StateMoveThunderStart::procFixPos() {}

}
}
}
}
