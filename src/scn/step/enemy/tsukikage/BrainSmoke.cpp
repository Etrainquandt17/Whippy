#include "scn/step/enemy/tsukikage/BrainSmoke.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/tsukikage/StateWarp.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

BrainSmoke::BrainSmoke(Enemy& enemy) : BrainBase(enemy) {}

bool BrainSmoke::onStart() {
    obj().stateChanger().setNextState<StateWarp, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::tsukikage
