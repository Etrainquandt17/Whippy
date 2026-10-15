#include "scn/step/boss/goliath/StateSwoopFall.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateSwoopLanding.h"
#include "scn/step/boss/goliath/StateSwoopRotateLanding.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateSwoopFall::StateSwoopFall(Boss* boss) : StateBase(boss), mFrame(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x10);
    mStartPos = obj().location().pos();
    mGoalPos = obj().location().pos();
    mGoalPos.y = custom.landCtrl().getFloorYWithBump();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_1);
}

StateSwoopFall::~StateSwoopFall() {}

void StateSwoopFall::procAnim() {
    if (mFrame < 4) {
        mFrame++;
    } else if (Utility::IsVariationExtra(obj())) {
        obj().stateChanger().setNextState<StateSwoopRotateLanding, Boss*>(objPtr());
    } else {
        obj().stateChanger().setNextState<StateSwoopLanding, Boss*>(objPtr());
    }
}

void StateSwoopFall::procMove() {
    f32 t = static_cast<f32>(mFrame) / 4.0f;
    obj().location().setPos(Math::LinearInterpolation(mStartPos, mGoalPos, t));
}

void StateSwoopFall::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
