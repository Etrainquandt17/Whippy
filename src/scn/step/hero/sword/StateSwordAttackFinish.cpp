#include "scn/step/hero/sword/StateSwordAttackFinish.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/hero/AbilityManager.h"
#include "gobj/FootState.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordAttackFinish::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->abilityManager().getChainPhase() == 1 && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordAttackFinish, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordAttackFinish::StateSwordAttackFinish(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setGround();
    obj().model().script().start(0x89);
}

StateSwordAttackFinish::~StateSwordAttackFinish() {
}

void StateSwordAttackFinish::procAnim() {
    const SwordParam& param = obj().param().sword();
    mFrame++;
    if (mFrame == param._10) {
        obj().move().setSpeedH(param._14 * obj().target().getSign());
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
    }
}

void StateSwordAttackFinish::procMove() {
    Utility::MoveDefaultBrakeNoOnIce(obj());
}

void StateSwordAttackFinish::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        // &obj() and not objPtr(): the original link kept this function apart from
        // common::StateGuard::procFixPos, which has the same code, so the two call something different.
        obj().stateChanger().setNextState<common::StateFall, Hero*>(&obj());
    }
}

}}}}  // namespace scn::step::hero::sword
