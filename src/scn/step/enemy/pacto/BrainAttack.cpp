#include "scn/step/enemy/pacto/BrainAttack.h"

#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/pacto/StateBack.h"

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainAttack::onRecover() {
    obj().model().reqScript(0);
    obj().stateChanger().setNextState<StateBack, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::pacto
