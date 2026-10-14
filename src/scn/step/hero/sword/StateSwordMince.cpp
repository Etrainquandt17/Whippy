#include "scn/step/hero/sword/StateSwordMince.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/sword/StateSwordAttackFinish.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordMince::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordMince, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordMince::StateSwordMince(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsNext(false) {
    obj().footState().setGround();
    obj().model().script().start(0x83);
    obj().move().setSpeedH(obj().target().getSign() * obj().param().sword()._44);
}

StateSwordMince::~StateSwordMince() {
}

void StateSwordMince::procAnim() {
    const SwordParam& param = obj().param().sword();
    mFrame++;
    if (mFrame > param._48 && obj().hid().isTrigger(0x20)) {
        mIsNext = true;
    }
    if (obj().model().isAllEnd()) {
        if (mIsNext) {
            obj().stateChanger().setNextState<StateSwordAttackFinish, Hero*>(objPtr());
        } else {
            obj().abilityManager().setChainPhase(1);
            obj().abilityManager().setChainRespite(param._4C);
            obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
        }
    }
}

void StateSwordMince::procMove() {
    Utility::MoveDefaultBrakeNoOnIce(obj());
}

void StateSwordMince::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(&obj());
    }
}

}}}}  // namespace scn::step::hero::sword
