#include "scn/step/boss/lowper/StateBarrierAttack.h"

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

StateBarrierAttack::StateBarrierAttack(Boss* boss) : StateBase(boss), mCount(0), mIsStarted(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().model().reqScript(0x26);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    custom.enemyCtrl().setBarrierAngle(0.0f);
    custom.enemyCtrl().setBarrierRotSpeed(12.0f);
}

StateBarrierAttack::~StateBarrierAttack() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().resetBarrierAngle();
    custom.enemyCtrl().resetBarrierRadius();
    custom.enemyCtrl().resetBarrierRotSpeed();
}

void StateBarrierAttack::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mIsStarted) {
        if (mCount < 120) {
            mCount++;
        } else {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            return;
        }
    }
    if (obj().scriptTrigger().get(0)) {
        mIsStarted = true;
    }
    f32 t = static_cast<f32>(mCount) / 120.0f;
    f32 rate = hel::math::Math::SinDegF(90.0f * t);
    f32 wave = hel::math::Math::SinDegF(360.0f * rate);
    f32 radius = 1.5f * (1.0f - hel::math::Math::SinDegF(180.0f * rate)) + 3.5f * (hel::math::Math::SinDegF(90.0f * rate) * hel::math::Math::AbsF32(wave));
    custom.enemyCtrl().setBarrierRadius(radius);
}

void StateBarrierAttack::procMove() {}

void StateBarrierAttack::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
