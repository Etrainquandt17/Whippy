#include "scn/step/boss/goliath/StateFallIcicleBigJumpStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateFallIcicleBigJump.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateFallIcicleBigJumpStart::StateFallIcicleBigJumpStart(Boss* boss, u32 _1) : StateBase(boss), _8(_1) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x28);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateFallIcicleBigJumpStart::~StateFallIcicleBigJumpStart() {}

void StateFallIcicleBigJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFallIcicleBigJump, Boss*, u32>(objPtr(), _8);
    }
}

void StateFallIcicleBigJumpStart::procMove() {}

void StateFallIcicleBigJumpStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
