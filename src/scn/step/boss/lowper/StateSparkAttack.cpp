#include "scn/step/boss/lowper/StateSparkAttack.h"

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
#include "scn/step/boss/DamageFlash.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
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
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/sfx/Manager.h"
#include "scn/step/sfx/ReverseWorld.h"
#include "scn/step/sfx/ScreenFade.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateSparkAttack::StateSparkAttack(Boss* boss, u32 frame)
    : StateBase(boss), mCount(0), mFrame(frame), mStartPos(), mGoalPos(), mIsAttack(false), mInterval(0), mIntervalFrame(0) {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_1);
    hel::geo::Rect rect = obj().comp().mainCamera().getViewRect();
    f32 width = hel::math::Math::AbsF32(rect._C - rect._8);
    f32 sign = hel::math::Math::SignF32(obj().location().pos().x - obj().basePos().x);
    mStartPos = obj().location().pos();
    mGoalPos.x = obj().basePos().x - sign * (0.5f * width - 0.5f);
    mGoalPos.y = mStartPos.y;
    obj().model().reqScript(0x1D);
    obj().guard().setType(static_cast<GuardType>(1));
    mIntervalFrame = mFrame / 7.0f;
    obj().objColl().setAttackType(1, static_cast<ocoll::AttackType>(0x1BE));
}

StateSparkAttack::~StateSparkAttack() {
    obj().objColl().clearAttack(1);
    obj().soundSE().loop().stop();
}

void StateSparkAttack::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (mInterval != 0) {
        mInterval--;
        return;
    }
    mInterval = mIntervalFrame;
    mIsAttack = !mIsAttack;
    if (mIsAttack) {
        obj().objColl().clearAttack(1);
        obj().objColl().addAttack(1, 0, 0.7f, hel::math::Vector2(0.0f, 0.65f));
        obj().objColl().addAttack(1, 0, 0.3f, hel::math::Vector2(0.0f, 7.0f), hel::math::Vector2(0.0f, -7.0f));
        obj().effect().state().release();
        obj().effect().state().requestN(static_cast<effect::Kind>(0x3A0), 3);
        obj().effect().state().requestN(static_cast<effect::Kind>(0x39F), 3);
        obj().effect().state().requestN(static_cast<effect::Kind>(0x39E), 3);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        obj().soundSE().loop().start(0x1B2);
        obj().soundSE().normal().start(0x574);
    } else {
        obj().objColl().clearAttack(1);
        obj().objColl().addAttack(1, 0, 0.7f, hel::math::Vector2(0.0f, 0.65f));
        obj().effect().state().release();
        obj().effect().state().requestN(static_cast<effect::Kind>(0x39E), 3);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
        obj().soundSE().loop().stop();
    }
}

void StateSparkAttack::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, t);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateSparkAttack::procFixPos() {}

}
}
}
}
