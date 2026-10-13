#include "scn/step/hero/leaf/StateUpper.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/LeafParam.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

bool StateUpper::TryToChangeState(Hero* hero) {
    if (hero->hid().isHold(8) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateUpper, Hero*>(hero);
        return true;
    }
    return false;
}

StateUpper::StateUpper(Hero* hero)
    : StateBase(hero)
    , mIsTriggered(false) {
    obj().model().setFixDir(true);
    obj().model().script().start(0x9F);
    Utility::AirAttackInitSpeedV(obj());
}

StateUpper::~StateUpper() {
    const LeafParam& param = obj().param().leaf();
    obj().abilityManager().setActionInterval(param._50);
    if (!mIsTriggered) {
        obj().effect()._58.releaseAndVanish();
        hel::math::Vector3 pos = static_cast<const Hero&>(obj()).location().pos() +
                                 hel::math::Vector3(obj().target().isRightDir() ? 1.0f : -1.3f, 0.0f, 0.0f);
        obj().effect()._8.requestP(static_cast<effect::Kind>(0x380), pos);
    }
}

void StateUpper::procAnim() {
    if (obj().model().scriptTrigger().get(0)) {
        mIsTriggered = true;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateUpper::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateUpper::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
