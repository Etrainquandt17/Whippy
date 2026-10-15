#include "scn/step/boss/goliath/StateFallIcicleStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateFallIcicleJump1.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateFallIcicleStart::StateFallIcicleStart(Boss* boss, u32 _1, u32 _2) : StateBase(boss), _8(_1), _C(_2) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x24);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateFallIcicleStart::~StateFallIcicleStart() {}

void StateFallIcicleStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFallIcicleJump1, Boss*, u32, u32>(objPtr(), _8, _C);
    }
}

void StateFallIcicleStart::procMove() {}

void StateFallIcicleStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
