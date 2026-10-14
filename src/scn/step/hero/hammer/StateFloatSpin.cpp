#include "scn/step/hero/hammer/StateFloatSpin.h"
#include "gobj/FootState.h"
#include "gobj/MoveParam.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/common/StateJump.h"
#include "scn/step/hero/common/StateWaterFloat.h"
#include "util/StateChanger.h"

using hel::math::Direction3;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool StateFloatSpin::TryToChangeState(Hero* hero) {
    if (hero->stateChecker().isFloat() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateFloatSpin, Hero*>(hero);
        return true;
    }
    return false;
}

StateFloatSpin::StateFloatSpin(Hero* hero)
    : StateBase(hero)
    , mIsBubble(true)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().stateChecker().setFloat(true);
    obj().model().script().start(0x137);
}

StateFloatSpin::~StateFloatSpin() {
    obj().stateChecker().setFloat(false);
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_HAMMER) {
        obj().model().subAnimControl().setLiftUpRHand(true);
    }
}

void StateFloatSpin::procAnim() {
    if (!obj().water().isOnSurface()) {
        reqJumpEffect();
        obj().stateChanger().setNextState<common::StateJump, Hero*>(objPtr());
        return;
    }
    mFrame++;
    if (obj().model().scriptTrigger().get(0)) {
        mIsBubble = false;
    }
    if (mIsBubble) {
        hero::Utility::RequestBubbleRollAction(obj(), mFrame);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWaterFloat, Hero*>(objPtr());
    }
}

void StateFloatSpin::procMove() {
    const CommonParamWater water = obj().param().common()._A8;
    hero::Utility::MoveFromKeyState(obj(), water._14, water._10, gobj::MoveParamFall::Zero());
}

void StateFloatSpin::procFixPos() {
}

void StateFloatSpin::reqJumpEffect() {
    Vector3 pos = static_cast<const Hero&>(obj()).location().pos();
    pos.y += 0.5f;
    Direction3 dir;
    dir.mUp = obj().water().getSurfaceUpVec(pos.getXY());
    dir.restructUpFront();
    obj().effect()._8.requestPD(static_cast<effect::Kind>(0x74), pos, dir);
}

}}}}  // namespace scn::step::hero::hammer
