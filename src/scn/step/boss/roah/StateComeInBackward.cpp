#include "scn/step/boss/roah/StateComeInBackward.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateComeInBackward::StateComeInBackward(Boss* boss, Config config)
    : StateBase(boss), mCount(0), mStartPos(), mGoalPos(), mConfig(config) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().target().setIsRightDir(true);
    obj().model().reqScript(0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    mStartPos = obj().location().pos().getXY();
    mGoalPos = mConfig._4 + obj().comp().mainCamera().getCenter();
}

StateComeInBackward::~StateComeInBackward() {}

void StateComeInBackward::procAnim() {
    if (mCount < mConfig._0) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateComeInBackward::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mConfig._0);
    f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
    obj().location().setPos(hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateComeInBackward::procFixPos() {}

}
}
}
}
