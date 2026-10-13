#include "scn/step/hero/stone/StateFallScrewStart.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/StateFall.h"
#include "scn/step/hero/stone/Utility.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

namespace {

inline const StoneParamFallScrewStart& param(Hero& hero) {
    return hero.param().stone()._1C;
}

}

StateFallScrewStart::StateFallScrewStart(Hero* hero, Context& context)
    : StateBase(hero)
    , mContext(context)
    , mFrame(0) {
    obj().model().script().start(0xD9);
    Utility::OnStateStartChange(obj(), mContext);
    obj().move().setSpeedV(param(obj())._0);
}

StateFallScrewStart::~StateFallScrewStart() {
    Utility::OnStateEndChange(obj());
}

void StateFallScrewStart::procAnim() {
    mFrame++;
    if (mFrame == param(obj())._8) {
        obj().move().resetSpeedV();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFall, Hero*, std::tr1::reference_wrapper<Context> >(
            objPtr(), std::tr1::ref(mContext));
    }
}

void StateFallScrewStart::procMove() {
    Utility::ProcMoveChange(obj());
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(param(obj())._4);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateFallScrewStart::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
