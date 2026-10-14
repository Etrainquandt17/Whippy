#include "scn/step/boss/roah/StateTackleEnd.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateTackleEnd::StateTackleEnd(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().target().setIsRightDir(false);
    obj().model().reqScript(0);
    custom.mahoroaCtrl().getCustom().reqMotionWarpOut();
    custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(3));
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().location().setPos((obj().comp().mainCamera().getCenter() + Vector2(param.mTackleEndOffset)).toVector3());
    mStartPos = obj().location().pos().getXY();
    mGoalPos = obj().basePos();
    custom.rotCtrl().setFixRotRate(1.0f);
}

StateTackleEnd::~StateTackleEnd() {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(1));
    custom.rotCtrl().setFixRotRate(param.mFixRotRate);
}

void StateTackleEnd::procAnim() {
    const Param& param = obj().param().roah();
    if (mCount < param.mTackleEndFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateTackleEnd::procMove() {
    const Param& param = obj().param().roah();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mTackleEndFrame);
    f32 rate = Math::SinDegF(90.0f * t);
    obj().location().setPos(Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateTackleEnd::procFixPos() {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 x = obj().location().pos().x;
    if (obj().comp().mainCamera().getCenter().x + param.mTackleEndHitX > x) {
        custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    }
}

}}}}  // namespace scn::step::boss::roah
