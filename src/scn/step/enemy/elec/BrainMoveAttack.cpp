#include "scn/step/enemy/elec/BrainMoveAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/elec/StateChase.h"
#include "scn/step/enemy/elec/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

BrainMoveAttack::BrainMoveAttack(Enemy& enemy) : BrainBase(enemy), mIsFound(false) {}

bool BrainMoveAttack::onStart() {
    if (obj().variation() == 0xb8) {
        obj().stateChanger().setNextState<StateMoveCCW, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveCWR, Enemy*>(&obj());
    }
    return true;
}

bool BrainMoveAttack::onRecover() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

void BrainMoveAttack::update() {
    if (!mIsFound && Utility::IsHeroInRange(obj(), 8.0f, -8.0f, -3.0f, 3.0f)) {
        mIsFound = true;
        obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    }
}

}}}}  // namespace scn::step::enemy::elec
