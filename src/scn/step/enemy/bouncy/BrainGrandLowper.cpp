#include "scn/step/enemy/bouncy/BrainGrandLowper.h"

#include "gobj/Move.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/bouncy/ParamData.h"
#include "scn/step/enemy/bouncy/StateGrandLowperAppear.h"
#include "scn/step/enemy/bouncy/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

bool BrainGrandLowper::onRecover() {
    obj().move().setSpeedH(obj().param().bouncy().mMoveRecoverSpeedH);
    obj().move().setSpeedV(obj().param().bouncy().mMoveRecoverSpeedV);
    obj().stateChanger().setNextState<StateJump, Enemy*>(&obj());
    Utility::SetTargetByDirType(obj());
    return true;
}

}}}}  // namespace scn::step::enemy::bouncy
