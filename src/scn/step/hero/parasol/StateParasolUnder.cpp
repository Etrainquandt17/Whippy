#include "scn/step/hero/parasol/StateParasolUnder.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ParasolParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/parasol/Barrier.h"
#include "util/StateChanger.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace parasol {

bool StateParasolUnder::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateParasolUnder, Hero*>(hero);
        return true;
    }
    return false;
}

StateParasolUnder::StateParasolUnder(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    Barrier::SetValid(obj(), false);
    obj().move().setSpeedV(obj().param().parasol()._160);
    Utility::AirAttackInitSpeedV(obj());
    obj().model().script().start(0x109);
}

StateParasolUnder::~StateParasolUnder() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_PARASOL) {
        if (obj().model().weapon().isValid()) {
            obj().model().weapon().effect().release();
        }
        obj().model().subAnimControl().setLiftUpRHand(true);
        Barrier::SetValid(obj(), true);
        Vector3 velocity = obj().move().velocity();
        velocity.y = Math::Min(velocity.y, obj().param().parasol()._164);
        obj().move().setVelocity(velocity);
    }
}

void StateParasolUnder::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateParasolUnder::procMove() {
    const ParasolParam& param = obj().param().parasol();
    gobj::MoveParamFall fall = mFrame <= 2 ? gobj::MoveParamFall::Zero() : param._178;
    Utility::MoveFromKeyState(obj(), param._168, param._174, fall);
}

void StateParasolUnder::procFixPos() {
}

}}}}  // namespace scn::step::hero::parasol
