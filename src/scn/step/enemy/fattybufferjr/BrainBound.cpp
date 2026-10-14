#include "scn/step/enemy/fattybufferjr/BrainBound.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/fattybufferjr/StateAppearFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

BrainBound::BrainBound(Enemy& enemy) : BrainBase(enemy) {}

bool BrainBound::onStart() {
    obj().stateChanger().setNextState<StateAppearFall, Enemy*>(&obj());
    return true;
}

bool BrainBound::onLanding() {
    return false;
}

}}}}  // namespace scn::step::enemy::fattybufferjr
