#include "scn/step/boss/lowper/StateReflectHomingShot.h"

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

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateReflectHomingShot::StateReflectHomingShot(Boss* boss) : StateBase(boss), mCount(0), mPhase(0), _10(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x27);
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
}

StateReflectHomingShot::~StateReflectHomingShot() {
    obj().model().resetScale();
}

void StateReflectHomingShot::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount != 0) {
        mCount--;
        if (mCount == 15) {
            Vector3 center = custom.waftMoveCtrl().getCenter();
            switch (mPhase) {
            case 0: {
                center.x = obj().basePos().x - (center.x - obj().basePos().x);
                center.z = -20.0f;
                break;
            }
            case 1:
                center.x = obj().basePos().x;
                center.z = -60.0f;
                break;
            }
            custom.waftMoveCtrl().setCenter(center);
            mPhase++;
        }
        f32 t = mCount / 30.0f;
        f32 rate = 1.0f - Math::AbsF32(Math::CosDegF(180.0f * t));
        Vector3 scale =
            Math::LinearInterpolation(Vector3::ALL_ONE, Vector3(0.01f, 2.0f, 0.01f), rate);
        obj().model().setScale(scale);
    }
    if (obj().scriptTrigger().get(0)) {
        reqShotBullet();
    }
    if (obj().scriptTrigger().get(1)) {
        mCount = 30;
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWaitFar, Boss*>(objPtr());
    }
}

void StateReflectHomingShot::procMove() {}

void StateReflectHomingShot::procFixPos() {}

void StateReflectHomingShot::reqShotBullet() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(7), obj().location().pos(), Vector3::ZERO, _10);
    _10++;
}

}}}}  // namespace scn::step::boss::lowper
