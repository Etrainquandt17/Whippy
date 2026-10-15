#include "scn/step/boss/goliath/StateEnergyBallStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateEnergyBallJump.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateEnergyBallStart::StateEnergyBallStart(Boss* boss, u32 _1, u32 _2, f32 _3) : StateBase(boss), _8(_1), _C(_2), _10(_3) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x1D);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateEnergyBallStart::~StateEnergyBallStart() {}

void StateEnergyBallStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateEnergyBallJump, Boss*, u32, u32, f32>(objPtr(), _8, _C, _10);
    }
}

void StateEnergyBallStart::procMove() {}

void StateEnergyBallStart::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
