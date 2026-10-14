#include "scn/step/boss/hrd3/StateFlyingBodyPressFall.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/PartsCtrl.h"
#include "scn/step/boss/hrd3/StateFlyingBodyPressEnd.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateFlyingBodyPressFall::StateFlyingBodyPressFall(Boss* boss)
    : StateBase(boss), mCount(0), mStartPos(boss->location().pos()) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x1C);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().guard().setType(static_cast<GuardType>(2));
    f32 rot = -custom.partsCtrl().getMaxRotV() * obj().target().getSign();
    obj().model().rotCtrl().initRotV(rot);
}

StateFlyingBodyPressFall::~StateFlyingBodyPressFall() {}

void StateFlyingBodyPressFall::procAnim() {
    const Param& param = obj().param().hrd3();
    if (mCount < param._E4) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateFlyingBodyPressEnd, Boss*>(objPtr());
    }
}

void StateFlyingBodyPressFall::procMove() {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._E4);
    f32 rate = 1.0f - Math::CosDegF(90.0f * t);
    f32 goalY = custom.partsCtrl().getFallOverHeightOffset() + custom.landCtrl().getFloorY();
    Vector3 pos = mStartPos;
    pos.y = Math::LinearInterpolation(mStartPos.y, goalY, rate);
    obj().location().setPos(pos);
}

void StateFlyingBodyPressFall::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
