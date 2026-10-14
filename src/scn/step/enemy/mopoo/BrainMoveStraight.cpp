#include "scn/step/enemy/mopoo/BrainMoveStraight.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mopoo/StateHide.h"
#include "scn/step/enemy/mopoo/StateMoveStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {

BrainMoveStraight::BrainMoveStraight(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMoveStraight::onStart() {
    obj().stateChanger().setNextState<StateHide, Enemy*>(&obj());
    return true;
}

bool BrainMoveStraight::onRecover() {
    obj().stateChanger().setNextState<StateMoveStraight, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mopoo
