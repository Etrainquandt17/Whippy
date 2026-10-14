#include "scn/step/enemy/brontoburt/BrainFly.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/brontoburt/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

bool BrainFly::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::brontoburt
