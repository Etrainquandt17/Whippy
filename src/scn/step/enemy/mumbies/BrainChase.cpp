#include "scn/step/enemy/mumbies/BrainChase.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mumbies/StateChase.h"

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {

BrainChase::BrainChase(Enemy& enemy) : BrainBase(enemy) {}

bool BrainChase::onStart() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

bool BrainChase::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::mumbies
