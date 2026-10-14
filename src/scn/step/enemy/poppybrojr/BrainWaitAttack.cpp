#include "scn/step/enemy/poppybrojr/BrainWaitAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

BrainWaitAttack::BrainWaitAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWaitAttack::onStart() {
    obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWaitAttack::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::poppybrojr
