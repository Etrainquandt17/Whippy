#include "scn/step/hero/fire/StateFireIgnition.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/FireParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

StateFireIgnition::StateFireIgnition(Hero* hero)
    : StateBase(hero)
    , mFrame(obj().param().fire()._B4) {
    obj().piggyback().unlinkAll();
    obj().model().script().start(0xB5);
    const FireParam& param = obj().param().fire();
    obj().invincible().set(param._B4);
    obj().abilityManager().setCustomDarknessLightSizeKind(static_cast<sfx::DarknessLightSizeKind>(5));
}

StateFireIgnition::~StateFireIgnition() {
}

void StateFireIgnition::procAnim() {
    if (mFrame != 0) {
        mFrame--;
    }
    if (mFrame == 0 && !obj().hid().isHold(0x20)) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateFireIgnition::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateFireIgnition::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::fire
