#include "scn/step/hero/cutter/StateCutterCatch.h"
#include "gobj/FootState.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateGuard.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateSliding.h"
#include "scn/step/hero/common/StateSquat.h"
#include "scn/step/hero/common/StateWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterCatch::TryToChangeState(Hero* hero) {
    if (hero->stateChecker().is_1d() && !hero->stateChecker().isJumpStart()) {
        hero->stateChanger().setNextState<StateCutterCatch, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterCatch::StateCutterCatch(Hero* hero)
    : StateBase(hero) {
    obj().model().setFixDir(true);
    obj().model().script().start(0x93);
    if (obj().runChecker().isGroundContinue()) {
        obj().stateChecker().setRun(true);
    }
}

StateCutterCatch::~StateCutterCatch() {
    if (obj().stateChecker().isRun()) {
        obj().runChecker().setAirContinue();
        obj().runChecker().setGroundContinue();
    }
    obj().stateChecker().setRun(false);
}

void StateCutterCatch::procAnim() {
    if (obj().abilityManager().tryToChangeState()) {
        return;
    }
    if (common::StateSliding::TryToChangeState(objPtr()) || common::StateSquat::TryToChangeState(objPtr())
        || common::StateLadder::TryToChangeState(objPtr()) || common::StateJumpStart::TryToChangeState(objPtr())
        || common::StateGuard::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        if (obj().footState().isGround()) {
            if (obj().stateChecker().isRun()) {
                obj().runChecker().setGroundContinue();
            }
            if (common::StateRun::TryToChangeState(objPtr())) {
                return;
            }
            obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
        } else {
            obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
        }
    }
}

void StateCutterCatch::procMove() {
    Utility::MoveDefault(obj());
}

void StateCutterCatch::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::cutter
