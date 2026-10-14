#include "scn/step/boss/galactaknight/StateSpinAttackCharge.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/StateSpinAttack.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateSpinAttackCharge::StateSpinAttackCharge(Boss* boss, u32 frame, f32 distance, u32 count)
    : StateBase(boss), mFrame(frame), mIsStart(false), mDistance(distance), mCount(count) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().guard().setType(static_cast<GuardType>(1));
    obj().model().reqScript(0x19);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateSpinAttackCharge::~StateSpinAttackCharge() {
    obj().soundSE().loop().stop();
}

void StateSpinAttackCharge::procAnim() {
    const Param& param = obj().param().galactaknight();
    if (obj().scriptTrigger().get(0)) {
        mIsStart = true;
        obj().model().rotCtrl().setRotHIntpRate(param._BC);
    }
    if (mIsStart) {
        if (mFrame > param._B8) {
            Utility::TurnHatedHero(obj());
        }
        if (mFrame != 0) {
            mFrame--;
        } else {
            obj().stateChanger().setNextState<StateSpinAttack, Boss*, f32, u32>(objPtr(), mDistance, mCount);
        }
    }
}

void StateSpinAttackCharge::procMove() {}

void StateSpinAttackCharge::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
