#include "scn/step/enemy/clayn/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/clayn/StateHideWait.h"
#include "scn/step/enemy/clayn/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateHideWait, Enemy*>(&obj());
    return true;
}

bool BrainWait::onRecover() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWait::onLanding() {
    obj().stateChanger().setNextState<StateHideWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::clayn
