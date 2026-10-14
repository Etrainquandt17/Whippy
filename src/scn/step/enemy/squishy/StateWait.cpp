#include "scn/step/enemy/squishy/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/squishy/ParamData.h"
#include "scn/step/enemy/squishy/StateFall.h"
#include "scn/step/enemy/squishy/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().move().resetVelocity();
    obj().model().rotCtrl().initRotH(0.0f);
    obj().model().rotCtrl().setValid(false);
}

StateWait::~StateWait() {
    obj().model().rotCtrl().setValid(true);
}

void StateWait::procAnim() {
    const ParamData& param = obj().param().squishy();
    mFrame++;
    if (mFrame == param.mMoveOnLandFrame) {
        obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
    }
}

void StateWait::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::squishy
