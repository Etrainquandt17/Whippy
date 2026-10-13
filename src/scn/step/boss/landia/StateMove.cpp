#include "scn/step/boss/landia/StateMove.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/StateWait.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateMove::StateMove(Boss* boss, Config config) : StateBase(boss), mCount(0), mStartPos(), mGoalPos(), mConfig(config) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetVelocity();
    mStartPos = custom.waftCtrl().getRefPos().getXY();
    mGoalPos = obj().comp().mainCamera().getCenter();
    mGoalPos.x += mConfig._4.x * obj().target().getSign();
    mGoalPos.y += mConfig._4.y;
}

StateMove::~StateMove() {}

void StateMove::procAnim() {
    if (mCount < mConfig._0) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateMove::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mConfig._0);
    f32 rate = hel::math::Math::SinDegF(90.0f * t);
    custom.waftCtrl().setRefPos(hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateMove::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
