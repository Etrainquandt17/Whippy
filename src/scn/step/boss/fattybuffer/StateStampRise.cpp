#include "scn/step/boss/fattybuffer/StateStampRise.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateStampHold.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/hero/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

namespace {

const StampParam& t_param(Boss& boss) {
    const Param& param = boss.param().fattybuffer();
    return boss.angry().isAngry() ? param.mStampAngry : param.mStamp;
}

}

StateStampRise::StateStampRise(Boss* boss, bool isChase) : StateBase(boss), mCount(0), mStartX(0.0f), mGoalX(0.0f), mIsChase(isChase) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0xD);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetVelocity();
    Vector3 pos = obj().location().pos();
    Vector3 heroPos = obj().comp().heroManager().getNearestPlayerPos(pos);
    mStartX = pos.x;
    mGoalX = heroPos.x;
    bool isRightDir = mStartX < mGoalX;
    obj().target().setIsRightDir(isRightDir);
}

StateStampRise::~StateStampRise() {}

void StateStampRise::procAnim() {
    const StampParam& param = t_param(obj());
    if (mCount < param.mRiseFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateStampHold, Boss*, bool>(objPtr(), mIsChase);
    }
}

void StateStampRise::procMove() {
    const StampParam& param = t_param(obj());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mRiseFrame);
    f32 s = 1.0f - Math::SinDegF(90.0f * t);
    f32 rate = 1.0f - s * (s * s);
    f32 y = rate * param.mRiseHeight;
    f32 x = Math::Interpolate(mStartX, mGoalX, t);
    obj().location().setPos(Vector3(x, y + obj().basePos().y, 0.0f));
}

void StateStampRise::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
