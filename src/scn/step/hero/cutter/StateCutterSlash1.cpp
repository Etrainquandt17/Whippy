#include "scn/step/hero/cutter/StateCutterSlash1.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/cutter/StateCutterSlash2.h"
#include "scn/step/hero/cutter/StateCutterThrow.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterSlash1::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->abilityManager().getChainPhase() == 0 && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCutterSlash1, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterSlash1::StateCutterSlash1(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsNext(false)
    , mIsCheckHit(true) {
    obj().footState().setGround();
    obj().model().script().start(0x8D);
    obj().objColl().objColl().setSearchHitTeamXlu(-3);
}

StateCutterSlash1::~StateCutterSlash1() {
}

void StateCutterSlash1::procAnim() {
    mFrame++;
    if (mFrame >= 2 && obj().hid().isTrigger(0x20)) {
        mIsNext = true;
    }
    if (obj().model().isAllEnd()) {
        if (mIsNext) {
            obj().stateChanger().setNextState<StateCutterSlash2, Hero*>(objPtr());
        } else {
            obj().abilityManager().setChainPhase(1);
            obj().abilityManager().setChainRespite(0x14);
            obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
        }
    }
}

void StateCutterSlash1::procMove() {
    Utility::MoveDefaultBrakeNoOnIce(obj());
}

void StateCutterSlash1::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        // &obj() and not objPtr(): the original link kept this function apart from
        // common::StateGuard::procFixPos, which has the same code, so the two call something different.
        obj().stateChanger().setNextState<common::StateFall, Hero*>(&obj());
    }
}

bool StateCutterSlash1::procObjCollReact() {
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
