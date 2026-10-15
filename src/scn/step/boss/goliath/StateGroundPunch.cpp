#include "scn/step/boss/goliath/StateGroundPunch.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateGroundChangeStart.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateGroundPunch::StateGroundPunch(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x15);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_5);
}

StateGroundPunch::~StateGroundPunch() {}

void StateGroundPunch::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateGroundChangeStart, Boss*>(objPtr());
    }
}

void StateGroundPunch::procMove() {}

void StateGroundPunch::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
