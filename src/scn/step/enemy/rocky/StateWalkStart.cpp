#include "scn/step/enemy/rocky/StateWalkStart.h"

#include "gobj/Anim.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "scn/step/enemy/rocky/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateWalkStart::StateWalkStart(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(7);
    obj().model().anim().setFrameRate(1.0f);
}

StateWalkStart::~StateWalkStart() {}

void StateWalkStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWalk, Enemy*>(objPtr());
    }
}

void StateWalkStart::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::rocky
