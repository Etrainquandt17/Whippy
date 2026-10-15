#include "scn/step/boss/goliath/StateFallIcicleJump2Start.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateFallIcicleJump2.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateFallIcicleJump2Start::StateFallIcicleJump2Start(Boss* boss, u32 _1, u32 _2) : StateBase(boss), _8(_1), _C(_2) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x26);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    custom.icicleCtrl().startRequest();
}

StateFallIcicleJump2Start::~StateFallIcicleJump2Start() {}

void StateFallIcicleJump2Start::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.icicleCtrl().updateRequest();
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFallIcicleJump2, Boss*, u32, u32>(objPtr(), _8, _C);
    }
}

void StateFallIcicleJump2Start::procMove() {}

void StateFallIcicleJump2Start::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
