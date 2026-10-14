#include "scn/step/boss/galactaknight/StateSwordBeamAttack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateSwordBeamAttack::StateSwordBeamAttack(Boss* boss, ScriptKind kind) : StateBase(boss), mIsStart(false), mWait(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(kind);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateSwordBeamAttack::~StateSwordBeamAttack() {}

void StateSwordBeamAttack::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mWait != 0) {
        mWait--;
    }
    if (custom.swordBeamCtrl().isEmpty() && obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
    if (obj().scriptTrigger().get(0)) {
        mIsStart = true;
    }
    if (mIsStart && mWait == 0 && !custom.swordBeamCtrl().isEmpty()) {
        custom.swordBeamCtrl().requestOne();
        mWait = 5;
    }
}

void StateSwordBeamAttack::procMove() {}

void StateSwordBeamAttack::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
