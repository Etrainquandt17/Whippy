#include "scn/step/hero/fire/StateFireSpiral.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/FireParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

bool StateFireSpiral::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateFireSpiral, Hero*>(hero);
        return true;
    }
    return false;
}

StateFireSpiral::StateFireSpiral(Hero* hero)
    : StateBase(hero)
    , mFrame(obj().param().fire()._D4)
    , mLandFrame(obj().param().fire()._D8) {
    obj().model().setFixDir(true);
    obj().model().script().start(0xB6);
    Utility::AirAttackInitSpeedV(obj());
    obj().abilityManager().setCustomDarknessLightSizeKind(static_cast<sfx::DarknessLightSizeKind>(5));
}

StateFireSpiral::~StateFireSpiral() {
    obj().effect()._58.releaseAndVanish();
    effect::Kind kind = static_cast<effect::Kind>(0x17E);
    if (obj().model().isRightDir()) {
        kind = static_cast<effect::Kind>(0x180);
    }
    obj().effect()._8.requestN(kind, 6);
}

void StateFireSpiral::procAnim() {
    if (mFrame != 0) {
        mFrame--;
    }
    if (mLandFrame != 0) {
        mLandFrame--;
    }
    if (mFrame == 0 && !obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateFireSpiral::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateFireSpiral::procFixPos() {
    if (mLandFrame == 0) {
        if (common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
            return;
        }
    } else {
        Utility::MapCollReactDefaultAction(obj());
    }
}

}}}}  // namespace scn::step::hero::fire
