#include "scn/step/enemy/wapodpod/BrainRise.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/wapodpod/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapodpod {

BrainRise::BrainRise(Enemy& enemy) : BrainBase(enemy) {}

bool BrainRise::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainRise::onRecover() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::wapodpod
