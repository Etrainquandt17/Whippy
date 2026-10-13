#include "scn/step/hero/cutter/StateCutterDrop.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/CutterParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterDrop::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCutterDrop, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterDrop::StateCutterDrop(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(0x96);
    obj().model().setFixDir(true);
    obj().move().setSpeedH(obj().param().cutter()._10 * obj().target().getSign());
    obj().move().setSpeedV(obj().param().cutter()._14);
    obj().invincible().set(obj().param().cutter()._18);
}

StateCutterDrop::~StateCutterDrop() {
}

void StateCutterDrop::procAnim() {
    mFrame++;
    if (mFrame >= obj().param().cutter()._20 && !obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
        return;
    }
    if (mFrame >= obj().param().cutter()._1C && obj().hid().isTrigger(0x10)) {
        obj().stateChanger().setNextState<common::StateHover, Hero*, bool>(objPtr(), false);
    }
}

void StateCutterDrop::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
}

void StateCutterDrop::procFixPos() {
    if (mFrame > 1 && !obj().objColl().objColl().attack().isCollideGimmick()
        && common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
        obj().move().resetVelocity();
    }
}

}
}
}
}
