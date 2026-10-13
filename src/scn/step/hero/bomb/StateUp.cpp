#include "scn/step/hero/bomb/StateUp.h"
#include "gobj/GearAnim.h"
#include "gobj/Script.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/BombParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/bomb/GearBombController.h"
#include "scn/step/hero/bomb/StateCharge.h"
#include "scn/step/hero/common/StateGuard.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateSquat.h"
#include "scn/step/hero/common/StateWalk.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

bool StateUp::TryToChangeState(Hero* hero, GearBombController& controller) {
    if (controller.isHave()) {
        return false;
    }
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateUp, Hero*, std::tr1::reference_wrapper<GearBombController> >(
            hero, std::tr1::ref(controller));
        return true;
    }
    return false;
}

StateUp::StateUp(Hero* hero, GearBombController& controller)
    : StateBase(hero)
    , mController(controller)
    , mFrame(0) {
    obj().model().setFixDir(true);
    mController.haveBomb();
    obj().model().script().start(0x10A);
    obj().piggyback().unlinkAll();
}

StateUp::~StateUp() {
    obj().model().subAnimControl().setLiftUpRHand(true);
}

void StateUp::procAnim() {
    mFrame++;
    if (mFrame >= obj().param().bomb()._0) {
        if (StateCharge::TryToChangeState(objPtr(), mController) || common::StateSquat::TryToChangeState(objPtr())
            || common::StateLadder::TryToChangeState(objPtr()) || common::StateJumpStart::TryToChangeState(objPtr())
            || common::StateGuard::TryToChangeState(objPtr()) || common::StateRun::TryToChangeState(objPtr())
            || common::StateWalk::TryToChangeState(objPtr())) {
            obj().model().weapon().anim().start(1, true);
            return;
        }
    }
    if (obj().model().scriptTrigger().get(0) && !obj().hid().isHold(0x20)) {
        Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    if (obj().model().scriptTrigger().get(1)) {
        if (obj().hid().isHold(0x20)) {
            obj().stateChanger().setNextState<StateCharge, Hero*, std::tr1::reference_wrapper<GearBombController>, bool>(
                objPtr(), std::tr1::ref(mController), obj().hid().isHold(8));
        } else {
            Utility::ChangeStateWaitOrFall(obj());
        }
    }
}

void StateUp::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateUp::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

bool StateUp::procObjCollReact() {
    return false;
}

}}}}  // namespace scn::step::hero::bomb
