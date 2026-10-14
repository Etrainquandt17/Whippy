#include "scn/step/enemy/dubiorjr/BrainMain.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/dubiorjr/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

BrainMain::BrainMain(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMain::onStart() {
    obj().stateChanger().setNextState<StateFly, Enemy*, f32>(&obj(), 0.0f);
    return true;
}

bool BrainMain::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::dubiorjr
