#include "scn/step/enemy/metalgeneralthunder/BrainMain.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/metalgeneralthunder/StateShot.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

BrainMain::BrainMain(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMain::onStart() {
    obj().stateChanger().setNextState<StateShot, Enemy*>(&obj());
    return true;
}

bool BrainMain::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::metalgeneralthunder
