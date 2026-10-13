#include "scn/step/hero/damage/StateSuperTeamAttack.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/ObjStop.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/damage/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateSuperTeamAttack::StateSuperTeamAttack(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().model().script().start(0x49);
    Utility::InitTarget(obj());
    Utility::InitVelocity(obj());
    obj().objStop().setSpecial();
    if (obj().objColl().objColl().bodyColl().hit().isCollide()) {
        ocoll::Element element =
            static_cast<ocoll::Element>(obj().objColl().objColl().bodyColl().damageInfo().data().mElement);
        obj().damageFlash().set(element);
    }
}

StateSuperTeamAttack::~StateSuperTeamAttack() {
    obj().objStop().unsetSpecial();
    obj().damageFlash().unset();
    obj().invincible().set(30);
}

void StateSuperTeamAttack::procAnim() {
    if (obj().abilityManager().tryToChangeStateOnDamage()) {
        return;
    }
    if (obj().objStop().isSpecial()) {
        obj().objStop().unsetSpecial();
    }
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSuperTeamAttack::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.001f), obj().param().common()._90);
}

void StateSuperTeamAttack::procFixPos() {}

}
}
}
}
