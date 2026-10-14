#include "scn/step/hero/damage/StateAbilityCrash.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/hero/AbilityCrashCtrl.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace damage {

bool StateAbilityCrash::TryToChangeState(Hero* hero) {
    if (hero->abilityCrashCtrl().isRequested()) {
        hero->abilityCrashCtrl().clearRequested();
        hero->stateChanger().setNextState<StateAbilityCrash, Hero*>(hero);
        return true;
    }
    return false;
}

StateAbilityCrash::StateAbilityCrash(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().model().script().start(0x49);
    obj().move().setVelocity(Vector3(-0.075f * obj().target().getSign(), 0.125f, 0.0f));
    obj().invincible().setPerm();
    obj().effect()._58.requestN(static_cast<effect::Kind>(0xE0), 1);
    obj().soundSE()._160.start(0xD4);
    obj().damageFlash().set(static_cast<ocoll::Element>(4));
    obj().hitStop().set(20);
}

StateAbilityCrash::~StateAbilityCrash() {
    obj().model().modelRotCtrl().setRotV(0.0f);
    obj().model().modelRotCtrl().setRotH(0.0f);
    obj().damageFlash().unset();
    obj().invincible().set(60);
}

void StateAbilityCrash::procAnim() {
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateAbilityCrash::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), obj().param().common()._90);
}

void StateAbilityCrash::procFixPos() {}

}}}}  // namespace scn::step::hero::damage
