#include "scn/step/hero/stone/StateLanding.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/StateEnd.h"
#include "scn/step/hero/stone/StateFall.h"
#include "scn/step/hero/stone/StateSlip.h"
#include "scn/step/hero/stone/StateWait.h"
#include "scn/step/hero/stone/Utility.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

StateLanding::StateLanding(Hero* hero, Context& context)
    : StateBase(hero)
    , mContext(context)
    , mFrame(0)
    , mIsCancel(false) {
    obj().model().script().start(context.isScrew() ? static_cast<ScriptKind>(0xDC) : static_cast<ScriptKind>(0xDB));
    Utility::OnStateStartChange(obj(), mContext);
    if (!mContext.isRun()) {
        obj().move().resetVelocity();
    }
}

StateLanding::~StateLanding() {
    Utility::OnStateEndChange(obj());
}

void StateLanding::procAnim() {
    mFrame++;
    if (!mIsCancel && obj().hid().isTrigger(0x20)) {
        mIsCancel = true;
    }
    if (mFrame > obj().param().stone()._38) {
        if (mIsCancel) {
            obj().stateChanger().setNextState<StateEnd, Hero*>(objPtr());
        } else if (mContext.isRun()) {
            obj().stateChanger().setNextState<StateSlip, Hero*, std::tr1::reference_wrapper<Context> >(
                objPtr(), std::tr1::ref(mContext));
        } else {
            obj().stateChanger().setNextState<StateWait, Hero*, std::tr1::reference_wrapper<Context> >(
                objPtr(), std::tr1::ref(mContext));
        }
    }
}

void StateLanding::procMove() {
    Utility::ProcMoveChange(obj());
    Utility::MoveGround(obj(), mContext);
}

void StateLanding::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
    if (obj().footState().isAir()) {
        obj().stateChanger().setNextState<StateFall, Hero*, std::tr1::reference_wrapper<Context> >(
            objPtr(), std::tr1::ref(mContext));
    }
}

}}}}  // namespace scn::step::hero::stone
