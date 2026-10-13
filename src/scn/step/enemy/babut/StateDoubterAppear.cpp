#include "scn/step/enemy/babut/StateDoubterAppear.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/common/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

StateDoubterAppear::StateDoubterAppear(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(7);
    obj().vacuumReceiver().setResistLevelStep(2);
    obj().objColl().setBodyCollStateXlu();
}

StateDoubterAppear::~StateDoubterAppear() {
    obj().objColl().setBodyCollStateNormal();
}

void StateDoubterAppear::procAnim() {
    if (obj().move().velocity().isZeroLoose(0.00001f)) {
        obj().stateChanger().setNextState<common::StateFly, Enemy*>(objPtr());
    }
}

void StateDoubterAppear::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Create(0.0075f));
}

}}}}  // namespace scn::step::enemy::babut
