#include "scn/step/enemy/shotzo/BrainPursuitCeil.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/shotzo/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

BrainPursuitCeil::BrainPursuitCeil(Enemy& enemy) : BrainBase(enemy) {}

bool BrainPursuitCeil::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::shotzo
