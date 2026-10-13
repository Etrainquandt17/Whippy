#include "scn/step/hero/sword/StateSwordUnderThrust.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "scn/step/hero/CommonParam.h"
#include "gobj/FootState.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/sword/StateSwordUnderThrustLanding.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

StateSwordUnderThrust::StateSwordUnderThrust(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().model().script().start(0x7C);
    obj().move().resetSpeedH();
}

StateSwordUnderThrust::~StateSwordUnderThrust() {
}

void StateSwordUnderThrust::procAnim() {
}

void StateSwordUnderThrust::procMove() {
    f32 speed = obj().param().sword()._A4;
    obj().move().airDecelFall(obj().param().common()._74, gobj::MoveParamFall::Create(speed, speed, 0.1f));
}

void StateSwordUnderThrust::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<StateSwordUnderThrustLanding, Hero*>(objPtr());
    }
}

}}}}  // namespace scn::step::hero::sword
