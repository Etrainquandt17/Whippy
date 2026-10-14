#include "scn/step/enemy/mopoo/BrainMoveCurve.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mopoo/StateHide.h"
#include "scn/step/enemy/mopoo/StateMoveCurve.h"

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {

BrainMoveCurve::BrainMoveCurve(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMoveCurve::onStart() {
    obj().stateChanger().setNextState<StateHide, Enemy*>(&obj());
    return true;
}

bool BrainMoveCurve::onRecover() {
    obj().stateChanger().setNextState<StateMoveCurve, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mopoo
