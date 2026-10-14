#include "scn/step/hero/sword/StateSwordRaising.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/sword/StateSwordMeteor.h"
#include "scn/step/hero/sword/StateSwordRaisingEnd.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordRaising::TryToChangeState(Hero* hero) {
    if (hero->hid().isHold(8) && hero->hid().isTrigger(0x20)
        && (!hero->footState().isGround() || !hero->stateChecker().isRun() || !hero->hid().isHold(3))) {
        hero->stateChanger().setNextState<StateSwordRaising, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordRaising::StateSwordRaising(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mRate(obj().param().sword()._50) {
    obj().model().script().start(0x7F);
    obj().footState().setAir();
    const SwordParam& param = obj().param().sword();
    obj().invincible().set(param._54);
}

StateSwordRaising::~StateSwordRaising() {
}

void StateSwordRaising::procAnim() {
    const SwordParam& param = obj().param().sword();
    mFrame++;
    if (mFrame > param._58 && StateSwordMeteor::TryToChangeState(objPtr())) {
        return;
    }
    if (mFrame == param._5C) {
        obj().stateChanger().setNextState<StateSwordRaisingEnd, Hero*>(objPtr());
    }
}

void StateSwordRaising::procMove() {
    const SwordParam& param = obj().param().sword();
    if (mFrame >= param._60) {
        mRate -= param._64;
        if (mRate < 0.0f) {
            mRate = 0.0f;
        }
        obj().move().setSpeedH(mRate * param._68 * obj().target().getSign());
        obj().move().setSpeedV(mRate * param._6C);
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
    } else {
        Utility::MoveDefaultBrake(obj());
    }
}

void StateSwordRaising::procFixPos() {
}

}}}}  // namespace scn::step::hero::sword
