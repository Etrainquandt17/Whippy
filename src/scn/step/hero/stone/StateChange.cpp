#include "scn/step/hero/stone/StateChange.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/StateFall.h"
#include "scn/step/hero/stone/StateFallScrewStart.h"
#include "scn/step/hero/stone/StateSlip.h"
#include "scn/step/hero/stone/Utility.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

bool StateChange::ChkChangeStateScrew(Hero* hero) {
    if (hero->footState().isGround()) {
        return false;
    }
    if (hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        return true;
    }
    return false;
}

void StateChange::ChangeStateNoScrew(Hero* hero, Context& context) {
    context.setIsScrew(false);
    hero->stateChanger().setNextState<StateChange, Hero*, std::tr1::reference_wrapper<Context> >(
        hero, std::tr1::ref(context));
}

StateChange::StateChange(Hero* hero, Context& context)
    : StateBase(hero)
    , mContext(context)
    , _C(false) {
    obj().piggyback().unlinkAll();
    if (obj().footState().isGround() && obj().runChecker().isGroundContinue()) {
        obj().stateChecker().setRun(true);
    } else {
        obj().stateChecker().setRun(false);
    }
    obj().model().script().start(mContext.isScrew() ? static_cast<ScriptKind>(0xD7) : static_cast<ScriptKind>(0xD6));
    Utility::OnStateStartChange(obj(), mContext);
    obj().move().resetSpeedV();
    if (obj().footState().isAir() && obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
}

StateChange::~StateChange() {
    obj().invincible().clear();
    Utility::OnStateEndChange(obj());
    obj().stateChecker().setRun(false);
}

void StateChange::procAnim() {
    if (obj().model().scriptTrigger().get(0)) {
        Utility::InitRotH(obj(), mContext);
    }
    if (mContext.isRun()) {
        Utility::UpdateSlipRolling(obj(), mContext);
    }
    if (obj().model().isAllEnd()) {
        if (mContext.isScrew()) {
            obj().stateChanger().setNextState<StateFallScrewStart, Hero*, std::tr1::reference_wrapper<Context> >(
                objPtr(), std::tr1::ref(mContext));
        } else if (mContext.isRun()) {
            obj().stateChanger().setNextState<StateSlip, Hero*, std::tr1::reference_wrapper<Context> >(
                objPtr(), std::tr1::ref(mContext));
        } else {
            obj().stateChanger().setNextState<StateFall, Hero*, std::tr1::reference_wrapper<Context> >(
                objPtr(), std::tr1::ref(mContext));
        }
    }
}

void StateChange::procMove() {
    f32 decel = obj().param().stone()._18;
    if (obj().footState().isGround()) {
        if (mContext.isRun()) {
            decel = 0.0f;
        }
        obj().move().groundDecel(gobj::MoveParamDecel::Create(decel));
    } else {
        obj().move().airDecelFall(gobj::MoveParamDecel::Create(decel), gobj::MoveParamFall::Zero());
    }
}

void StateChange::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
    if (obj().footState().isGround() && obj().stateChecker().isRun()) {
        mContext.setIsRun(true);
    }
}

}}}}  // namespace scn::step::hero::stone
