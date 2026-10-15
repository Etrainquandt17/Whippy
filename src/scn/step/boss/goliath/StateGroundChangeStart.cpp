#include "scn/step/boss/goliath/StateGroundChangeStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateGroundChange.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateGroundChangeStart::StateGroundChangeStart(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x16);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_5);
}

StateGroundChangeStart::~StateGroundChangeStart() {}

void StateGroundChangeStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateGroundChange, Boss*>(objPtr());
    }
}

void StateGroundChangeStart::procMove() {}

void StateGroundChangeStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
