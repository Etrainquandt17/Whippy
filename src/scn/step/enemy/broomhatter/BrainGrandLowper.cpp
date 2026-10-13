#include "scn/step/enemy/broomhatter/BrainGrandLowper.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/broomhatter/StateGrandLowperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

bool BrainGrandLowper::onLanding() {
    return false;
}

}}}}  // namespace scn::step::enemy::broomhatter
