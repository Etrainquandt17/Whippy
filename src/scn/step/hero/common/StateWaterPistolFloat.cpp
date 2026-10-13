#include "scn/step/hero/common/StateWaterPistolFloat.h"
#include "gobj/Move.h"
#include "hel/math/Vector2.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/IndiviUtil.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/common/StateWaterFloat.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateWaterPistolFloat::TryToChangeState(Hero* hero) {
    if (!IndiviUtil::IsKirby(hero->kind())) {
        return false;
    }
    if (hero->stateChecker().isCarryBombDanger()) {
        return false;
    }
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateWaterPistolFloat, Hero*>(hero);
        return true;
    }
    return false;
}

StateWaterPistolFloat::StateWaterPistolFloat(Hero* hero)
    : StateBase(hero) {
    obj().model().setFixDir(true);
    obj().stateChecker().setFloat(true);
    obj().model().script().start(0x23);
}

StateWaterPistolFloat::~StateWaterPistolFloat() {
    obj().stateChecker().setFloat(false);
    obj().runChecker().cancelContinue();
}

void StateWaterPistolFloat::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (obj().model().scriptTrigger().get(0)) {
        hel::math::Vector2 offset(obj().model().isRightDir() ? 1.0f : -1.0f, 0.0f);
        Utility::CreateWaterPistol(obj(), offset, false);
    }
    if (obj().model().scriptTrigger().get(1)) {
        obj().stateChanger().setNextState<StateWaterFloat, Hero*>(objPtr());
    } else if (!obj().water().isOnSurface()) {
        Utility::ReqWaterFloatOutProduce(obj());
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateWaterPistolFloat::procMove() {
    const CommonParamWater water = obj().param().common()._A8;
    Utility::MoveFromKeyState(obj(), water._14, water._10, gobj::MoveParamFall::Zero());
}

void StateWaterPistolFloat::procFixPos() {}

}}}}  // namespace scn::step::hero::common
