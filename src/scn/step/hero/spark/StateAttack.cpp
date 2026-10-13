#include "scn/step/hero/spark/StateAttack.h"
#include "gobj/Script.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/SparkParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/spark/Custom.h"
#include "scn/step/hero/spark/StateAttackEnd.h"
#include "scn/step/sfx/DarknessLightSizeKind.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace spark {

namespace {

inline const SparkParamAttack& param(Hero& hero) {
    return hero.param().spark()._0;
}

}

bool StateAttack::TryToChangeState(Hero* hero) {
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateAttack, Hero*>(hero);
        return true;
    }
    return false;
}

StateAttack::StateAttack(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsEnd(false) {
    obj().piggyback().unlinkAll();
    obj().model().setFixDir(true);
    obj().model().script().start(0xCA);
    Utility::AirAttackInitSpeedV(obj());
    const SparkParamAttack& p = param(obj());
    obj().invincible().set(p._0);
    obj().abilityManager().customSpark().setAction(true);
}

StateAttack::~StateAttack() {
    if (!mIsEnd) {
        obj().effect()._8.releaseAndVanish();
        obj().effect()._58.releaseAndVanish();
    }
    obj().soundSE()._78.stop();
    obj().abilityManager().customSpark().setAction(false);
}

void StateAttack::procAnim() {
    mFrame++;
    if (obj().model().scriptTrigger().get(0)) {
        obj().abilityManager().setCustomDarknessLightSizeKind(static_cast<sfx::DarknessLightSizeKind>(5));
    }
    if (mFrame == param(obj())._4) {
        obj().soundSE()._78.start(0x1B2);
    }
    if (mFrame > param(obj())._8 && !obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<StateAttackEnd, Hero*>(objPtr());
        mIsEnd = true;
    }
}

void StateAttack::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateAttack::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::spark
