#include "scn/step/boss/goliath/StateRocket.h"

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
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
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

StateRocket::StateRocket(Boss* boss, f32 height, u32 time, bool isOpposite)
    : StateBase(boss), mTime(time), mFrame(0), mStartPos(boss->location().pos()), mGoalPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = isOpposite ? custom.landCtrl().getOppositeWallX() : custom.landCtrl().getFaceToFaceWallX();
    mGoalPos.y = height + custom.landCtrl().getFloorYWithBump();
    obj().target().setIsRightDir(mGoalPos.x > obj().location().pos().x);
    mGoalPos.x -= obj().target().getSign();
    obj().model().reqScript(0x1F);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(static_cast<GuardType>(1));
    Direction3 dir;
    dir.mUp = mGoalPos - mStartPos;
    if (dir.mUp.isZeroLoose(0.00001f)) {
        dir.mUp = Vector3::BASIS_X * obj().target().getSign();
    }
    dir.mUp.normalize();
    dir.restructUpFront();
    Matrix34 mtx(dir, Vector3::ZERO);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx);
}

StateRocket::~StateRocket() {
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().reset();
}

void StateRocket::procAnim() {
    if (mFrame < mTime) {
        mFrame++;
        if (mFrame == mTime) {
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
            Vector3 pos = obj().location().pos();
            pos.y += 1.5f;
            if (!(mGoalPos - mStartPos).isZeroLoose(0.00001f)) {
                pos += (mGoalPos - mStartPos).getNormalized() * 1.25f;
            }
            obj().effect().normal().requestP(static_cast<effect::Kind>(0x283), pos);
        }
    } else {
        obj().brainCtrl().toValid();
    }
}

void StateRocket::procMove() {
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    obj().location().setPos(pos);
}

void StateRocket::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
