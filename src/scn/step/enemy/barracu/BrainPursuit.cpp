#include "scn/step/enemy/barracu/BrainPursuit.h"

#include "scn/step/chara/Water.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/barracu/StateBound.h"
#include "scn/step/enemy/barracu/StatePursuit.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

BrainPursuit::BrainPursuit(Enemy& enemy) : BrainBase(enemy) {}

bool BrainPursuit::onStart() {
    if (obj().water().isInWater()) {
        obj().stateChanger().setNextState<StatePursuit, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateBound, Enemy*>(&obj());
    }
    return true;
}

bool BrainPursuit::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::barracu
