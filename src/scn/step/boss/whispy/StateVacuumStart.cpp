#include "scn/step/boss/whispy/StateVacuumStart.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/StateVacuum.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateVacuumStart::StateVacuumStart(Boss* boss) : StateBase(boss) {
    obj().model().reqScript(15);
    obj().guard().setType(Utility::IsVariationExtra(obj()) ? GUARD_TYPE_3 : GUARD_TYPE_4);
}

StateVacuumStart::~StateVacuumStart() {}

void StateVacuumStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateVacuum, Boss*>(objPtr());
    }
}

void StateVacuumStart::procMove() {}

void StateVacuumStart::procFixPos() {}

}}}}  // namespace scn::step::boss::whispy
