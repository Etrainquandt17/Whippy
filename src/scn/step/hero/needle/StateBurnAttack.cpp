#include "scn/step/hero/needle/StateBurnAttack.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/NeedleParam.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/needle/Custom.h"
#include "scn/step/hero/needle/StateAttack.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

namespace {

inline const NeedleParamBurnAttack& param(Hero& hero) {
    return hero.param().needle()._38;
}

}

StateBurnAttack::StateBurnAttack(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().model().script().start(0xBE);
    reqWeaponAll();
    obj().move().resetVelocity();
    const NeedleParamBurnAttack& p = param(obj());
    obj().invincible().set(p._0);
}

StateBurnAttack::~StateBurnAttack() {
}

void StateBurnAttack::procAnim() {
    mFrame++;
    if (mFrame >= param(obj())._4 && obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<StateAttack, Hero*, bool, bool>(objPtr(), true, true);
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateBurnAttack::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateBurnAttack::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

void StateBurnAttack::reqWeaponAll() {
    u32 num = obj().footState().isGround() ? 6 : 10;
    obj().abilityManager().customNeedle().shotAllWeapon(num);
}

}}}}  // namespace scn::step::hero::needle
