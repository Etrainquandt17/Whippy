#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/boss/goliath/StateEnergyBallThrow.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateLanding.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/goliathenergyball/StateThrow.h"
#include "util/ObjList.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateEnergyBallThrow::StateEnergyBallThrow(Boss* boss, ObjRefHandle<weapon::Weapon> ball, u32 time, f32 speed)
    : StateBase(boss), mTime(time), mFrame(0), mStartPos(boss->location().pos()), mGoalPos(), mSpeed(speed), mBall(ball) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = custom.landCtrl().getCenterX();
    mGoalPos.y = custom.landCtrl().getFloorYWithBump();
    obj().model().reqScript(0x2F);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(static_cast<GuardType>(5));
}

StateEnergyBallThrow::~StateEnergyBallThrow() {}

void StateEnergyBallThrow::procAnim() {
    const Param& param = obj().param().goliath();
    if (mFrame < mTime) {
        mFrame++;
        if (mFrame == param._CC && mBall.isAlive()) {
            mBall->stateChanger().setNextState<weapon::goliathenergyball::StateThrow, weapon::Weapon*>(mBall.operator->());
            mBall->move().setSpeedV(mSpeed);
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        }
    } else {
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
        obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
    }
}

void StateEnergyBallThrow::procMove() {
    const Param& param = obj().param().goliath();
    f32 rateY;
    f32 rateBump;
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    f32 u = 1.0f - Math::CosDegF(90.0f * t);
    rateY = u * u;
    f32 v = 1.0f - Math::SinDegF(180.0f * t);
    rateBump = 1.0f - v * (v * v);
    Vector3 pos;
    pos.x = Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t);
    pos.y = Math::LinearInterpolation(mStartPos.y, mGoalPos.y, rateY) + param._D0 * rateBump;
    pos.z = mStartPos.z;
    obj().location().setPos(pos);
}

void StateEnergyBallThrow::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
