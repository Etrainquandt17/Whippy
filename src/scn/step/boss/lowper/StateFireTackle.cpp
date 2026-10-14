#include "scn/step/boss/lowper/StateFireTackle.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/EnemyCtrl.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

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

StateFireTackle::StateFireTackle(Boss* boss, u32 frame, bool isEx)
    : StateBase(boss), mCount(0), mFrame(frame), mStartPos(), mGoalPos(), mRotY(0.0f), mIsEx(isEx) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_5);
    Rect rect = obj().comp().mainCamera().getViewRect();
    f32 width = Math::AbsF32(rect._C - rect._8);
    f32 sign = Math::SignF32(obj().location().pos().x - obj().basePos().x);
    mStartPos = obj().location().pos();
    if (mIsEx) {
        mGoalPos.x = obj().basePos().x - sign * param._6C;
    } else {
        mGoalPos.x = obj().basePos().x - sign * (0.5f * width + param._68);
    }
    mGoalPos.y = mStartPos.y;
    obj().model().reqScript(0x1B);
    obj().model().rotCtrl().setRotHTarget(90.0f);
    obj().guard().setType(static_cast<GuardType>(4));
}

StateFireTackle::~StateFireTackle() {
    obj().model().model().nodes().at(3).localMtx().reset();
}

void StateFireTackle::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    mRotY += obj().param().lowper()._64;
    if (mRotY >= 360.0f) {
        mRotY -= 360.0f;
    }
    NodeAccessor node = obj().model().model().nodes().at(3);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(90.0f, 0.0f, 0.0f)) *
                             Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRotY, 0.0f)));
}

void StateFireTackle::procMove() {
    f32 rate = Math::SinDegF(90.0f * (static_cast<f32>(mCount) / static_cast<f32>(mFrame)));
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateFireTackle::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
