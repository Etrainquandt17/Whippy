#include "scn/step/hero/common/StateSuperJump.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Stepping.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateSuperJump::StateSuperJump(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsFall(false) {
    obj().footState().setAir();
    obj().move().setSpeedV(obj().param().common()._180);
    if (obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().stateChecker().set_14(14);
    obj().stepping().setEnableReceive(true);
    obj().invincible().setPerm();
    obj().model().setFixDir(true);
    obj().stateChecker().setSuperJump(true);
    obj().model().script().start(0x41);
}

StateSuperJump::~StateSuperJump() {
    obj().stateChecker().setRun(false);
    obj().stateChecker().setSuperJump(false);
}

void StateSuperJump::procAnim() {
    mFrame++;
    obj().abilityManager().chkDiscardAbility();
    if (mFrame == obj().param().common()._184) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSuperJump::procMove() {
    if (mIsFall) {
        Utility::MoveFromKeyState(obj(), obj().param().common()._78, obj().param().common()._74,
                                  obj().param().common()._194);
    } else {
        Utility::MoveFromKeyState(obj(), obj().param().common()._78, obj().param().common()._74,
                                  obj().param().common()._188);
    }
    if (!mIsFall && obj().move().velocity().y <= 0.0f) {
        obj().move().resetSpeedV();
        mIsFall = true;
    }
}

void StateSuperJump::procFixPos() {}

}}}}  // namespace scn::step::hero::common
