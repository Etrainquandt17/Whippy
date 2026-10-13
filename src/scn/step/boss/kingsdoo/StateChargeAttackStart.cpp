#include "scn/step/boss/kingsdoo/StateChargeAttackStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/kingsdoo/Param.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

StateChargeAttackStart::StateChargeAttackStart(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(17);
    obj().brainCtrl().toValid();
    Utility::ControlHateOnAction(obj());
}

StateChargeAttackStart::~StateChargeAttackStart() {}

void StateChargeAttackStart::procAnim() {}

void StateChargeAttackStart::procMove() {
    const Param& param = obj().param().kingsdoo();
    obj().move().groundDecel(param._24);
}

void StateChargeAttackStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}
}
}
}
