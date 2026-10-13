#include "scn/step/hero/bomb/StatePut.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/BombParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/bomb/GearBombController.h"
#include "scn/step/hero/common/StateSquat.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

bool StatePut::TryToChangeState(Hero* hero, GearBombController& controller) {
    if (controller.isHave()) {
        return false;
    }
    if (hero->hid().isTrigger(0x20) && hero->hid().isHold(4)) {
        hero->stateChanger().setNextState<StatePut, Hero*, std::tr1::reference_wrapper<GearBombController> >(
            hero, std::tr1::ref(controller));
        return true;
    }
    return false;
}

StatePut::StatePut(Hero* hero, GearBombController& controller)
    : StateBase(hero)
    , mController(controller)
    , mFrame(0) {
    obj().model().setFixDir(true);
    const BombParam& param = obj().param().bomb();
    if (obj().footState().isAir()) {
        if (obj().move().velocity().y >= 0.0f) {
            obj().move().setSpeedV(param._4);
        } else {
            obj().move().setSpeedV(param._8);
        }
    }
    mController.haveBomb();
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().script().start(0x111);
}

StatePut::~StatePut() {
    if (mController.isHave()) {
        put();
    }
    const BombParam& param = obj().param().bomb();
    obj().abilityManager().setActionInterval(param._10);
}

void StatePut::procAnim() {
    mFrame++;
    if (mFrame == obj().param().bomb()._C) {
        put();
    }
    if (!mController.isHave() && common::StateSquat::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StatePut::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StatePut::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

void StatePut::put() {
    mController.putBomb();
}

}}}}  // namespace scn::step::hero::bomb
