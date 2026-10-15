#include "scn/step/boss/goliath/StateRocketAttack.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateRocketEnd.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateRocketAttack::StateRocketAttack(Boss* boss, f32 x, u32 time, bool isLast)
    : StateBase(boss), mTime(time), mFrame(0), mStartPos(boss->location().pos()), mGoalPos(), mIsLast(isLast) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (isLast) {
        Utility::ControlHateOnAction(obj());
    }
    mGoalPos.x = x;
    mGoalPos.y = custom.landCtrl().getFloorYWithBump();
    mGoalPos.x = custom.landCtrl().getAdjustX(mGoalPos.x, 2.0f);
    obj().target().setIsRightDir(mGoalPos.x > obj().location().pos().x);
    obj().model().reqScript(0x1F);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(static_cast<GuardType>(1));
    Direction3 dir;
    dir.mUp = mGoalPos - mStartPos;
    if (dir.mUp.isZeroLoose(0.00001f)) {
        dir.mUp = -Vector3::BASIS_Y;
    }
    dir.mUp.normalize();
    dir.restructUpFront();
    Matrix34 mtx(dir, Vector3::ZERO);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx);
}

StateRocketAttack::~StateRocketAttack() {
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().reset();
}

void StateRocketAttack::procAnim() {
    if (mFrame < mTime) {
        mFrame++;
    } else {
        if (!obj().brainCtrl().isValid()) {
            if (mIsLast) {
                obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
            } else {
                obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
            }
            Vector3 pos = obj().location().pos();
            pos.y += 1.5f;
            if (!(mGoalPos - mStartPos).isZeroLoose(0.00001f)) {
                pos += (mGoalPos - mStartPos).getNormalized() * 1.25f;
            }
            obj().effect().normal().requestP(static_cast<effect::Kind>(0x283), pos);
            obj().soundSE().normal().start(0x376);
        }
        if (mIsLast) {
            obj().stateChanger().setNextState<StateRocketEnd, Boss*>(objPtr());
        } else {
            obj().brainCtrl().toValid();
        }
    }
}

void StateRocketAttack::procMove() {
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    obj().location().setPos(pos);
}

void StateRocketAttack::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
