#include "scn/step/enemy/mahoroalowper/BrainZigzag.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroalowper/StateZigzag.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroalowper {

BrainZigzag::BrainZigzag(Enemy& enemy) : BrainBase(enemy) {}

bool BrainZigzag::onStart() {
    obj().stateChanger().setNextState<StateZigzag, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroalowper
