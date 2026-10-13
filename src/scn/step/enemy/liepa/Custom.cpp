#include "scn/step/enemy/liepa/Custom.h"

#include "g3d/ModelAnimAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/liepa/ParamData.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "std/cmath.h"

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mCameraCenterPrevPosX(0.0f) {}

bool Custom::onInit() {
    obj().footState().setAir();
    obj().target().setIsRightDir(false);
    obj().nururi().setValid(false);
    obj().nururi().setCanNururi(false);
    setSubAnimTexture();
    obj().culling().setValid(false);
    return false;
}

bool Custom::onDamaged() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(0));
    ocoll::Element element = obj().objColl().bodyColl().damageInfo().attackElement();
    obj().damageFlash().set(element);
    return true;
}

bool Custom::onHitPointIsZero() {
    chara::DamageInfo info = obj().damageInfo();
    if (info.attackElement() == 0x10) {
        obj().comp().permSoundSE().start(0x2a5);
        obj().dead();
    } else {
        obj().deadWithEffectNoItem();
    }
    return true;
}

void Custom::onProcFixPos() {
    mCameraCenterPrevPosX = obj().comp().mainCamera().getCenter().x;
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit()) {
        obj().deadWithEffectNoItem();
    } else if (Utility::CheckShootingCulling(obj())) {
        obj().dead();
    }
}

bool Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x387), Utility::GetCenterPos(obj()));
    obj().comp().permSoundSE().start(0x2a5);
    return true;
}

f32 Custom::cameraCenterPrevPosX() {
    return mCameraCenterPrevPosX;
}

bool Custom::isExistHeroInAttackRange() {
    return !getNearestHeroInAttackRange().isZeroLoose(0.00001f);
}

// TODO: differs by one instruction: the original keeps the address of the negated BASIS_X in a register across the loop.
hel::math::Vector2 Custom::getNearestHeroInAttackRange() {
    const ParamData& param = obj().param().liepa();
    hel::math::Vector2 result = hel::math::Vector2::ZERO;
    u32 count = obj().comp().heroManager().getPlayerCount();
    for (u32 i = 0; i < count; i++) {
        hel::math::Vector2 heroPos = obj().comp().heroManager().getPlayerByIndex(i).location().pos().getXY();
        hel::math::Vector2 diff = heroPos - obj().location().pos().getXY();
        f32 angle = 57.29578f * static_cast<f32>(acos((-hel::math::Vector2::BASIS_X).cos(diff)));
        if (angle < param.mAttackAngle) {
            if (result.isZeroLoose(0.00001f)) {
                result = heroPos;
            } else {
                f32 dist = result.distance(obj().location().pos().getXY());
                if (heroPos.distance(obj().location().pos().getXY()) < dist) {
                    result = heroPos;
                }
            }
        }
    }
    return result;
}

void Custom::reqShot() {
    hel::math::Vector2 pos = Utility::GetCenterPos(obj()).getXY();
    hel::geo::Rect rect = obj().comp().mainCamera().getViewRect();
    if (!rect.isInclude(pos.x, pos.y)) {
        return;
    }
    hel::math::Vector3 target = getNearestHeroInAttackRange().toVector3();
    hel::math::Vector2 dir = target.getXY() - obj().location().pos().getXY();
    if (target.isZeroLoose(0.00001f)) {
        dir = -hel::math::Vector2::BASIS_X;
    }
    weapon::Desc desc(static_cast<weapon::Kind>(0x79), 0, static_cast<ostop::Flag>(4), pos, dir, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    obj().soundSE().start(0x295);
}

void Custom::setSubAnimTexture() {
    obj().model().anim().subAnimSet(0, 1, 0);
    obj().model().anim().subAnimAccessor(0).start(true);
}

void Custom::setBodyColl() {
    hel::math::Vector2 offset(obj().charaParam()._4.x, obj().charaParam()._4.y);
    obj().objColl().addBodyColl(0, obj().charaParam()._2c, offset);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::liepa
