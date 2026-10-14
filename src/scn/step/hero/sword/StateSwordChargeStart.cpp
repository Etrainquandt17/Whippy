#include "scn/step/hero/sword/StateSwordChargeStart.h"
#include "gobj/Move.h"
#include "gobj/FootState.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/sword/StateSwordCharge.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordChargeStart::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->hid().isHold(0x20)) {
        hero->stateChanger().setNextState<StateSwordChargeStart, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordChargeStart::StateSwordChargeStart(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setGround();
    obj().model().script().start(0x85);
}

StateSwordChargeStart::~StateSwordChargeStart() {
}

void StateSwordChargeStart::procAnim() {
    mFrame++;
    if (!obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateSwordCharge, Hero*>(objPtr());
    }
}

void StateSwordChargeStart::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateSwordChargeStart::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(&obj());
    }
}

}}}}  // namespace scn::step::hero::sword
