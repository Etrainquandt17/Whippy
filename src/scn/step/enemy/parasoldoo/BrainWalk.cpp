#include "scn/step/enemy/parasoldoo/BrainWalk.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/parasoldoo/StateFall.h"
#include "scn/step/enemy/parasoldoo/StateParasolFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<StateParasolFall, Enemy*>(&obj());
    return true;
}

bool BrainWalk::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

void BrainWalk::update() {
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::parasoldoo
