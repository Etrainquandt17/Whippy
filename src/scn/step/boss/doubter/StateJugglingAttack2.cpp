#include "scn/step/boss/doubter/StateJugglingAttack2.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateJugglingAttack2::StateJugglingAttack2(Boss* boss) : StateBase(boss), _8(0.0f) {
    obj().footState().setAir();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    custom.jugglingCtrl().signalAllEnemyPrepare2();
    custom.jugglingCtrl().inactivateEnf();
    obj().model().reqScript(30);
    custom.bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(1));
}

StateJugglingAttack2::~StateJugglingAttack2() {}

void StateJugglingAttack2::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        custom.jugglingCtrl().signalAllEnemyShot2();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateJugglingAttack2::procMove() {
    obj().location().setPos(DynamicCastToRef<Custom, ICustom>(obj().custom()).waftPositionCtrl().getNextPos());
}

void StateJugglingAttack2::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
