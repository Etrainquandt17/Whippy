#include "scn/step/hero/cutter/StateCutterSlash2.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CutterParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/cutter/StateCutterFinalCutterRise.h"
#include "scn/step/hero/cutter/StateCutterThrow.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterSlash2::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->abilityManager().getChainPhase() == 1 && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCutterSlash2, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterSlash2::StateCutterSlash2(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsNext(false)
    , mIsCheckHit(true) {
    obj().footState().setGround();
    obj().model().script().start(0x8E);
    obj().move().setSpeedH(obj().target().getSign() * obj().param().cutter()._24._0);
    obj().objColl().objColl().setSearchHitTeamXlu(-3);
}

StateCutterSlash2::~StateCutterSlash2() {
}

void StateCutterSlash2::procAnim() {
    CutterParamSlash param = obj().param().cutter()._24;
    mFrame++;
    if (mFrame >= param._4 && obj().hid().isTrigger(0x20)) {
        mIsNext = true;
    }
    if (obj().model().isAllEnd()) {
        if (mIsNext) {
            obj().stateChanger().setNextState<StateCutterFinalCutterRise, Hero*>(objPtr());
        } else {
            obj().abilityManager().setChainPhase(2);
            obj().abilityManager().setChainRespite(param._8);
            obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
        }
    }
}

void StateCutterSlash2::procMove() {
    Utility::MoveDefaultBrakeNoOnIce(obj());
}

void StateCutterSlash2::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        // &obj() and not objPtr(): the original link kept this function apart from
        // common::StateGuard::procFixPos, which has the same code, so the two call something different.
        obj().stateChanger().setNextState<common::StateFall, Hero*>(&obj());
    }
}

bool StateCutterSlash2::procObjCollReact() {
    if (mIsCheckHit) {
        mIsCheckHit = false;
        if (!Utility::IsSearchCollideNoStarEffect(obj())) {
            obj().stateChanger().setNextState<StateCutterThrow, Hero*>(objPtr());
            return true;
        }
    }
    return false;
}

}}}}  // namespace scn::step::hero::cutter
