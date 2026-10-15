#include "scn/step/boss/goliath/StateSwoopStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateSwoopRise.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateSwoopStart::StateSwoopStart(Boss* boss, u32 _1, u32 _2) : StateBase(boss), _8(_1), _C(_2) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0xE);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_1);
}

StateSwoopStart::~StateSwoopStart() {}

void StateSwoopStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateSwoopRise, Boss*, u32, u32>(objPtr(), _8, _C);
    }
}

void StateSwoopStart::procMove() {}

void StateSwoopStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
