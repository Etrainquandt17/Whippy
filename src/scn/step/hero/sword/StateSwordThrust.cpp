#include "scn/step/hero/sword/StateSwordThrust.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/chara/Knockback.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/sword/StateSwordRaising.h"
#include "scn/step/hero/sword/StateSwordThrustEnd.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordThrust::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordThrust, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordThrust::StateSwordThrust(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsDash(false) {
    obj().mapColl().setThroughOneSpace(true);
    obj().invincible().setPerm();
    obj().knockback().setIsValid(false);
    obj().model().script().start(0x79);
}

StateSwordThrust::~StateSwordThrust() {
    obj().mapColl().setThroughOneSpace(false);
}

void StateSwordThrust::procAnim() {
    if (mIsDash) {
        if (obj().hid().isHold(8) && obj().hid().isTrigger(0x20)) {
            obj().stateChanger().setNextState<StateSwordRaising, Hero*>(objPtr());
            return;
        }
        if (0.0f == obj().move().velocity().x) {
            obj().stateChanger().setNextState<StateSwordThrustEnd, Hero*>(objPtr());
            return;
        }
    }
    if (++mFrame == 6) {
        obj().move().setSpeedH(obj().target().getSign() * obj().param().sword()._70);
        mIsDash = true;
    }
}

void StateSwordThrust::procMove() {
    if (mIsDash) {
        const SwordParam& param = obj().param().sword();
        if (obj().footState().isGround()) {
            gobj::MoveParamDecel decel = mFrame < param._74 ? param._78 : param._80;
            obj().move().groundDecel(decel);
        } else {
            gobj::MoveParamDecel decel = mFrame < param._74 ? param._7C : param._84;
            obj().move().airDecelFall(decel, obj().param().common()._90);
        }
    } else {
        Utility::MoveDefaultBrakeNoOnIce(obj());
    }
}

void StateSwordThrust::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::sword
