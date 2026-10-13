#include "scn/step/boss/whispy/StateVacuumEnd.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/StateWait.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateVacuumEnd::StateVacuumEnd(Boss* boss) : StateBase(boss) {
    obj().model().reqScript(17);
    obj().guard().setType(Utility::IsVariationExtra(obj()) ? GUARD_TYPE_1 : GUARD_TYPE_2);
}

StateVacuumEnd::~StateVacuumEnd() {}

void StateVacuumEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateVacuumEnd::procMove() {}

void StateVacuumEnd::procFixPos() {}

}
}
}
}
