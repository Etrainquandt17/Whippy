#include "scn/step/enemy/lanzer/BrainWait.h"

#include "gobj/Target.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    if (obj().variation() == 0x8a) {
        obj().target().setIsRightDir(false);
    } else if (obj().variation() == 0x8b) {
        obj().target().setIsRightDir(true);
    }
    return true;
}

bool BrainWait::onLanding() {
    return onStart();
}

void BrainWait::update() {
    if (obj().variation() == 0x89) {
        Utility::TurnHero(obj());
    }
}

}}}}  // namespace scn::step::enemy::lanzer
