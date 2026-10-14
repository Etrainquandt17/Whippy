#include "scn/step/enemy/noddy/BrainWalk.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/noddy/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace noddy {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::noddy
