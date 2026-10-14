#include "scn/step/enemy/leaper/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateShootingFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace leaper {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<common::StateShootingFly, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::leaper
