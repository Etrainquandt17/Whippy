#include "scn/step/hero/damage/StateBodyHit.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/damage/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateBodyHit::StateBodyHit(Hero* hero)
    : StateBase(hero) {
    init(static_cast<ScriptKind>(0x49));
}

StateBodyHit::StateBodyHit(Hero* hero, ScriptKind script)
    : StateBase(hero) {
    init(script);
}

StateBodyHit::~StateBodyHit() {
    obj().damageFlash().unset();
}

void StateBodyHit::procAnim() {
    if (obj().abilityManager().tryToChangeStateOnDamage()) {
        return;
    }
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateBodyHit::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.001f), obj().param().common()._90);
}

void StateBodyHit::procFixPos() {}

void StateBodyHit::init(ScriptKind script) {
    obj().footState().setAir();
    obj().model().script().start(script);
    Utility::InitTarget(obj());
    Utility::InitVelocity(obj());
    if (obj().objColl().objColl().bodyColl().hit().isCollide()) {
        ocoll::Element element =
            static_cast<ocoll::Element>(obj().objColl().objColl().bodyColl().damageInfo().data().mElement);
        obj().damageFlash().set(element);
    }
}

}}}}  // namespace scn::step::hero::damage
