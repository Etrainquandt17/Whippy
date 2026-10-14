#include "scn/step/boss/lowper/StateFireTackleStart.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "pow.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateFireTackle.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateFireTackleStart::StateFireTackleStart(Boss* boss, u32 frame, u32 _3, bool isEx)
    : StateBase(boss), mFrame(frame), _C(_3), mCount(0), mStartPos(), mGoalPos(), mRotX(0.0f), mRotY(0.0f), mRotSpeed(0.0f),
      mIsEx(isEx) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_FIRE_TACKLE);
    Utility::ControlHateOnAction(obj());
    Rect rect = obj().comp().mainCamera().getViewRect();
    f32 width = Math::AbsF32(rect._C - rect._8);
    f32 sign = Math::SignF32(obj().location().pos().x - obj().basePos().x);
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    mStartPos = obj().location().pos();
    mGoalPos.x = obj().basePos().x + sign * (0.5f * width + 3.5f);
    mGoalPos.y = heroPos.y;
    if (mGoalPos.y < obj().basePos().y) {
        mGoalPos.y = obj().basePos().y;
    }
    obj().model().reqScript(0x1A);
    obj().model().rotCtrl().setRotHTarget(90.0f);
    obj().guard().setType(static_cast<GuardType>(4));
}

StateFireTackleStart::~StateFireTackleStart() {
    obj().model().model().nodes().at(3).localMtx().reset();
}

void StateFireTackleStart::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateFireTackle, Boss*, unsigned long, bool>(objPtr(), _C, mIsEx);
    }
    mRotX = Math::LinearInterpolation(mRotX, 90.0f, 0.1f);
    mRotSpeed += 0.5f;
    if (mRotSpeed >= 20.0f) {
        mRotSpeed = 20.0f;
    }
    mRotY += mRotSpeed;
    if (mRotY >= 360.0f) {
        mRotY -= 360.0f;
    }
    NodeAccessor node = obj().model().model().nodes().at(3);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(mRotX, 0.0f, 0.0f)) *
                             Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRotY, 0.0f)));
}

void StateFireTackleStart::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    Vector3 pos(
        Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t * t),
        Math::LinearInterpolation(mStartPos.y, mGoalPos.y, 1.0f - POW2(1.0f - Math::SinDegF(90.0f * t))),
        Math::LinearInterpolation(mStartPos.z, mGoalPos.z, t)
    );
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.25f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateFireTackleStart::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
