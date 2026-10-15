#include "scn/step/boss/goliath/StateWallJumpFarHeroStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateWallJumpFarHero.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateWallJumpFarHeroStart::StateWallJumpFarHeroStart(Boss* boss, f32 _1, u32 _2) : StateBase(boss), _8(_1), _C(_2) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0xA);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateWallJumpFarHeroStart::~StateWallJumpFarHeroStart() {}

void StateWallJumpFarHeroStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWallJumpFarHero, Boss*, f32, u32>(objPtr(), _8, _C);
    }
}

void StateWallJumpFarHeroStart::procMove() {}

void StateWallJumpFarHeroStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
