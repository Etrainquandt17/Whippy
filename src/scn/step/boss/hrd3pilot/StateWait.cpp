#include "scn/step/boss/hrd3pilot/StateWait.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    obj().model().reqScript(0);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {}

void StateWait::procMove() {}

void StateWait::procFixPos() {}

}
}
}
}
