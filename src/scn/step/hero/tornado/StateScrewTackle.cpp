#include "scn/step/hero/tornado/StateScrewTackle.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/TornadoParam.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace tornado {

namespace {

const f32 GRAVITY_RATE_TABLE[] = { 0.0f, 0.0f, 0.01f };
const f32 ACCEL_V_RATE_TABLE[] = { 1.0f, 0.6f, 0.15f };

}

bool StateScrewTackle::TryToChangeState(Hero* hero, u32 count) {
    if (hero->footState().isAir() && hero->runChecker().isAirContinue() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateScrewTackle, Hero*, u32>(hero, count);
        return true;
    }
    return false;
}

StateScrewTackle::StateScrewTackle(Hero* hero, u32 count)
    : StateBase(hero)
    , mSubState(0)
    , mSpeedV(0.0f)
    , mGravityRate(0.0f)
    , mAccelVRate(1.0f) {
    obj().model().script().start(0x127);
    if (obj().footState().isAir()) {
        int index = hel::math::Math::LimitMinMax<int>(count, 0, 2);
        mGravityRate = GRAVITY_RATE_TABLE[index];
        mAccelVRate = ACCEL_V_RATE_TABLE[index];
    }
    obj().move().resetVelocity();
    obj().footState().setAir();
    obj().invincible().setPerm();
}

StateScrewTackle::~StateScrewTackle() {
    obj().effect()._58.release();
}

void StateScrewTackle::procAnim() {
    if (obj().model().scriptTrigger().get(0)) {
        mSubState = 1;
        const TornadoParam& param = obj().param().tornado();
        obj().move().setSpeedH(param._A8 * obj().model().getSign());
    }
    if (obj().model().scriptTrigger().get(1)) {
        mSubState = 2;
    }
    if (obj().model().isAllEnd()) {
        const TornadoParam& param = obj().param().tornado();
        obj().abilityManager().setActionInterval(param._B4);
        Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    if (mSubState == 1) {
        const TornadoParam& param = obj().param().tornado();
        if (obj().hid().isHold(8)) {
            mSpeedV = param._AC * mAccelVRate;
        } else if (obj().hid().isHold(4)) {
            mSpeedV = -param._AC * mAccelVRate;
        }
        mSpeedV += -param._AC * mGravityRate;
    }
}

void StateScrewTackle::procMove() {
    const TornadoParam& param = obj().param().tornado();
    if (mSubState == 1) {
        f32 speedV = obj().move().velocity().y;
        speedV = hel::math::Math::LimitMinMax(speedV + mSpeedV, -param._B0, param._B0 * mAccelVRate);
        obj().move().setSpeedV(speedV);
        obj().move().airDecelFall(param._B8, gobj::MoveParamFall::Zero());
    } else if (mSubState == 2) {
        obj().move().airDecelFall(param._BC, obj().param().common()._90);
    }
}

void StateScrewTackle::procFixPos() {
}

}
}
}
}
