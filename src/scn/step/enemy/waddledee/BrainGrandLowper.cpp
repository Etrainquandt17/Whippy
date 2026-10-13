#include "scn/step/enemy/waddledee/BrainGrandLowper.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWalkStraight.h"
#include "scn/step/enemy/waddledee/StateGrandLowperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

bool BrainGrandLowper::onLanding() {
    obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::waddledee
