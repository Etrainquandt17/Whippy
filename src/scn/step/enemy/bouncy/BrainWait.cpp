#include "scn/step/enemy/bouncy/BrainWait.h"

#include "gobj/Move.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/bouncy/ParamData.h"
#include "scn/step/enemy/bouncy/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateJump, Enemy*>(&obj());
    obj().move().resetSpeedH();
    return true;
}

bool BrainWait::onRecover() {
    obj().move().resetSpeedH();
    obj().move().setSpeedV(obj().param().bouncy().mWaitRecoverSpeedV);
    return onStart();
}

}}}}  // namespace scn::step::enemy::bouncy
