#include "scn/step/boss/lowper/StateFireTackleStart.h"

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
#include "scn/step/boss/lowper/StateFireTackle.h"
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

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateFireTackleStart::StateFireTackleStart(Boss* boss, u32 frame, u32 _3, bool isEx)
    : StateBase(boss), mFrame(frame), _C(_3), mCount(0), mStartPos(), mGoalPos(), mRotX(0.0f), mRotY(0.0f), mRotSpeed(0.0f),
      mIsEx(isEx) {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_5);
    Utility::ControlHateOnAction(obj());
    hel::geo::Rect rect = obj().comp().mainCamera().getViewRect();
    f32 width = hel::math::Math::AbsF32(rect._C - rect._8);
    f32 sign = hel::math::Math::SignF32(obj().location().pos().x - obj().basePos().x);
    hel::math::Vector3 heroPos = Utility::GetHatedHeroPos(obj());
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
    mRotX = hel::math::Math::LinearInterpolation(mRotX, 90.0f, 0.1f);
    mRotSpeed += 0.5f;
    if (mRotSpeed >= 20.0f) {
        mRotSpeed = 20.0f;
    }
    mRotY += mRotSpeed;
    if (mRotY >= 360.0f) {
        mRotY -= 360.0f;
    }
    g3d::NodeAccessor node = obj().model().model().nodes().at(3);
    node.localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(mRotX, 0.0f, 0.0f)) *
                             hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, mRotY, 0.0f)));
}

void StateFireTackleStart::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    hel::math::Vector3 pos(
        hel::math::Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t * t),
        hel::math::Math::LinearInterpolation(
            mStartPos.y, mGoalPos.y,
            1.0f - (1.0f - hel::math::Math::SinDegF(90.0f * t)) * (1.0f - hel::math::Math::SinDegF(90.0f * t))
        ),
        hel::math::Math::LinearInterpolation(mStartPos.z, mGoalPos.z, t)
    );
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.25f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateFireTackleStart::procFixPos() {}

}
}
}
}
