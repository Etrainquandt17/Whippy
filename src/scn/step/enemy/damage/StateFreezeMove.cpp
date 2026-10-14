#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE
#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/damage/StateFreezeMove.h"

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

using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

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

}

StateFreezeMove::StateFreezeMove(Enemy* enemy, const u64& ownerUid)
    : StateBase(enemy), mFrame(0), mRot(obj().model().rotCtrl().getRotH()), mOwnerUid(ownerUid), mWeapon(), _28(false) {
    ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(ownerUid);
    obj().worldCage().setIsValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().nururi().setCanNururi(false);
    obj().nururi().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().model().setDynamicsDisable();
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
    Vector3 pos = obj().location().pos();
    Vector3 heroPos = hero->location().pos();
    Vector3 diff = heroPos - pos;
    f32 speed = diff.x > 0.0f ? -0.2f : 0.2f;
    obj().move().setSpeedH(speed);
    obj().target().setIsRightDir(diff.x <= 0.0f);
    createWeapon(hero);
    obj().comp().permSoundSE().start(0x246);
    GXColor color = {0xC8, 0xC8, 0xFF, 0x80};
    obj().flash().setEnfAlways(color);
}

StateFreezeMove::~StateFreezeMove() {
    obj().vacuumReceiver().setIsValid(true);
    obj().nururi().setValid(true);
    obj().model().setDynamicsEnable();
    obj().flash().disableAlwaysRequest();
    if (mWeapon.isAlive()) {
        mWeapon->dead();
    }
}

void StateFreezeMove::procAnim() {
    mFrame++;
    if (mFrame > 300 || mWeapon.isNull()) {
        Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
    } else {
        mRot -= obj().water().isInWater() ? 3.0f : 4.0f;
        if (mRot < 0.0f) {
            mRot += 360.0f;
        }
        f32 rot = mRot * obj().target().getSign();
        obj().model().rotCtrl().setRotH(rot);
    }
}

void StateFreezeMove::procMove() {
    if (obj().water().isInWater()) {
        obj().move().setMoveRate(0.3f);
    } else {
        obj().move().resetMoveRate();
    }
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
    gobj::MoveParamFall fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateFreezeMove::procConstraint() {
    if (mWeapon.isAlive()) {
        mWeapon->location().setPos(obj().location().centerPos());
        mWeapon->model().procFixPos();
    }
}

void StateFreezeMove::procFixPos() {
    if (t_IsHitWall(obj().mapColl().result())) {
        Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
    } else if (mWeapon.isAlive() && mWeapon->objColl().attack().isCollideGimmick()) {
        Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
    }
}

void StateFreezeMove::createWeapon(const ObjRefHandle<hero::Hero>& hero) {
    Vector2 pos = obj().location().pos().getXY();
    Vector3 toCenter = obj().location().toCenter();
    Vector2 center = pos + toCenter.getXY();
    Vector2 zero;
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
        mWeapon->objColl().setAttackType(static_cast<ocoll::AttackType>(0xc6));
        f32 scale = Utility::EmDamageUtility_GetModelScale(&obj());
        Vector2 offset = Vector2::ZERO;
        offset.y += Utility::EmDamageUtility_GetOCollOffsetY(&obj());
        if (obj().kind() == 0x65) {
            offset.y += 0.4f;
        }
        if (obj().kind() == 0x73) {
            offset.y += 0.5f;
        }
        weapon::Weapon* weapon = mWeapon.operator->();
        scale *= t_IceCubeRadius(weapon->param());
        weapon->objColl().addAttack(0, scale, offset);
        mWeapon->culling().setValid(false);
    }
}

}}}}  // namespace scn::step::enemy::damage
