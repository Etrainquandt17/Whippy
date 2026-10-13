#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/hero/beam/StateBeamCycleBeam.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/captured/StateCapturedBeam.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/BeamParam.h"
#include "scn/step/hero/CaptureAttacker.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/beam/StateBeamCaptureHold.h"
#include "scn/step/sfx/DarknessLightSizeKind.h"
#include "util/ObjList.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

bool StateBeamCycleBeam::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateBeamCycleBeam, Hero*>(hero);
        return true;
    }
    return false;
}

StateBeamCycleBeam::StateBeamCycleBeam(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsFirst(true) {
    obj().model().setFixDir(true);
    obj().model().script().start(0xC4);
    const BeamParam& param = obj().param().beam();
    obj().invincible().set(param._1C);
    obj().abilityManager().setCustomDarknessLightSizeKind(static_cast<sfx::DarknessLightSizeKind>(5));
}

StateBeamCycleBeam::~StateBeamCycleBeam() {
    obj().effect()._8.releaseAndVanish();
}

void StateBeamCycleBeam::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateBeamCycleBeam::procMove() {
    gobj::MoveParamDecel decel = obj().param().beam()._20;
    if (obj().footState().isGround()) {
        obj().move().groundDecel(decel);
    } else {
        obj().move().airDecelFall(decel, obj().param().common()._90);
    }
}

void StateBeamCycleBeam::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

bool StateBeamCycleBeam::procObjCollReact() {
    if (mIsFirst) {
        mIsFirst = false;
        util::ObjRefHandle<enemy::Enemy> enemy = obj().captureAttacker().chkCaptureEnemy();
        if (enemy.isAlive()) {
            enemy->stateChanger().setNextState<enemy::captured::StateCapturedBeam, enemy::Enemy*>(enemy.operator->());
            enemy->stateChanger().changeStateIfPossible();
            obj().stateChanger().setNextState<StateBeamCaptureHold, Hero*>(objPtr());
            return true;
        }
    }
    return false;
}

}
}
}
}
