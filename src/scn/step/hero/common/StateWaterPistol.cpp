#include "scn/step/hero/common/StateWaterPistol.h"
#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/IndiviUtil.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "util/StateChanger.h"

using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateWaterPistol::TryToChangeState(Hero* hero, const Vector2& dir) {
    if (!IndiviUtil::IsKirby(hero->kind())) {
        return false;
    }
    if (hero->stateChecker().isCarryBombDanger()) {
        return false;
    }
    if (hero->water().isInWater() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateWaterPistol, Hero*, Vector2>(hero, dir);
        return true;
    }
    return false;
}

bool StateWaterPistol::TryToChangeState(Hero* hero) {
    Vector2 dir(hero->target().getSign(), 0.0f);
    if (hero->hid().isHold(1)) {
        dir = Vector2(-1.0f, 0.0f);
    } else if (hero->hid().isHold(2)) {
        dir = Vector2(1.0f, 0.0f);
    } else if (hero->hid().isHold(8)) {
        dir = Vector2(0.0f, 1.0f);
    } else if (hero->hid().isHold(4)) {
        dir = Vector2(0.0f, -1.0f);
    }
    return TryToChangeState(hero, dir);
}

StateWaterPistol::StateWaterPistol(Hero* hero, const Vector2& dir)
    : StateBase(hero)
    , mDir(dir) {
    if (obj().footState().isAir() || !Math::EqZero(dir.y)) {
        obj().model().script().start(0x1E);
    } else {
        obj().model().script().start(0x1F);
    }
    obj().model().setFixDir(true);
    if (Math::AbsF32(mDir.x) < 0.1f) {
        obj().model().modelRotCtrl().setRotHTarget(0.0f);
        if (mDir.y > 0.0f) {
            obj().model().modelRotCtrl().setRotDTarget(-50.0f);
        } else {
            obj().model().modelRotCtrl().setRotDTarget(50.0f);
        }
    }
}

StateWaterPistol::~StateWaterPistol() {
    obj().runChecker().cancelContinue();
}

void StateWaterPistol::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (obj().model().scriptTrigger().get(0)) {
        Utility::CreateWaterPistol(obj(), mDir, false);
    }
    if (obj().model().scriptTrigger().get(1)) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateWaterPistol::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateWaterPistol::procFixPos() {}

}}}}  // namespace scn::step::hero::common
