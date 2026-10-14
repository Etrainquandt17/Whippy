#include "scn/step/enemy/starman/BrainJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateWalkStraight.h"
#include "scn/step/enemy/starman/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

BrainJump::BrainJump(Enemy& enemy) : BrainBase(enemy) {}

bool BrainJump::onStart() {
    Utility::SetTargetByDirType(obj());
    obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
    return true;
}

bool BrainJump::onLanding() {
    obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
    return true;
}

bool BrainJump::onRecover() {
    obj().move().resetSpeedV();
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

void BrainJump::update() {
    if (obj().footState().isGround()) {
        Utility::ChkCliffTurn(obj());
    }
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::starman
