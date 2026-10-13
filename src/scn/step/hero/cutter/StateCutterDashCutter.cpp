#include "scn/step/hero/cutter/StateCutterDashCutter.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/chara/Knockback.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/CutterParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterDashCutter::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCutterDashCutter, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterDashCutter::StateCutterDashCutter(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setGround();
    obj().model().script().start(0x8C);
    obj().mapColl().setThroughOneSpace(true);
    obj().invincible().setPerm();
    obj().knockback().setIsValid(false);
}

StateCutterDashCutter::~StateCutterDashCutter() {
    obj().mapColl().setThroughOneSpace(false);
}

void StateCutterDashCutter::procAnim() {
    mFrame++;
    if (mFrame == obj().param().cutter()._4) {
        obj().move().setSpeedH(obj().target().getSign() * obj().param().cutter()._0);
    }
    if (mFrame == obj().param().cutter()._8) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateCutterDashCutter::procMove() {
    gobj::MoveParamDecel decel = obj().param().cutter()._C;
    if (obj().footState().isGround()) {
        obj().move().groundDecel(decel);
    } else {
        obj().move().airDecelFall(decel, obj().param().common()._90);
    }
}

void StateCutterDashCutter::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::cutter
