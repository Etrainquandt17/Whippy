#include "scn/step/enemy/brontoburt/BrainWaitPursuit.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/brontoburt/StatePursuit.h"
#include "scn/step/enemy/brontoburt/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

BrainWaitPursuit::BrainWaitPursuit(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWaitPursuit::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWaitPursuit::onRecover() {
    obj().stateChanger().setNextState<StatePursuit, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::brontoburt
