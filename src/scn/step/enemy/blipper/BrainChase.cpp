#include "scn/step/enemy/blipper/BrainChase.h"

#include "scn/step/chara/Water.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/blipper/StateChase.h"
#include "scn/step/enemy/blipper/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

BrainChase::BrainChase(Enemy& enemy) : BrainBase(enemy) {}

bool BrainChase::onStart() {
    if (obj().water().isInWater()) {
        obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    }
    return true;
}

bool BrainChase::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::blipper
