#include "scn/step/boss/hrd3/StateMoveFar.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
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

StateMoveFar::StateMoveFar(Boss* boss, u32 frame, const Vector3& pos)
    : StateBase(boss), mCount(0), mFrame(frame), mStartPos(boss->location().pos()), mGoalPos(pos) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    obj().target().setIsRightDir(false);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateMoveFar::~StateMoveFar() {}

void StateMoveFar::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().brainCtrl().toValid();
    }
}

void StateMoveFar::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = Math::SinDegF(90.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    obj().location().setPos(pos);
}

void StateMoveFar::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
