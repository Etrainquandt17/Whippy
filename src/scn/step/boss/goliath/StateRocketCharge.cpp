#include "scn/step/boss/goliath/StateRocketCharge.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateRocketCharge::StateRocketCharge(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x21);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_1);
}

StateRocketCharge::~StateRocketCharge() {}

void StateRocketCharge::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateRocketCharge::procMove() {}

void StateRocketCharge::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
