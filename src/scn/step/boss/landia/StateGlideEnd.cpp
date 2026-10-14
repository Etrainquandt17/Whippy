#include "scn/step/boss/landia/StateGlideEnd.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/StateWait.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateGlideEnd::StateGlideEnd(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    const Param& param = obj().param().landia();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    custom.waftCtrl().setWaveDefault();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    Vector2 pos(param.mGlideEndOffsetX * obj().target().getSign() + obj().comp().mainCamera().getCenter().x,
                param.mBaseHeight + obj().basePos().y);
    custom.waftCtrl().setPosEnf(pos.toVector3());
    obj().target().invert();
    mStartPos = custom.waftCtrl().getRefPos().getXY();
    mGoalPos.x = mStartPos.x;
    mGoalPos.y = param.mGlideEndOffsetY + obj().comp().mainCamera().getCenter().y;
}

StateGlideEnd::~StateGlideEnd() {}

void StateGlideEnd::procAnim() {
    const Param& param = obj().param().landia();
    if (mCount < param.mGlideEndFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateGlideEnd::procMove() {
    const Param& param = obj().param().landia();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mGlideEndFrame);
    f32 rate = Math::SinDegF(90.0f * t);
    custom.waftCtrl().setRefPos(Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateGlideEnd::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
