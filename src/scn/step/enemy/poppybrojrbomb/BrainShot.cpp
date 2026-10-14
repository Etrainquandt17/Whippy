#include "scn/step/enemy/poppybrojrbomb/BrainShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/poppybrojrbomb/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojrbomb {

BrainShot::BrainShot(Enemy& enemy) : BrainBase(enemy) {}

bool BrainShot::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::poppybrojrbomb
