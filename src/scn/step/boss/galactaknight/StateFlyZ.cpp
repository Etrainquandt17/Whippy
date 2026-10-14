#include "scn/step/boss/galactaknight/StateFlyZ.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/CollisionCtrl.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateStep.h"
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

StateFlyZ::StateFlyZ(Boss* boss, f32 margin)
    : StateBase(boss), mCount(0), mStartPos(boss->location().pos()), mGoalPos(), mSign(1.0f), mDir(Direction3::BASIS) {
    const Param& param = obj().param().galactaknight();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = custom.landCtrl().getFarEdgeX(margin);
    mGoalPos.y = param._D0 + custom.landCtrl().getFloorY();
    mSign = mStartPos.x < mGoalPos.x ? 1.0f : -1.0f;
    mDir.mFront = Vector3::BASIS_X * mSign;
    mDir.restructFrontUp();
    obj().target().setIsRightDir(mSign < 0.0f);
    obj().model().reqScript(0xB);
    obj().soundSE().normal().start(0x39E);
    obj().model().rotCtrl().initRotH(0.0f);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().worldCage().setIsValid(false);
}

StateFlyZ::~StateFlyZ() {
    obj().worldCage().setIsValid(true);
    obj().model().model().nodes().at(1).localMtx().reset();
}

void StateFlyZ::procAnim() {
    const Param& param = obj().param().galactaknight();
    if (mCount < param._C8) {
        mCount++;
    } else {
        obj().model().rotCtrl().setRotH(param._D4);
        obj().stateChanger().setNextState<StateStep, Boss*, ScriptKind, f32, f32, unsigned long>(
            objPtr(), static_cast<ScriptKind>(3), 0.0f, param._E0, param._CC
        );
    }
}

void StateFlyZ::procMove() {
    const Param& param = obj().param().galactaknight();
    Vector3 prevPos = obj().location().pos();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._C8);
    f32 sin = Math::SinDegF(90.0f * t);
    f32 cos = Math::CosDegF(90.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.x += -0.15f * ((mGoalPos.x - mStartPos.x) * Math::SinDegF(360.0f * t));
    pos.y += param._D8 * (sin * Math::CosDegF(270.0f * sin));
    pos.z += param._DC * (sin * Math::CosDegF(270.0f * sin));
    obj().location().setPos(pos);
    Vector3 diff = pos - prevPos;
    if (!diff.isZeroLoose(0.00001f)) {
        diff.normalize();
        mDir.mFront = mDir.mFront.slerp(diff, 0.1f);
        mDir.restructFrontUp();
    }
    f32 roll = 0.5f * (32.0f * mSign) * (1.0f + Math::CosDegF(360.0f * t));
    mDir.mUp.rotate(mDir.mFront, 0.017453292f * roll);
    mDir.restructUpFront();
    if (mDir.mFront.z < 0.0f) {
        f32 r = 1.0f - cos;
        f32 rate = r * (r * r);
        mDir.mUp = mDir.mUp.slerp(Vector3::BASIS_Y, rate);
        mDir.mUp.normalize();
        mDir.restructUpLeft();
        rate *= rate;
        Vector3 front = Vector3::BASIS_Z;
        front.rotate(Vector3::AXIS_Y, -mSign * (0.017453292f * param._D4));
        mDir.mFront = mDir.mFront.slerp(front, rate);
        mDir.mFront.normalize();
        mDir.restructFrontUp();
    }
    Matrix34 mtx(mDir, Vector3::ZERO);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx);
}

void StateFlyZ::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
