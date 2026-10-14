#include "scn/step/boss/fattybuffer/StateStampStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateStampRise.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStampStart::StateStampStart(Boss* boss, bool flag) : StateBase(boss), mFlag(flag) {
    obj().footState().setGround();
    obj().model().reqScript(0xC);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateStampStart::~StateStampStart() {}

void StateStampStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateStampRise, Boss*, bool>(objPtr(), mFlag);
    }
}

void StateStampStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateStampStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
