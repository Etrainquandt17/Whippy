#include "scn/step/hero/cutter/StateCutterSweepCutter.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterSweepCutter::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isHold(0x20)) {
        hero->stateChanger().setNextState<StateCutterSweepCutter, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterSweepCutter::StateCutterSweepCutter(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(0x95);
    obj().model().setFixDir(true);
    if (obj().move().velocity().y >= 0.0f) {
        obj().move().resetSpeedV();
    }
}

StateCutterSweepCutter::~StateCutterSweepCutter() {
}

void StateCutterSweepCutter::procAnim() {
    mFrame++;
    if (!obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateCutterSweepCutter::procMove() {
    Utility::MoveDefault(obj());
}

void StateCutterSweepCutter::procFixPos() {
    if (common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
        return;
    }
}

}
}
}
}
