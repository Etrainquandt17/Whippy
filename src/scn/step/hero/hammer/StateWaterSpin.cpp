#include "scn/step/hero/hammer/StateWaterSpin.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool StateWaterSpin::TryToChangeState(Hero* hero) {
    if (hero->water().isInWater() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateWaterSpin, Hero*>(hero);
        return true;
    }
    return false;
}

StateWaterSpin::StateWaterSpin(Hero* hero)
    : StateBase(hero)
    , mIsBubble(true)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().script().start(0x136);
}

StateWaterSpin::~StateWaterSpin() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_HAMMER) {
        obj().model().subAnimControl().setLiftUpRHand(true);
    }
}

void StateWaterSpin::procAnim() {
    mFrame++;
    if (obj().model().scriptTrigger().get(0)) {
        mIsBubble = false;
    }
    if (mIsBubble) {
        hero::Utility::RequestBubbleRollAction(obj(), mFrame);
    }
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateWaterSpin::procMove() {
    hero::Utility::MoveDefault(obj());
}

void StateWaterSpin::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
}

}}}}  // namespace scn::step::hero::hammer
