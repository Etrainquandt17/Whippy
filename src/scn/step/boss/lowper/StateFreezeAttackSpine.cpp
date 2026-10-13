#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/boss/lowper/StateFreezeAttackSpine.h"

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
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

namespace {

const f32 T_SPINE_ANGLE_TABLE[] = { 65.0f, 115.0f, 245.0f, 295.0f };

}

StateFreezeAttackSpine::StateFreezeAttackSpine(Boss* boss, u32 frame) : StateBase(boss), mFrame(frame), mCount(0), mWeapons() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().model().reqScript(0x1F);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    obj().guard().setType(static_cast<GuardType>(4));
    reqIceSpine();
}

StateFreezeAttackSpine::~StateFreezeAttackSpine() {
    obj().objColl().clearAttack(1);
}

void StateFreezeAttackSpine::procAnim() {
    if (mCount < mFrame) {
        mCount++;
        if (mCount == mFrame) {
            obj().objColl().clearAttack(1);
            obj().model().reqScript(0x23);
        }
    } else {
        if (obj().scriptTrigger().get(2)) {
            shotIceSpine();
        }
        if (obj().model().isAllEnd()) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        }
    }
}

void StateFreezeAttackSpine::procMove() {}

void StateFreezeAttackSpine::procFixPos() {}

void StateFreezeAttackSpine::reqIceSpine() {
    hel::math::Vector3 pos = obj().location().pos();
    pos.y += 0.5f;
    f32 speed = 0.03f;
    weapon::Desc desc(static_cast<weapon::Kind>(0x83), 0, static_cast<ostop::Flag>(8), pos.getXY(), hel::math::Vector2::ZERO,
                      obj().objColl().owner());
    for (int i = 0; i < 4; i++) {
        hel::math::Vector2 dir(0.0f, 1.0f);
        dir.rotate(0.017453292f * T_SPINE_ANGLE_TABLE[i]);
        desc._1c = dir * speed;
        mWeapons[i] = obj().comp().weaponManager().request(desc);
    }
    obj().soundSE().normal().start(0x561);
}

void StateFreezeAttackSpine::shotIceSpine() {
    f32 speed = obj().param().lowper()._7C;
    for (int i = 0; i < 4; i++) {
        if (mWeapons[i].isAlive()) {
            hel::math::Vector2 dir(0.0f, 1.0f);
            dir.rotate(0.017453292f * T_SPINE_ANGLE_TABLE[i]);
            dir *= speed;
            mWeapons[i]->move().setVelocity(dir.toVector3());
        }
    }
    obj().soundSE().normal().start(0x562);
}

}
}
}
}
