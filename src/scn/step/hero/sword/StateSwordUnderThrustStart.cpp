#include "scn/step/hero/sword/StateSwordUnderThrustStart.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/sword/StateSwordUnderThrust.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordUnderThrustStart::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordUnderThrustStart, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordUnderThrustStart::StateSwordUnderThrustStart(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(0x7B);
    obj().move().resetSpeedV();
}

StateSwordUnderThrustStart::~StateSwordUnderThrustStart() {
}

void StateSwordUnderThrustStart::procAnim() {
    if (++mFrame == obj().param().sword()._94) {
        obj().stateChanger().setNextState<StateSwordUnderThrust, Hero*>(objPtr());
    }
}

void StateSwordUnderThrustStart::procMove() {
    const SwordParam& param = obj().param().sword();
    Utility::MoveFromKeyState(obj(), obj().param().common()._78, obj().param().common()._74, param._98);
}

void StateSwordUnderThrustStart::procFixPos() {
}

}}}}  // namespace scn::step::hero::sword
