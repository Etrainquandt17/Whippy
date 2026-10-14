#include "scn/step/boss/fattybuffer/StateStampFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateStampLanding.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

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

StateStampFall::StateStampFall(Boss* boss) : StateBase(boss), mCount(0), mStartY(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0xE);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_3);
    obj().move().resetVelocity();
    mStartY = obj().location().pos().y;
}

StateStampFall::~StateStampFall() {}

void StateStampFall::procAnim() {
    const StampParam& param = t_param(obj());
    if (mCount < param.mFallFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateStampLanding, Boss*>(objPtr());
    }
}

void StateStampFall::procMove() {
    const StampParam& param = t_param(obj());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mFallFrame);
    Vector3 pos = obj().location().pos();
    pos.y = Math::Interpolate(mStartY + param.mHoldHeight, obj().basePos().y, t);
    obj().location().setPos(pos);
}

void StateStampFall::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
