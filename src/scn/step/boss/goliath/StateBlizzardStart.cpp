#include "scn/step/boss/goliath/StateBlizzardStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateBlizzardCharge.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateBlizzardStart::StateBlizzardStart(Boss* boss, u32 frame, const BlizzardDesc& desc) : StateBase(boss), mFrame(frame), mDesc(desc) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x19);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_1);
}

StateBlizzardStart::~StateBlizzardStart() {}

void StateBlizzardStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateBlizzardCharge, Boss*, u32, BlizzardDesc>(objPtr(), mFrame, mDesc);
    }
}

void StateBlizzardStart::procMove() {}

void StateBlizzardStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
