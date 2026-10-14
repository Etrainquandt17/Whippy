#include "scn/step/enemy/sisterbound/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sisterbound/StateFall.h"
#include "scn/step/enemy/sisterbound/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    Utility::SetTargetByDirType(obj());
    obj().stateChanger().setNextState<StateJump, Enemy*>(&obj());
    return true;
}

bool BrainMove::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::sisterbound
