#include "scn/step/boss/dubior/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
    obj().hateCtrl().fix();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateWait::procMove() {
    const Param& param = obj().param().dubior();
    obj().move().decel(param._4C);
}

void StateWait::procFixPos() {}

}
}
}
}
