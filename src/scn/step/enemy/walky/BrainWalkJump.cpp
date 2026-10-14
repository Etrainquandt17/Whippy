#include "scn/step/enemy/walky/BrainWalkJump.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/walky/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

BrainWalkJump::BrainWalkJump(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkJump::onStart() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

bool BrainWalkJump::onLanding() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

void BrainWalkJump::update() {
    Utility::ChkNururiTurn(obj());
    Utility::ChkCliffTurn(obj());
}

}}}}  // namespace scn::step::enemy::walky
