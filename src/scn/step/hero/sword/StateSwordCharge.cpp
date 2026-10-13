#include "scn/step/hero/sword/StateSwordCharge.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "gobj/FootState.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/sword/StateSwordSpin.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

StateSwordCharge::StateSwordCharge(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setGround();
    obj().model().setSELoopNoReset();
    obj().model().script().start(0x86);
    obj().piggyback().setEnableReceive(true);
}

StateSwordCharge::~StateSwordCharge() {
}

void StateSwordCharge::procAnim() {
    mFrame++;
    if (!obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<StateSwordSpin, Hero*>(objPtr());
    }
}

void StateSwordCharge::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateSwordCharge::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(&obj());
    }
}

}}}}  // namespace scn::step::hero::sword
