#include "scn/step/hero/stone/StateWait.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/StateFall.h"
#include "scn/step/hero/stone/StateSlip.h"
#include "scn/step/hero/stone/Utility.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

StateWait::StateWait(Hero* hero, Context& context)
    : StateBase(hero)
    , mContext(context) {
    obj().model().script().start(context.isScrew() ? static_cast<ScriptKind>(0xDE) : static_cast<ScriptKind>(0xDD));
    Utility::OnStateStartChange(obj(), mContext);
    obj().stateChecker().set_59(true);
    if (!mContext.isRun()) {
        obj().move().resetVelocity();
    }
    obj().stateChecker().setStoneWait(true);
}

StateWait::~StateWait() {
    Utility::OnStateEndChange(obj());
    obj().stateChecker().setStoneWait(false);
}

void StateWait::procAnim() {
    if (Utility::ChkCancel(obj())) {
        return;
    }
}

void StateWait::procMove() {
    Utility::ProcMoveChange(obj());
    Utility::MoveGround(obj(), mContext);
}

void StateWait::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
    if (obj().footState().isAir()) {
        obj().stateChanger().setNextState<StateFall, Hero*, std::tr1::reference_wrapper<Context> >(
            objPtr(), std::tr1::ref(mContext));
    } else if (Utility::IsSlope(obj())) {
        obj().stateChanger().setNextState<StateSlip, Hero*, std::tr1::reference_wrapper<Context> >(
            objPtr(), std::tr1::ref(mContext));
    }
}

}
}
}
}
