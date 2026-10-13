#include "scn/step/hero/stone/StateFall.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/LogoutController.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/StateEnd.h"
#include "scn/step/hero/stone/StateLanding.h"
#include "scn/step/hero/stone/Utility.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

namespace {

inline const StoneParamFall& param(Hero& hero) {
    return hero.param().stone()._28;
}

}

StateFall::StateFall(Hero* hero, Context& context)
    : StateBase(hero)
    , mContext(context)
    , mFrame(0) {
    obj().model().script().start(context.isScrew() ? 0xDA : 0xD8);
    Utility::OnStateStartChange(obj(), mContext);
    mContext.setRotEnable(false);
}

StateFall::~StateFall() {
    Utility::OnStateEndChange(obj());
}

void StateFall::procAnim() {
    mFrame++;
    if (!mContext.isScrew() && obj().hid().isTrigger(0x20)) {
        obj().stateChanger().setNextState<StateEnd, Hero*>(objPtr());
        return;
    }
    if (mContext.isScrew() && mFrame >= param(obj())._C && obj().hid().isTrigger(0x20)) {
        obj().stateChanger().setNextState<StateEnd, Hero*>(objPtr());
        return;
    }
    if (obj().logoutController().isLogoutForce()) {
        obj().stateChanger().setNextState<StateEnd, Hero*>(objPtr());
    }
}

void StateFall::procMove() {
    Utility::ProcMoveChange(obj());
    f32 speed = mContext.isScrew() ? param(obj())._4 : param(obj())._0;
    f32 decel = param(obj())._8;
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(speed, speed, speed);
    if (mContext.isRun()) {
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), fall);
    } else {
        obj().move().airDecelFall(gobj::MoveParamDecel::Create(decel), fall);
    }
}

void StateFall::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

bool StateFall::procObjCollReact() {
    if (!obj().objColl().objColl().attack().isCollideGimmick() && obj().footState().isGround()) {
        obj().stateChanger().setNextState<StateLanding, Hero*, std::tr1::reference_wrapper<Context> >(
            objPtr(), std::tr1::ref(mContext));
        return true;
    }
    return false;
}

}
}
}
}
