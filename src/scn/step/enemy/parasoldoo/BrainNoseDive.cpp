#include "scn/step/enemy/parasoldoo/BrainNoseDive.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/parasoldoo/StateFall.h"
#include "scn/step/enemy/parasoldoo/StateNoseDive.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {

BrainNoseDive::BrainNoseDive(Enemy& enemy) : BrainBase(enemy) {}

bool BrainNoseDive::onStart() {
    obj().stateChanger().setNextState<StateNoseDive, Enemy*>(&obj());
    return true;
}

bool BrainNoseDive::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

void BrainNoseDive::update() {
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::parasoldoo
