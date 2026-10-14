#include "scn/step/boss/lowper/StateBarrierAttack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateBarrierAttack::StateBarrierAttack(Boss* boss) : StateBase(boss), mCount(0), mIsStarted(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x26);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    custom.enemyCtrl().setBarrierAngle(0.0f);
    custom.enemyCtrl().setBarrierRotSpeed(12.0f);
}

StateBarrierAttack::~StateBarrierAttack() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().resetBarrierAngle();
    custom.enemyCtrl().resetBarrierRadius();
    custom.enemyCtrl().resetBarrierRotSpeed();
}

void StateBarrierAttack::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mIsStarted) {
        if (mCount < 120) {
            mCount++;
        } else {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            return;
        }
    }
    if (obj().scriptTrigger().get(0)) {
        mIsStarted = true;
    }
    f32 t = static_cast<f32>(mCount) / 120.0f;
    f32 rate = Math::SinDegF(90.0f * t);
    f32 wave = Math::SinDegF(360.0f * rate);
    f32 radius = 1.5f * (1.0f - Math::SinDegF(180.0f * rate)) + 3.5f * (Math::SinDegF(90.0f * rate) * Math::AbsF32(wave));
    custom.enemyCtrl().setBarrierRadius(radius);
}

void StateBarrierAttack::procMove() {}

void StateBarrierAttack::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
