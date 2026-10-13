#include "scn/step/hero/stone/StateStartJump.h"
#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/StateChange.h"
#include "scn/step/hero/stone/Utility.h"
#include "std/tr1/reference_wrapper.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

bool StateStartJump::ChkChangeState(Hero* hero) {
    return hero->hid().isTrigger(0x20);
}

StateStartJump::StateStartJump(Hero* hero, Context& context)
    : StateBase(hero)
    , mContext(context) {
    obj().model().script().start(0xD5);
    if (!mContext.isRun()) {
        obj().move().setSpeedV(obj().param().stone()._14);
        obj().footState().setAir();
    }
    if (obj().footState().isAir() && obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().objColl().setXlu();
    int max = obj().param().stone()._C;
    int min = obj().param().stone()._8;
    u32 frame = min + app::Random::Rand(max - min);
    mContext.setMaxRotFrame(frame);
}

StateStartJump::~StateStartJump() {
    obj().objColl().unsetXlu();
}

void StateStartJump::procAnim() {
    if (mContext.isRun()) {
        Utility::UpdateSlipRolling(obj(), mContext);
    }
    if (obj().model().isAllEnd()) {
        StateChange::ChangeStateNoScrew(objPtr(), std::tr1::ref(mContext));
    }
}

void StateStartJump::procMove() {
    if (mContext.isRun()) {
        if (obj().footState().isGround()) {
            obj().move().groundDecel(gobj::MoveParamDecel::Zero());
        } else {
            hero::Utility::MoveDefaultBrake(obj());
        }
    } else {
        hero::Utility::MoveDefaultAction(obj());
    }
}

void StateStartJump::procFixPos() {
    if (obj().stateChecker().isRun()) {
        hero::Utility::MapCollReactDefaultAction(obj());
        if (obj().footState().isGround()) {
            mContext.setIsRun(true);
        }
    }
}

}}}}  // namespace scn::step::hero::stone
