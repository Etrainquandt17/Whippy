#include "scn/step/hero/stone/StateSlip.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/hero/CameraTarget.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/StateFall.h"
#include "scn/step/hero/stone/StateWait.h"
#include "scn/step/hero/stone/Utility.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace stone {

namespace {

inline const StoneParamSlip& param(Hero& hero) {
    return hero.param().stone()._3C;
}

}

StateSlip::StateSlip(Hero* hero, Context& context)
    : StateBase(hero)
    , mContext(context)
    , mIsRolling(context.isRun()) {
    obj().model().script().start(mContext.isScrew() ? static_cast<ScriptKind>(0xE0) : static_cast<ScriptKind>(0xDF));
    Utility::OnStateStartChange(obj(), mContext);
    obj().cameraTarget().setDependSpeed(true);
}

StateSlip::~StateSlip() {
    Utility::OnStateEndChange(obj());
    if (!isSpeedZero()) {
        Vector3 velocity = obj().move().velocity();
        velocity.setLength(param(obj())._10);
        obj().move().setVelocity(velocity);
    }
}

void StateSlip::procAnim() {
    if (mIsRolling) {
        Utility::UpdateSlipRolling(obj(), mContext);
    }
    if (Utility::ChkCancel(obj())) {
        return;
    }
}

void StateSlip::procMove() {
    if (obj().footState().isAir()) {
        return;
    }
    Utility::ProcMoveChange(obj());
    if (Utility::IsSlope(obj())) {
        mContext.setIsRun(false);
        Vector2 normal = obj().mapColl()._74;
        f32 rate = 1.0f;
        if (!isSpeedZero() && normal.x * obj().move().velocity().x < 0.0f) {
            rate = param(obj())._C;
        }
        gobj::MoveParamAccel accel = param(obj())._0;
        accel._4 *= rate;
        obj().move().groundAccel(normal.x > 0.0f, accel);
    } else {
        Utility::MoveGround(obj(), mContext);
        if (isSpeedZero()) {
            mContext.setIsRun(false);
            obj().stateChanger().setNextState<StateWait, Hero*, std::tr1::reference_wrapper<Context> >(
                objPtr(), std::tr1::ref(mContext));
        }
    }
}

void StateSlip::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
    if (obj().footState().isAir()) {
        obj().move().resetSpeedH();
        obj().stateChanger().setNextState<StateFall, Hero*, std::tr1::reference_wrapper<Context> >(
            objPtr(), std::tr1::ref(mContext));
        return;
    }
    if (mContext.getRotFrame() == mContext.getMaxRotFrame()) {
        f32 speed = obj().move().velocity().x;
        if (!Math::EqZero(speed)) {
            bool isStop = false;
            if (obj().target().isRightDir()) {
                if (obj().mapColl().result().isHitWallFront() && speed > 0.0f) {
                    isStop = true;
                } else if (obj().mapColl().result().isHitWallBack() && speed < 0.0f) {
                    isStop = true;
                }
            } else {
                if (obj().mapColl().result().isHitWallFront() && speed < 0.0f) {
                    isStop = true;
                } else if (obj().mapColl().result().isHitWallBack() && speed > 0.0f) {
                    isStop = true;
                }
            }
            if (isStop) {
                obj().move().setSpeedH(0.0f);
            }
        }
    }
}

bool StateSlip::isSpeedZero() const {
    return Math::EqZero(obj().move().velocity().length());
}

}}}}  // namespace scn::step::hero::stone
