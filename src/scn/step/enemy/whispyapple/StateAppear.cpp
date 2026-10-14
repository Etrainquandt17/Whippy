#include "scn/step/enemy/whispyapple/StateAppear.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/whispyapple/StateFall.h"
#include "scn/step/enemy/whispyapple/WhispyAppleUtility.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().move().resetVelocity();
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(7);
}

StateAppear::~StateAppear() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateAppear::procAnim() {
    if (obj().model().isAllEnd()) {
        WhispyAppleUtility::ReqFallSE(obj());
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::whispyapple
