#include "scn/step/enemy/chasekeydegout/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/chasekeydegout/StateChase.h"
#include "scn/step/enemy/common/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace chasekeydegout {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainWait::onRecover() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::chasekeydegout
