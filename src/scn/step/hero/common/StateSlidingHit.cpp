#include "scn/step/hero/common/StateSlidingHit.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/common/StateFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateSlidingHit::StateSlidingHit(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().model().script().start(0xD);
    obj().move().setVelocity(hel::math::Vector3(-obj().target().getSign() * obj().param().common()._1B8,
                                                obj().param().common()._1BC, 0.0f));
}

StateSlidingHit::~StateSlidingHit() {}

void StateSlidingHit::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFall, Hero*>(objPtr());
    }
}

void StateSlidingHit::procMove() {
    obj().move().airDecelFall(obj().param().common()._1C0, obj().param().common()._90);
}

void StateSlidingHit::procFixPos() {}

}
}
}
}
