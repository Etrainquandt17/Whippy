#include "scn/step/enemy/kabu/StateGrandLowperEscapeStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/kabu/StateGrandLowperEscape.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

StateGrandLowperEscapeStart::StateGrandLowperEscapeStart(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().move().resetVelocity();
    obj().model().reqScript(12);
}

StateGrandLowperEscapeStart::~StateGrandLowperEscapeStart() {}

void StateGrandLowperEscapeStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateGrandLowperEscape, Enemy*>(objPtr());
    }
}

void StateGrandLowperEscapeStart::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateGrandLowperEscapeStart::procFixPos() {}

}
}
}
}
