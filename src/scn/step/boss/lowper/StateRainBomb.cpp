#include "scn/step/boss/lowper/StateRainBomb.h"

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

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateRainBomb::StateRainBomb(Boss* boss, const hel::math::Vector3& pos, u32 frame, u32 interval, u32 count)
    : StateBase(boss), mStartPos(), mGoalPos(), mCount(0), mFrame(frame), mInterval(0), mIntervalFrame(interval), mShotCount(count),
      mIsShotEnd(false), mIsStarted(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mStartPos = custom.waftMoveCtrl().getCenter();
    mGoalPos = obj().basePos().toVector3() + pos;
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.4f);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().model().reqScript(0x12);
}

StateRainBomb::~StateRainBomb() {}

void StateRainBomb::procAnim() {
    if (mIsStarted && mCount < mFrame) {
        mCount++;
    }
    if (obj().scriptTrigger().get(0)) {
        reqBullet();
    }
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0x14);
        mIsShotEnd = true;
        mIsStarted = true;
    }
    if (mShotCount != 0 && mInterval == 0) {
        if (mIsShotEnd == true) {
            obj().model().reqScript(0x13);
            mInterval = mIntervalFrame;
            mIsShotEnd = false;
            mShotCount--;
        }
    } else {
        mInterval--;
    }
    if (mCount == mFrame) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateRainBomb::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, t);
    f32 intervalRate = static_cast<f32>(mInterval) / static_cast<f32>(mIntervalFrame);
    f32 wave = hel::math::Math::AbsF32(hel::math::Math::SinDegF(90.0f * intervalRate));
    f32 offsetY = 1.5f * (wave - 1.0f);
    pos.y += offsetY;
    custom.waftMoveCtrl().setCenter(pos);
}

void StateRainBomb::procFixPos() {}

void StateRainBomb::reqBullet() {
    hel::math::Vector3 pos = obj().location().pos();
    hel::math::Vector3 speed(0.0f, 0.01f, 0.0f);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(1), pos, speed, 0);
}

}
}
}
}
