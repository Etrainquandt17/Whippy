#include "scn/step/enemy/barracu/BrainSwimStraight.h"

#include "scn/step/chara/Water.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/barracu/StateBound.h"
#include "scn/step/enemy/barracu/StateSwimStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

BrainSwimStraight::BrainSwimStraight(Enemy& enemy) : BrainBase(enemy) {}

bool BrainSwimStraight::onStart() {
    if (obj().water().isInWater()) {
        obj().stateChanger().setNextState<StateSwimStraight, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateBound, Enemy*>(&obj());
    }
    return true;
}

bool BrainSwimStraight::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::barracu
