#include "scn/step/enemy/broomhatter/StateGrandLowperEscapeStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/broomhatter/StateGrandLowperEscape.h"
#include "scn/step/enemy/common/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

StateGrandLowperEscapeStart::StateGrandLowperEscapeStart(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().move().resetVelocity();
    obj().model().reqScript(9);
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
