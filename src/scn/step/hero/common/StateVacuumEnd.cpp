#include "scn/step/hero/common/StateVacuumEnd.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/gimmick/StateHangSwitchWait.h"
#include "scn/step/hero/gimmick/StateRopeFlatWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateVacuumEnd::StateVacuumEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().script().start(0x13);
}

StateVacuumEnd::~StateVacuumEnd() {}

void StateVacuumEnd::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (gimmick::StateHangSwitchWait::TryToChangeState(objPtr()) ||
        gimmick::StateRopeFlatWait::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<StateVacuum, Hero*>(objPtr());
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateVacuumEnd::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateVacuumEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
