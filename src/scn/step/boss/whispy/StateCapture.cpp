#include "scn/step/boss/whispy/StateCapture.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/whispy/StateChewing.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateCapture::StateCapture(Boss* boss) : StateBase(boss) {
    obj().model().reqScript(18);
}

StateCapture::~StateCapture() {}

void StateCapture::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateChewing, Boss*>(objPtr());
    }
}

void StateCapture::procMove() {}

void StateCapture::procFixPos() {}

}
}
}
}
