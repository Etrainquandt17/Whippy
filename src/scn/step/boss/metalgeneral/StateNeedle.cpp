#include "scn/step/boss/metalgeneral/StateNeedle.h"

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

StateNeedle::StateNeedle(Boss* boss, u32 index) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    switch (static_cast<int>(index)) {
    case 1:
        obj().model().reqScript(0x13);
        break;
    case 2:
        obj().model().reqScript(0x14);
        break;
    case 3:
        obj().model().reqScript(0x15);
        break;
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(static_cast<GuardType>(2));
    obj().move().resetVelocity();
}

StateNeedle::~StateNeedle() {}

void StateNeedle::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFall, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        custom.weaponCtrl().reqNeedlePlus();
    }
    if (obj().scriptTrigger().get(1)) {
        custom.weaponCtrl().reqNeedleSlant();
    }
    if (obj().scriptTrigger().get(2)) {
        custom.weaponCtrl().reqNeedleAll();
    }
}

void StateNeedle::procMove() {}

void StateNeedle::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
