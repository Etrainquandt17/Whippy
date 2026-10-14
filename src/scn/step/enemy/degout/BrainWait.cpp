#include "scn/step/enemy/degout/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/degout/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainWait::onRecover() {
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::degout
