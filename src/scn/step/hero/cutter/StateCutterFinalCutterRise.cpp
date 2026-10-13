#include "scn/step/hero/cutter/StateCutterFinalCutterRise.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CameraTarget.h"
#include "scn/step/hero/CutterParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/cutter/StateCutterFinalCutterDrop.h"
#include "scn/step/hero/cutter/StateCutterThrow.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterFinalCutterRise::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->abilityManager().getChainPhase() == 2 && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCutterFinalCutterRise, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterFinalCutterRise::StateCutterFinalCutterRise(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , _C(1.0f)
    , mIsCheckHit(true) {
    obj().footState().setGround();
    obj().model().script().start(0x8F);
    obj().move().setSpeedH(obj().target().getSign() * obj().param().cutter()._30);
    obj().invincible().setPerm();
    obj().cameraTarget().setZeroIntpRate();
    obj().objColl().objColl().setSearchHitTeamXlu(-3);
}

StateCutterFinalCutterRise::~StateCutterFinalCutterRise() {
    obj().move().resetVelocity();
}

void StateCutterFinalCutterRise::procAnim() {
    mFrame++;
    if (mFrame == obj().param().cutter()._38) {
        obj().footState().setAir();
        obj().move().setSpeedV(obj().param().cutter()._34);
    }
    if (mFrame == obj().param().cutter()._3C) {
        obj().stateChanger().setNextState<StateCutterFinalCutterDrop, Hero*>(objPtr());
    }
}

void StateCutterFinalCutterRise::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateCutterFinalCutterRise::procFixPos() {
}

bool StateCutterFinalCutterRise::procObjCollReact() {
    if (mIsCheckHit) {
        mIsCheckHit = false;
        if (!Utility::IsSearchCollideNoStarEffect(obj())) {
            obj().stateChanger().setNextState<StateCutterThrow, Hero*>(objPtr());
            return true;
        }
    }
    return false;
}

}
}
}
}
