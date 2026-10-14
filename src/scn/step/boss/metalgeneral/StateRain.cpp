#include "scn/step/boss/metalgeneral/StateRain.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/StateFall.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateRain::StateRain(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x16);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(static_cast<GuardType>(2));
    obj().move().resetVelocity();
}

StateRain::~StateRain() {}

void StateRain::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFall, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        custom.weaponCtrl().reqBall();
    }
    if (obj().scriptTrigger().get(1)) {
        custom.weaponCtrl().signalBall(enemy::metalgeneralball::SIGNAL_KIND_1);
    }
    if (obj().scriptTrigger().get(2)) {
        custom.weaponCtrl().signalBall(enemy::metalgeneralball::SIGNAL_KIND_2);
    }
    if (obj().scriptTrigger().get(3)) {
        custom.weaponCtrl().signalBall(enemy::metalgeneralball::SIGNAL_KIND_3);
    }
    if (obj().scriptTrigger().get(4)) {
        if (!custom.weaponCtrl().isHoldBall()) {
            obj().stateChanger().setNextState<StateFall, Boss*>(objPtr());
        }
    }
}

void StateRain::procMove() {}

void StateRain::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
