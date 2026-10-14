#include "scn/step/boss/fattybuffer/StateSwellBalloonStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateSwellBalloonMove.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellBalloonStart::StateSwellBalloonStart(Boss* boss, const Vector3& speed, u32 count)
    : StateBase(boss), mSpeed(speed), mCount(count) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    custom.mapCollCtrl().setBalloon();
    obj().model().reqScript(0x1C);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_4);
    mSpeed.x *= obj().target().getSign();
    obj().guard().setType(static_cast<GuardType>(4));
}

StateSwellBalloonStart::~StateSwellBalloonStart() {}

void StateSwellBalloonStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().move().setVelocity(mSpeed);
        obj().stateChanger().setNextState<StateSwellBalloonMove, Boss*, u32>(objPtr(), mCount);
    }
}

void StateSwellBalloonStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateSwellBalloonStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
