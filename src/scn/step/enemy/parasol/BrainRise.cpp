#include "scn/step/enemy/parasol/BrainRise.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/parasol/StateLink.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasol {

BrainRise::BrainRise(Enemy& enemy) : BrainBase(enemy) {}

bool BrainRise::onStart() {
    obj().stateChanger().setNextState<StateLink, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::parasol
