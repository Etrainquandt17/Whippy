#include "scn/step/boss/dubior/StateHeightAdjust.h"

#include "gobj/FootState.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateHeightAdjust::StateHeightAdjust(Boss* boss) : StateBase(boss), mMove(), mCount(0) {
    const Param& param = obj().param().dubior();
    obj().footState().setAir();
    obj().model().reqScript(0);
    if (Utility::IsVariationBossRush(obj())) {
        mMove.x = 0.0f;
    } else {
        f32 sign = obj().location().pos().x > obj().comp().mainCamera().getCenter().x ? 1.0f : -1.0f;
        mMove.x = sign * param.mHeightAdjustDistance - (obj().location().pos().x - obj().comp().mainCamera().getCenter().x);
    }
    f32 height = obj().location().pos().y - obj().basePos().y;
    mMove.y = (param.mFirstOffsY + param.mHeightHigh) / 2.0f > height ? param.mFirstOffsY - height : param.mHeightHigh - height;
}

StateHeightAdjust::~StateHeightAdjust() {}

void StateHeightAdjust::procAnim() {
    const Param& param = obj().param().dubior();
    if (mCount < param.mHeightAdjustTime) {
        mCount++;
        return;
    }
    obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
}

void StateHeightAdjust::procMove() {
    const Param& param = obj().param().dubior();
    Vector2 pos = obj().location().pos().getXY() + mMove / static_cast<f32>(param.mHeightAdjustTime);
    obj().location().setPos(pos.toVector3());
}

void StateHeightAdjust::procFixPos() {}

}}}}  // namespace scn::step::boss::dubior
