#include "scn/step/boss/lowper/StateBombFar.h"

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

StateBombFar::StateBombFar(Boss* boss) : StateBase(boss), mPos(), mCount(0), mIsStarted(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    obj().model().reqScript(0x10);
    mPos = obj().basePos().toVector3();
    mPos.y += 2.0f;
    mPos.z -= 80.0f;
    obj().model().rotCtrl().setRotHTarget(0.0f);
    hel::math::Vector3 center = obj().basePos().toVector3();
    center.y += 2.0f;
    center.z += -80.0f;
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(center);
}

StateBombFar::~StateBombFar() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.dataBuff().clearBombFarBulletData();
}

void StateBombFar::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mIsStarted) {
        mCount++;
    }
    if (obj().scriptTrigger().get(0)) {
        mIsStarted = true;
    }
    if (mIsStarted) {
        u32 count = custom.dataBuff().countBombFarBulletData();
        for (u32 i = 0; i < count; i++) {
            DataBuff::BombFarBulletData data = custom.dataBuff().getBombFarBulletData(i);
            if (mCount == data._4) {
                reqBomb(data._0);
            }
        }
    }
    if (mCount == custom.dataBuff().getMaxIntervalBombFarBulletData() + 60) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateBombFar::procMove() {}

void StateBombFar::procFixPos() {}

void StateBombFar::reqBomb(f32 speedX) {
    hel::math::Vector3 pos = obj().location().pos();
    pos.y += 0.25f;
    hel::math::Vector3 speed(speedX, 0.12f, 0.0f);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(2), pos, speed, 0);
}

}
}
}
}
