#include "scn/step/hero/damage/StateGuard.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Guard.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/PowerCharge.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateGuard.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateGuard::StateGuard(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    hel::math::Vector2 attackPos = obj().objColl().objColl().bodyColl().damageInfo().attackPos();
    obj().target().setIsRightDir(obj().location().pos().x < attackPos.x);
    obj().model().script().start(0x31);
    obj().move().setSpeedH(0.2f * -obj().target().getSign());
    obj().guard().setGuard(true);
    obj().guard().resetAnimFrame();
    obj().powerCharge().setCanCharge(true);
}

StateGuard::~StateGuard() {
    obj().guard().setGuard(false);
}

void StateGuard::procAnim() {
    mFrame++;
    if (obj().abilityManager().tryToChangeStateOnDamage()) {
        return;
    }
    if (mFrame >= 15) {
        if (common::StateGuard::TryToChangeStateContinue(objPtr())) {
            return;
        }
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateGuard::procMove() {
    hero::Utility::MoveGuardDamage(obj());
}

void StateGuard::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
