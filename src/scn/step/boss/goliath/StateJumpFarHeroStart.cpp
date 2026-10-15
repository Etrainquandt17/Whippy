#include "scn/step/boss/goliath/StateJumpFarHeroStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateJumpFarHero.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateJumpFarHeroStart::StateJumpFarHeroStart(Boss* boss, u32 _1, f32 _2) : StateBase(boss), _8(_1), _C(_2) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x1D);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateJumpFarHeroStart::~StateJumpFarHeroStart() {}

void StateJumpFarHeroStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJumpFarHero, Boss*, u32, f32>(objPtr(), _8, _C);
    }
}

void StateJumpFarHeroStart::procMove() {}

void StateJumpFarHeroStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
