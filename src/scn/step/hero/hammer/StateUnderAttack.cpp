#include "scn/step/hero/hammer/StateUnderAttack.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/HammerParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool StateUnderAttack::TryToChangeState(Hero* hero) {
    if (hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateUnderAttack, Hero*>(hero);
        return true;
    }
    return false;
}

StateUnderAttack::StateUnderAttack(Hero* hero)
    : StateBase(hero)
    , mEffectInterval(0)
    , mCanCancel(false) {
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().invincible().setPerm();
    obj().model().script().start(0x134);
    if (obj().footState().isAir()) {
        f32 speed = obj().param().hammer()._30;
        speed += obj().move().velocity().y;
        obj().move().setSpeedV(speed);
    }
}

StateUnderAttack::~StateUnderAttack() {
    obj().model().subAnimControl().setLiftUpRHand(true);
}

void StateUnderAttack::procAnim() {
    if (obj().model().scriptTrigger().get(0)) {
        mCanCancel = true;
    }
    if (mCanCancel) {
        if (common::StateJumpStart::TryToChangeState(objPtr()) || common::StateHover::TryToChangeState(objPtr())) {
            return;
        }
    }
    if (mEffectInterval != 0) {
        mEffectInterval--;
    }
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateUnderAttack::procMove() {
    hero::Utility::MoveDefaultAction(obj());
}

void StateUnderAttack::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

bool StateUnderAttack::procObjCollReact() {
    if (obj().objColl().objColl().isAttackCollide() && mEffectInterval == 0) {
        obj().effect()._58.requestN(static_cast<effect::Kind>(0x2C3), 0);
        mEffectInterval = obj().param().hammer()._34;
    }
    return false;
}

}
}
}
}
