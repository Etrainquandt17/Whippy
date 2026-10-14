#include "scn/step/boss/roah/StateZPassThrough.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateZPassThrough::StateZPassThrough(Boss* boss) : StateBase(boss), mCount(0), mStartPos(), mGoalPos() {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().target().setIsRightDir(true);
    obj().model().reqScript(0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    mStartPos = obj().comp().mainCamera().getCenter().toVector3() + Vector3(param.mZPassStartOffset);
    mGoalPos = obj().comp().mainCamera().getCenter().toVector3() + Vector3(param.mZPassGoalOffset);
    obj().location().setPos(mStartPos);
}

StateZPassThrough::~StateZPassThrough() {}

void StateZPassThrough::procAnim() {
    const Param& param = obj().param().roah();
    if (mCount < param.mZPassFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateZPassThrough::procMove() {
    const Param& param = obj().param().roah();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mZPassFrame);
    Vector3 pos;
    pos.x = Math::LinearInterpolation(mStartPos.x, mGoalPos.x, param.mZPassCurve * Math::SinDegF(360.0f * t) + t);
    pos.y = Math::LinearInterpolation(mStartPos.y, mGoalPos.y, t);
    pos.z = Math::LinearInterpolation(mStartPos.z, mGoalPos.z, t - param.mZPassCurve * Math::SinDegF(360.0f * t));
    obj().location().setPos(pos);
    Vector3 dir = obj().location().pos() - obj().location().prevPos();
    if (dir.length() > 0.0f) {
        dir.normalize();
        Direction3 direction;
        direction.mFront = dir;
        direction.restructFrontUp();
        direction.restructFrontLeft();
        // TODO: the two helper objects of restructFrontUp() trade stack slots: the original has its Left at 0x10 and
        // its Up at 0x14, while those of restructFrontLeft() match (Up at 0xC, Left at 0x8).
        Matrix34 mtx(direction, Vector3::ZERO);
        obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx);
    }
}

void StateZPassThrough::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
