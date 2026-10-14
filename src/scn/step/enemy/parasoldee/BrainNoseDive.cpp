#include "scn/step/enemy/parasoldee/BrainNoseDive.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/parasoldee/StateFall.h"
#include "scn/step/enemy/parasoldee/StateNoseDive.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldee {

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

}}}}  // namespace scn::step::enemy::parasoldee
