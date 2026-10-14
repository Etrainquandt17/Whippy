#include "scn/step/boss/galactaknight/StateFlyUpFar.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/CollisionCtrl.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateFlyUpFar::StateFlyUpFar(Boss* boss, f32 height, f32 arc)
    : StateBase(boss), mCount(0), mStartPos(boss->location().pos()), mGoalPos(), mDir(Direction3::BASIS), mHeight(height),
      mArc(arc) {
    const Param& param = obj().param().galactaknight();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = custom.landCtrl().getCenterX();
    mGoalPos.y = height + custom.landCtrl().getFloorY();
    mGoalPos.z = param._E8;
    obj().target().setIsRightDir(mStartPos.x < mGoalPos.x);
    mDir.mFront = Vector3::BASIS_X * obj().target().getSign();
    mDir.restructFrontUp();
    obj().model().reqScript(0xB);
    obj().soundSE().normal().start(0x39D);
    obj().model().rotCtrl().initRotH(0.0f);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().worldCage().setIsValid(false);
}

StateFlyUpFar::~StateFlyUpFar() {
    obj().worldCage().setIsValid(true);
    obj().model().model().nodes().at(1).localMtx().reset();
}

void StateFlyUpFar::procAnim() {
    const Param& param = obj().param().galactaknight();
    if (mCount < param._E4) {
        mCount++;
    } else {
        obj().brainCtrl().toValid();
    }
}

void StateFlyUpFar::procMove() {
    const Param& param = obj().param().galactaknight();
    Vector3 prevPos = obj().location().pos();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._E4);
    f32 rateZ = Math::SinDegF(90.0f * t);
    f32 cos = Math::CosDegF(90.0f * t);
    f32 rate = 1.0f - cos;
    Vector3 pos;
    pos.x = Math::LinearInterpolation(mStartPos.x, mGoalPos.x, Math::InterpolationParamMinToMin(rate));
    f32 y = Math::LinearInterpolation(mStartPos.y, mGoalPos.y, Math::InterpolationParamMinToMin(rate));
    pos.y = mArc * Math::SinDegF(180.0f * rate) + y;
    pos.z = Math::LinearInterpolation(mStartPos.z, mGoalPos.z, rateZ);
    obj().location().setPos(pos);
    Vector3 diff = pos - prevPos;
    Vector3 up = Vector3::BASIS_Y;
    if (!diff.isZeroLoose(0.00001f)) {
        diff.z *= 0.4f;
        diff.normalize();
        mDir.mFront = mDir.mFront.slerp(diff, 0.1f);
        mDir.restructFrontUp();
        f32 deg = Math::LinearInterpolation(60.0f, -180.0f, rate);
        up.rotate(mDir.mFront, 0.017453292f * deg);
    } else {
        mDir.mFront = Vector3::BASIS_Y;
        up = -Vector3::BASIS_Z;
    }
    mDir.mUp = mDir.mUp.slerp(up, 0.1f);
    mDir.restructUpFront();
    Matrix34 mtx(mDir, Vector3::ZERO);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx);
}

void StateFlyUpFar::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
