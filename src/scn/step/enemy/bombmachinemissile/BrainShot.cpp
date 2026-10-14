#include "scn/step/enemy/bombmachinemissile/BrainShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/bombmachinemissile/StateShot.h"

namespace scn {
namespace step {
namespace enemy {
namespace bombmachinemissile {

BrainShot::BrainShot(Enemy& enemy) : BrainBase(enemy) {}

bool BrainShot::onStart() {
    obj().stateChanger().setNextState<StateShot, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::bombmachinemissile
