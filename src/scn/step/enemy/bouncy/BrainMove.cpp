#include "scn/step/enemy/bouncy/BrainMove.h"

#include "gobj/Move.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/bouncy/ParamData.h"
#include "scn/step/enemy/bouncy/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<StateJump, Enemy*>(&obj());
    Utility::SetTargetByDirType(obj());
    return true;
}

bool BrainMove::onRecover() {
    obj().move().setSpeedH(obj().param().bouncy().mMoveRecoverSpeedH);
    obj().move().setSpeedV(obj().param().bouncy().mMoveRecoverSpeedV);
    return onStart();
}

}}}}  // namespace scn::step::enemy::bouncy
