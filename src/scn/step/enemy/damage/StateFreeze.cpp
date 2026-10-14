#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE
#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/damage/StateFreeze.h"

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
#include "scn/step/enemy/damage/StateFreezeMove.h"
#include "scn/step/enemy/damage/Utility.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"

using app::Random;
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

}

StateFreeze::StateFreeze(Enemy* enemy, u64 ownerUid) : StateBase(enemy), mFrame(0), mWeapon(), mPos(obj().location().pos()) {
    u32 node = obj().charaParam()._38;
    f32 scale = Utility::EmDamageUtility_GetModelScale(&obj());
    obj().footState().setAir();
    obj().model().reqScript(6);
    Utility::EmDamageUtility_StopAnimRandomFrame(&obj());
    int total = obj().model().anim().totalFrame();
    if (total != 0) {
        obj().model().anim().setFrame(Random::Rand(0, total));
        obj().model().anim().setFrameRate(0.0f);
    }
    Vector3 offset = Vector2(obj().charaParam()._4).toVector3();
    offset.y += Utility::EmDamageUtility_GetEffectOffsetY(&obj());
    obj().effect().normal().releaseAndVanish();
    obj().effect().super().releaseAndVanish();
    f32 effectScale = Utility::EmDamageUtility_GetEffectScale(&obj());
    obj().effect().charaBack().requestN(static_cast<effect::Kind>(0x5e7), node, offset, effectScale);
    obj().vacuumReceiver().setIsValid(false);
    obj().nururi().setCanNururi(false);
    obj().nururi().setValid(false);
    obj().interruptStateChanger().deny();
    obj().move().resetVelocity();
    obj().mapColl().reset();
    obj().objColl().bodyColl().setStateXlu();
    obj().objCollReact().setDamageState();
    obj().model().setDynamicsDisable();
    Vector2 center = obj().location().toCenter().getXY();
    center.y += Utility::EmDamageUtility_GetOCollOffsetY(&obj());
    obj().objColl().clearSearchHit();
    obj().objColl().addSearchHit(node, 0.7f * scale, center);
    obj().objColl().clearSearchAttack();
    obj().objColl().addSearchAttack(node, 0.7f * scale, center);
    ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(ownerUid);
    if (hero.isAlive()) {
        createWeapon(hero);
    }
    GXColor color = {0xC8, 0xC8, 0xFF, 0x80};
    obj().flash().setEnfAlways(color);
}

StateFreeze::~StateFreeze() {
    if (mWeapon.isAlive()) {
        mWeapon->dead();
    }
}

void StateFreeze::procAnim() {
    mFrame++;
    if (mFrame == 30 && !obj().isSuper() && mWeapon.isAlive()) {
        mWeapon->objColl().attack().setValid(true);
        f32 radius = reinterpret_cast<const t_IceCubeParam&>(mWeapon->param().iceCube()).mRadius * Utility::EmDamageUtility_GetModelScale(&obj());
        Vector2 offset = Vector2::ZERO;
        offset.y += Utility::EmDamageUtility_GetOCollOffsetY(&obj());
        if (obj().kind() == 0x65) {
            offset.y += 0.4f;
        }
        if (obj().kind() == 0x73) {
            offset.y += 0.5f;
        }
        mWeapon->objColl().addAttack(0, radius, offset);
    }
    if (mFrame > 600 || (mFrame > 60 && obj().isSuper()) || mWeapon.isNull()) {
        Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
    }
}

void StateFreeze::procMove() {
    obj().move().resetVelocity();
}

void StateFreeze::procConstraint() {
    if (mWeapon.isAlive()) {
        mWeapon->location().setPos(obj().location().centerPos());
        mWeapon->model().procFixPos();
    }
}

void StateFreeze::procFixPos() {
    if (!mPos.equalsLoose(obj().location().pos(), 0.25f)) {
        if (mFrame < 570) {
            mFrame = 570;
        }
        return;
    }
    ::ocoll::SearchHit& searchHit = obj().objColl().searchHit();
    if (mFrame > 10 && searchHit.isCollide() && !obj().isSuper()) {
        for (u32 i = 0; i < searchHit.getCollidedNum(); i++) {
            u64 uid = searchHit.getCollidedHitOwnerUid(i);
            ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(uid);
            if (hero.isAlive()) {
                Vector3 enemyPos = obj().location().pos();
                Vector3 heroPos = hero->location().pos();
                Vector3 diff = heroPos - enemyPos;
                hero->target().setIsRightDir(diff.x < 0.0f);
                hero->stateChecker().set_1e(true);
                obj().stateChanger().setNextState<StateFreezeMove, Enemy*, u64>(objPtr(), uid);
                return;
            }
        }
    }
    ::ocoll::SearchAttack& searchAttack = obj().objColl().searchAttack();
    if (mFrame > 10 && searchAttack.isCollide() && !obj().isSuper()) {
        for (u32 i = 0; i < searchAttack.getCollidedNum(); i++) {
            u64 uid = searchAttack.getCollidedAttackOwnerRootUid(i);
            ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(uid);
            if (hero.isAlive()) {
                u32 element = searchAttack.getCollidedAttackElement(i);
                if (searchAttack.getCollidedAttackType(i) != 0xc5 && element != 3) {
                    obj().stateChanger().setNextState<StateFreezeMove, Enemy*, u64>(objPtr(), uid);
                    return;
                }
            }
        }
    }
}

void StateFreeze::procObjCollReact() {
    if (mWeapon.isAlive() && mWeapon->objColl().isAttackCollide()) {
        Utility::EmDamageUtility_DeadWithFreezeEffect(&obj());
    }
}

void StateFreeze::createWeapon(const ObjRefHandle<hero::Hero>& hero) {
    Vector3 centerOffset = enemy::Utility::GetDefaultCenterOffset(obj());
    Vector2 pos = obj().location().pos().getXY();
    Vector2 center = pos + centerOffset.getXY();
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
        mWeapon->objColl().setAttackType(static_cast<ocoll::AttackType>(0xc5));
        mWeapon->objColl().attack().setValid(false);
        mWeapon->culling().setValid(false);
    }
}

}}}}  // namespace scn::step::enemy::damage
