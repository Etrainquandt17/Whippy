#include "scn/step/boss/hrd3pilot/StateAppear.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

StateAppear::StateAppear(Boss* boss) : StateBase(boss) {
    obj().model().reqScript(1);
}

StateAppear::~StateAppear() {}

void StateAppear::procAnim() {}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {}

}
}
}
}
