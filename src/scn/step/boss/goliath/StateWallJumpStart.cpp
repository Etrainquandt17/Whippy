#include "scn/step/boss/goliath/StateWallJumpStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateWallJump.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateWallJumpStart::StateWallJumpStart(Boss* boss, f32 _1, u32 _2) : StateBase(boss), _8(_1), _C(_2) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0xA);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateWallJumpStart::~StateWallJumpStart() {}

void StateWallJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWallJump, Boss*, f32, u32>(objPtr(), _8, _C);
    }
}

void StateWallJumpStart::procMove() {}

void StateWallJumpStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
