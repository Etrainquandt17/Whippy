#include "scn/step/enemy/gigatzo/BrainAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/gigatzo/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::gigatzo
