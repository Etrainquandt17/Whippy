#include "scn/step/hero/sword/StateSwordMeteor.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/sword/StateSwordMeteorLanding.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordMeteor::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordMeteor, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordMeteor::StateSwordMeteor(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    const SwordParam& param = obj().param().sword();
    obj().piggyback().unlinkAll();
    obj().footState().setAir();
    obj().model().script().start(0x81);
    obj().move().setSpeedH(param._20 * obj().target().getSign());
    obj().move().setSpeedV(param._24);
    obj().invincible().set(param._28);
}

StateSwordMeteor::~StateSwordMeteor() {
}

void StateSwordMeteor::procAnim() {
    mFrame++;
}

void StateSwordMeteor::procMove() {
    const SwordParam& param = obj().param().sword();
    f32 fall = param._30;
    if (mFrame > 10) {
        fall = param._34;
    }
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Create(param._38, fall, param._3C));
}

void StateSwordMeteor::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateSwordMeteorLanding, Hero*>(objPtr());
    }
}

}}}}  // namespace scn::step::hero::sword
