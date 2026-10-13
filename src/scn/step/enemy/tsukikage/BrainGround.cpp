#include "scn/step/enemy/tsukikage/BrainGround.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/tsukikage/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

BrainGround::BrainGround(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGround::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::tsukikage
