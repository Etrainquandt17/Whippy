#include "scn/step/enemy/nruff/BrainRun.h"

#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/nruff/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

BrainRun::BrainRun(Enemy& enemy) : BrainBase(enemy) {}

bool BrainRun::onStart() {
    obj().model().reqScript(3);
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

bool BrainRun::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::nruff
