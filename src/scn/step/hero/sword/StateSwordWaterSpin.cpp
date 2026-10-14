#include "scn/step/hero/sword/StateSwordWaterSpin.h"
#include "gobj/Move.h"
#include "gobj/FootState.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordWaterSpin::TryToChangeState(Hero* hero) {
    if (hero->water().isInWater() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordWaterSpin, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordWaterSpin::StateSwordWaterSpin(Hero* hero)
    : StateBase(hero)
    , mIsBubble(true)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().script().start(0x8A);
    obj().invincible().set(7);
}

StateSwordWaterSpin::~StateSwordWaterSpin() {
}

void StateSwordWaterSpin::procAnim() {
    mFrame++;
    if (obj().model().scriptTrigger().get(0)) {
        mIsBubble = false;
    }
    if (mIsBubble) {
        Utility::RequestBubbleRollAction(obj(), mFrame);
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSwordWaterSpin::procMove() {
    Utility::MoveDefault(obj());
}

void StateSwordWaterSpin::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
}

}}}}  // namespace scn::step::hero::sword
