#include "scn/step/enemy/metalgeneralbit/BrainMain.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/metalgeneralbit/StateAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

BrainMain::BrainMain(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMain::onStart() {
    obj().stateChanger().setNextState<StateAppear, Enemy*>(&obj());
    return true;
}

bool BrainMain::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::metalgeneralbit
