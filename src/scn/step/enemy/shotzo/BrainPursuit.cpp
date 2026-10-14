#include "scn/step/enemy/shotzo/BrainPursuit.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/shotzo/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

BrainPursuit::BrainPursuit(Enemy& enemy) : BrainBase(enemy) {}

bool BrainPursuit::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::shotzo
