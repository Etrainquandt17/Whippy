#include "scn/step/boss/metalgeneral/StateCirclingFlightEnd.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateFall.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateCirclingFlightEnd::StateCirclingFlightEnd(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x1D);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateCirclingFlightEnd::~StateCirclingFlightEnd() {}

void StateCirclingFlightEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFall, Boss*>(objPtr());
    }
}

void StateCirclingFlightEnd::procMove() {
    const Param& param = obj().param().metalgeneral();
    obj().move().decel(param._20);
}

void StateCirclingFlightEnd::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
