#include "scn/step/enemy/brontoburt/BrainPursuit.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/brontoburt/StatePursuit.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

BrainPursuit::BrainPursuit(Enemy& enemy) : BrainBase(enemy) {}

bool BrainPursuit::onStart() {
    obj().stateChanger().setNextState<StatePursuit, Enemy*>(&obj());
    return true;
}

bool BrainPursuit::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::brontoburt
