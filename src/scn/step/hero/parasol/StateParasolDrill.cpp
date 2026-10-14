#include "scn/step/hero/parasol/StateParasolDrill.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ParasolParam.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/parasol/Barrier.h"
#include "scn/step/hero/parasol/StateParasolDrillEnd.h"
#include "util/StateChanger.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace hero {
namespace parasol {

bool StateParasolDrill::TryToChangeState(Hero* hero) {
    if (hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateParasolDrill, Hero*>(hero);
        return true;
    }
    return false;
}

StateParasolDrill::StateParasolDrill(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , _C(true)
    , _10(0.0f)
    , _14(false)
    , mIsAir(obj().footState().isAir()) {
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    Barrier::SetValid(obj(), false);
    obj().mapColl().setThroughOneSpace(true);
    const ParasolParam& param = obj().param().parasol();
    f32 sign = obj().target().getSign();
    f32 speed = mIsAir ? param._8 : param._4;
    obj().move().setSpeedH(sign * speed);
    Utility::AirAttackInitSpeedV(obj());
    obj().invincible().setPerm();
    obj().soundSE()._4.start(0x1CD);
    obj().model().script().start(0x105);
}

StateParasolDrill::~StateParasolDrill() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_PARASOL) {
        if (obj().model().weapon().isValid()) {
            obj().model().weapon().effect().release();
        }
        obj().model().subAnimControl().setLiftUpRHand(true);
        Barrier::SetValid(obj(), true);
        obj().soundSE()._78.stop();
        obj().mapColl().setThroughOneSpace(false);
    }
}

void StateParasolDrill::procAnim() {
    const ParasolParam& param = obj().param().parasol();
    mFrame++;
    if (mIsAir && mFrame > param._0) {
        obj().move().setSpeedH(0.6f * obj().move().velocity().x);
        obj().stateChanger().setNextState<StateParasolDrillEnd, Hero*>(objPtr());
        return;
    }
    f32 limit = obj().param().parasol()._C;
    if (mIsAir) {
        limit *= 2.0f;
    }
    if (Math::AbsF32(obj().move().velocity().x) <= limit) {
        obj().stateChanger().setNextState<StateParasolDrillEnd, Hero*>(objPtr());
    }
}

void StateParasolDrill::procMove() {
    const ParasolParam& param = obj().param().parasol();
    if (mIsAir) {
        obj().move().airDecelFall(param._20, param._24);
    } else {
        obj().move().airDecelFall(param._10, param._14);
    }
}

void StateParasolDrill::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::parasol
