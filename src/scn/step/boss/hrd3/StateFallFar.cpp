#include "scn/step/boss/hrd3/StateFallFar.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateFallFar::StateFallFar(Boss* boss, u32 frame, const Vector3& pos)
    : StateBase(boss), mCount(0), mFrame(frame), mStartPos(boss->location().pos()), mGoalY(pos.y) {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mStartPos.x = pos.x;
    mStartPos.y = param._100;
    mStartPos.z = pos.z;
    obj().model().reqScript(0x1E);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateFallFar::~StateFallFar() {}

void StateFallFar::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().brainCtrl().toValid();
    }
}

void StateFallFar::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = Math::SinDegF(90.0f * t);
    Vector3 pos = mStartPos;
    pos.y = Math::LinearInterpolation(mStartPos.y, mGoalY, rate);
    obj().location().setPos(pos);
}

void StateFallFar::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
