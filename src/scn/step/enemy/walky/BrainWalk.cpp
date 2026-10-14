#include "scn/step/enemy/walky/BrainWalk.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/walky/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

bool BrainWalk::onLanding() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

void BrainWalk::update() {
    Utility::ChkNururiTurn(obj());
    Utility::ChkCliffTurn(obj());
}

}}}}  // namespace scn::step::enemy::walky
