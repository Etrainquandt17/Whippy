#include "scn/step/boss/goliath/StateWallJump.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateWallWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateWallJump::StateWallJump(Boss* boss, f32 height, u32 time)
    : StateBase(boss), mTime(time), mFrame(0), mStartPos(boss->location().pos()), mRot(0.0f), mRotSpeed(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = custom.landCtrl().getOppositeWallX();
    mGoalPos.y = height + custom.landCtrl().getFloorYWithBump();
    mGoalPos.z = custom.landCtrl().getWallDepth();
    obj().target().setIsRightDir(mGoalPos.x > obj().location().pos().x);
    mGoalPos.x -= obj().target().getSign();
    obj().model().reqScript(0xB);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateWallJump::~StateWallJump() {
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().reset();
}

void StateWallJump::procAnim() {
    if (mFrame < mTime) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateWallWait, Boss*>(objPtr());
        return;
    }
    mRot += mRotSpeed;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (obj().model().anim().currentG3DAnimIndex() == 0xC) {
        mRotSpeed += 4.0f;
        if (mRotSpeed > 30.0f) {
            mRotSpeed = 30.0f;
        }
    }
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(mRot, 0.0f, 0.0f)));
}

void StateWallJump::procMove() {
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.y += 2.0f * Math::SinDegF(180.0f * t);
    obj().location().setPos(pos);
}

void StateWallJump::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
