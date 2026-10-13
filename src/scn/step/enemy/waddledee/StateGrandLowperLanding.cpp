#include "scn/step/enemy/waddledee/StateGrandLowperLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

StateGrandLowperLanding::StateGrandLowperLanding(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().move().resetVelocity();
    obj().model().reqScript(18);
}

StateGrandLowperLanding::~StateGrandLowperLanding() {}

void StateGrandLowperLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(objPtr());
    }
}

void StateGrandLowperLanding::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateGrandLowperLanding::procFixPos() {}

}}}}  // namespace scn::step::enemy::waddledee
