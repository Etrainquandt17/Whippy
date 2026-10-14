#include "scn/step/enemy/pluid/BrainStay.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/pluid/StateStay.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

BrainStay::BrainStay(Enemy& enemy) : BrainBase(enemy) {}

bool BrainStay::onStart() {
    obj().stateChanger().setNextState<StateStay, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::pluid
