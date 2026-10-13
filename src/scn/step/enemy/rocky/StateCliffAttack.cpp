#include "scn/step/enemy/rocky/StateCliffAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateCliffJump.h"
#include "scn/step/enemy/rocky/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateCliffAttack::StateCliffAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(9);
    obj().model().anim().setFrameRate(1.0f);
    obj().move().resetSpeedH();
}

StateCliffAttack::~StateCliffAttack() {}

void StateCliffAttack::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd() && mFrame > obj().param().rocky().mCliffAttackWait) {
        obj().stateChanger().setNextState<StateCliffJump, Enemy*>(objPtr());
    }
}

void StateCliffAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::rocky
