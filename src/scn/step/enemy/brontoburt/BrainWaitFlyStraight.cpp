#include "scn/step/enemy/brontoburt/BrainWaitFlyStraight.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/brontoburt/StateFly.h"
#include "scn/step/enemy/brontoburt/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

BrainWaitFlyStraight::BrainWaitFlyStraight(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWaitFlyStraight::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWaitFlyStraight::onRecover() {
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::brontoburt
