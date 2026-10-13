#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE
#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/damage/StateFreezeShot.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "ocoll/Owner.h"
#include "ocoll/SearchAttack.h"
#include "ocoll/SearchHit.h"
#include "revolution/gx/GXStruct.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Flash.h"
#include "scn/step/enemy/InterruptStateChanger.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/ObjCollReact.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/damage/Utility.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace enemy {
namespace damage {

namespace {

// TODO: weapon::icecube::Param, which has no header yet.
struct t_IceCubeParam {
    f32 mRadius;
};

inline f32 t_IceCubeRadius(const weapon::Param& param) {
    return reinterpret_cast<const t_IceCubeParam&>(param.iceCube()).mRadius;
}

// TODO: chara::MapCollResult::isHitWall(), which the shared header declares without its body.
inline bool t_IsHitWall(const chara::MapCollResult& result) {
    return result._2 || result._3;
}

inline bool t_IsCameraOut(Enemy& enemy) {
    hel::math::Vector3 center = enemy.location().centerPos();
    f32 radius = (enemy.location().pos() - center).length();
    hel::geo::Rect rect = enemy.comp().mainCamera().getViewRect();
    rect._0 -= radius;
    rect._4 += radius;
    rect._8 += radius;
    rect._C -= radius;
    if (rect.isInclude(center.x, center.y)) {
        return false;
    }
    return true;
}

}

StateFreezeShot::StateFreezeShot(Enemy* enemy, const u64& ownerUid)
    : StateBase(enemy), mFrame(0), mRot(360.0f), mOwnerUid(ownerUid), mWeapon() {
    util::ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(ownerUid);
    obj().worldCage().setIsValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().nururi().setCanNururi(false);
    obj().nururi().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().model().setDynamicsDisable();
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
    hel::math::Vector3 offset = hel::math::Vector2(obj().charaParam()._4).toVector3();
    offset.y += Utility::EmDamageUtility_GetEffectOffsetY(&obj());
    u32 node = obj().charaParam()._38;
    f32 scale = Utility::EmDamageUtility_GetEffectScale(&obj());
    obj().effect().normal().releaseAndVanish();
    obj().effect().super().releaseAndVanish();
    obj().effect().charaBack().requestN(static_cast<effect::Kind>(0x5e7), node, offset, scale);
    obj().move().setSpeedH(0.22f * obj().target().getSign());
    obj().model().reqScript(6);
    Utility::EmDamageUtility_StopAnimRandomFrame(&obj());
    createWeapon(hero);
    obj().comp().permSoundSE().start(0x246);
    GXColor color = {0xC8, 0xC8, 0xFF, 0x80};
    obj().flash().setEnfAlways(color);
}

StateFreezeShot::~StateFreezeShot() {
    obj().vacuumReceiver().setIsValid(true);
    obj().nururi().setValid(true);
    obj().model().setDynamicsEnable();
    obj().water().setUseCallback(true);
    obj().flash().disableAlwaysRequest();
    if (mWeapon.isAlive()) {
        mWeapon->dead();
    }
}

void StateFreezeShot::procAnim() {
    mFrame++;
    if (mFrame > 300 || mWeapon.isNull()) {
        Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
    } else {
        mRot -= obj().water().isInWater() ? 4.0f : 8.0f;
        if (mRot < 0.0f) {
            mRot += 360.0f;
        }
        obj().model().rotCtrl().setRotH(mRot);
    }
}

void StateFreezeShot::procMove() {
    if (obj().water().isInWater()) {
        obj().move().setMoveRate(0.3f);
    } else {
        obj().move().resetMoveRate();
    }
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
    gobj::MoveParamFall fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateFreezeShot::procConstraint() {
    if (mWeapon.isAlive()) {
        mWeapon->location().setPos(obj().location().centerPos());
        mWeapon->model().procFixPos();
    }
}

void StateFreezeShot::procFixPos() {
    if (t_IsHitWall(obj().mapColl().result())) {
        Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
        return;
    }
    if (mWeapon.isAlive()) {
        if (mWeapon->objColl().attack().isCollide()) {
            obj().hitStop().set(8);
        }
        if (mWeapon->objColl().attack().isCollideGimmick()) {
            Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
            return;
        }
    }
    if (obj().kind() == 0x88) {
        if (t_IsCameraOut(obj())) {
            Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
        }
    }
}

void StateFreezeShot::createWeapon(const util::ObjRefHandle<hero::Hero>& hero) {
    hel::math::Vector2 pos = obj().location().pos().getXY();
    hel::math::Vector3 toCenter = obj().location().toCenter();
    hel::math::Vector2 center = pos + toCenter.getXY();
    hel::math::Vector2 zero;
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0x21);
    desc.mVariation = 0;
    desc.mFlag = static_cast<ostop::Flag>(1);
    desc.mPos = center;
    desc._14 = pos;
    desc._1c = zero;
    desc.mOwner = &hero->objColl().objColl().owner();
    mWeapon = obj().comp().weaponManager().request(desc);
    if (mWeapon.isAlive()) {
        mWeapon->objColl().setAttackType(static_cast<ocoll::AttackType>(0xcc));
        f32 scale = Utility::EmDamageUtility_GetModelScale(&obj());
        hel::math::Vector2 offset = hel::math::Vector2::ZERO;
        offset.y += Utility::EmDamageUtility_GetEffectOffsetY(&obj());
        if (obj().kind() == 0x65) {
            offset.y += 0.4f;
        }
        weapon::Weapon* weapon = mWeapon.operator->();
        scale *= t_IceCubeRadius(weapon->param());
        weapon->objColl().addAttack(0, scale, offset);
        mWeapon->culling().setValid(false);
    }
}

}
}
}
}
