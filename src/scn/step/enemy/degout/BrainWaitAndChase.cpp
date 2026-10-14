#include "scn/step/enemy/degout/BrainWaitAndChase.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/degout/StateChase.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

BrainWaitAndChase::BrainWaitAndChase(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWaitAndChase::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainWaitAndChase::onRecover() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::degout
