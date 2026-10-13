#include "scn/step/hero/parasol/StateParasolDive.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ParasolParam.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/parasol/Barrier.h"
#include "scn/step/hero/parasol/StateParasolParachuteFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

bool StateParasolDive::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateParasolDive, Hero*>(hero);
        return true;
    }
    return false;
}

StateParasolDive::StateParasolDive(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsDive(true)
    , mSign(0.0f)
    , mIsEffectReleased(false) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().script().start(0x102);
    obj().model().subAnimControl().setLiftUpRHand(false);
    Barrier::SetValid(obj(), false);
    mSign = obj().target().getSign();
    obj().move().setSpeedH(obj().target().getSign() * obj().param().parasol()._48);
    obj().move().setSpeedV(obj().param().parasol()._4C);
    obj().invincible().setPerm();
    obj().soundSE()._78.start(0x1D1);
}

StateParasolDive::~StateParasolDive() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_PARASOL) {
        if (!mIsEffectReleased && obj().model().weapon().isValid()) {
            obj().model().weapon().effect().release();
        }
        obj().model().subAnimControl().setLiftUpRHand(true);
        Barrier::SetValid(obj(), true);
        obj().soundSE()._78.stop();
    }
}

void StateParasolDive::procAnim() {
    mFrame++;
    mIsEffectReleased = false;
    if (mIsDive) {
        if (!obj().hid().isHold(0x20) && mFrame > obj().param().parasol()._50) {
            mIsDive = false;
            obj().model().script().start(0x103);
            obj().model().weapon().effect().release();
            mIsEffectReleased = true;
        }
    } else {
        obj().objColl().objColl().clearAttack();
        if (obj().model().isAllEnd()) {
            obj().stateChanger().setNextState<StateParasolParachuteFall, Hero*>(objPtr());
        }
    }
}

void StateParasolDive::procMove() {
    if (mIsDive) {
        obj().move().decel(gobj::MoveParamDecel::Zero());
        return;
    }
    Utility::MoveFromKeyState(obj(), obj().param().parasol()._54, obj().param().parasol()._60,
                              obj().param().parasol()._64);
}

void StateParasolDive::procFixPos() {
    if (mFrame > 1 && !obj().objColl().objColl().attack().isCollideGimmick()
        && common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
        obj().move().resetVelocity();
    }
}

}
}
}
}
