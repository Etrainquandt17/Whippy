#include "scn/step/boss/lowper/StateMoveToFar.h"

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
#include "scn/step/boss/lowper/StateWaitFar.h"
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

StateMoveToFar::StateMoveToFar(Boss* boss, f32 y)
    : StateBase(boss), mStartPos(), mGoalPos(), mCount(0), mOffset(hel::math::Vector3(0.0f, y, 0.0f)) {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_1);
    mStartPos = obj().location().pos();
    mGoalPos = obj().basePos().toVector3();
    mGoalPos.y += 4.0f;
    mGoalPos.z -= 80.0f;
    mGoalPos += mOffset;
    obj().model().reqScript(0);
    obj().model().rotCtrl().setRotHTarget(180.0f);
}

StateMoveToFar::~StateMoveToFar() {}

void StateMoveToFar::procAnim() {
    mCount++;
    if (mCount == 60) {
        obj().stateChanger().setNextState<StateWaitFar, Boss*>(objPtr());
    }
}

void StateMoveToFar::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / 60.0f;
    hel::math::Vector3 pos;
    f32 sign = mStartPos.x > 0.0f ? 1.0f : -1.0f;
    f32 rateX = t * (-0.3f * hel::math::Math::SinDegF(360.0f * t));
    rateX += t;
    pos.x = mStartPos.x * (1.0f - rateX) + mGoalPos.x * rateX;
    f32 swing = 4.0f * hel::math::Math::SinDegF(180.0f * rateX);
    swing += (1.0f - t) * ((1.0f - t) * ((1.0f - t) * ((1.0f - t) * (3.0f * hel::math::Math::SinDegF(180.0f * t)))));
    swing *= sign;
    pos.x += swing;
    f32 rateY = 0.5f * (1.0f - hel::math::Math::CosDegF(180.0f * t));
    pos.y = mStartPos.y * (1.0f - rateY) + mGoalPos.y * rateY;
    f32 rateZ = 0.5f * (1.0f - hel::math::Math::CosDegF(180.0f * t));
    pos.z = mStartPos.z * (1.0f - rateZ) + mGoalPos.z * rateZ;
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateMoveToFar::procFixPos() {}

}
}
}
}
