#include "scn/step/boss/common/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
    obj().hateCtrl().fix();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateWait::procMove() {
    obj().move().groundDecel(gobj::MoveParamDecel::Create(0.01f));
}

void StateWait::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}
}
}
}
