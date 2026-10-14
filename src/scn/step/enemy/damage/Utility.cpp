#include "scn/step/enemy/damage/Utility.h"

#include "app/Application.h"
#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Model.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Random.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/ObjCollReact.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/map/LandManager.h"

using app::Application;
using app::Random;
using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace damage {

void Utility::EmDamageUtility_InitTarget(Enemy* enemy) {
    if (enemy->objColl().bodyColl().isCollide()) {
        Vector2 attackPos = enemy->damageInfo().data().mAttackPos;
        bool isRight = enemy->location().pos().x < attackPos.x;
        enemy->target().setIsRightDir(isRight);
    }
}

void Utility::EmDamageUtility_InitVelocity(Enemy* enemy) {
    if (enemy->objColl().bodyColl().isCollide() && (enemy->hitPoint().isDead() || !enemy->charaParam()._45)) {
        Vector3 velocity = Vector3::BASIS_X;
        chara::DamageInfo info = enemy->damageInfo();
        f32 angle = info.data().mAngle;
        f32 width = info.data().mWidth;
        f32 speed = info.data().mSpeed;
        f32 rot = angle + width * Application::Object().random().randAF();
        velocity.rotate(Vector3::BASIS_Z, 0.017453292f * rot);
        velocity.x *= -1.0f * enemy->target().getSign();
        velocity *= speed * EmDamageUtility_GetInitVelocityRate(enemy, info);
        enemy->move().setVelocity(velocity);
    }
}

void Utility::EmDamageUtility_Move(Enemy* enemy) {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.0001f);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.2f, 0.006f, 0.005f);
    if (!enemy->hitPoint().isDead() && enemy->charaParam()._45) {
        fall = gobj::MoveParamFall::Zero();
    }
    if (enemy->water().isInWater()) {
        fall = gobj::MoveParamFall::Create(0.04f, 0.002f, 0.001f);
    }
    enemy->move().airDecelFall(decel, fall);
}

bool Utility::EmDamageUtility_ReflectWall(Enemy* enemy) {
    chara::MapCollResult result = enemy->mapColl().result();
    Rect rect = enemy->comp().mainCamera().getViewRect();
    Vector3 velocity = enemy->move().velocity();
    Vector3 center = enemy->location().centerPos();
    f32 margin = enemy->charaParam()._2c;
    rect._0 -= margin;
    rect._4 += margin;
    rect._8 += margin;
    rect._C -= margin;
    bool isRoof = false;
    bool isFloor = false;
    bool isLeft = false;
    bool isRight = false;
    if (result.mIsHitFloor && enemy->move().velocity().y < 0.0f) {
        isFloor = true;
    }
    if (result.mIsHitRoof) {
        isRoof = true;
    }
    if (result._2) {
        bool isRightDir = enemy->target().isRightDir();
        if (isRightDir) {
            isRight = true;
        }
        if (!isRightDir) {
            isLeft = true;
        }
    }
    if (result._3) {
        bool isRightDir = enemy->target().isRightDir();
        if (isRightDir) {
            isLeft = true;
        }
        if (!isRightDir) {
            isRight = true;
        }
    }
    if (center.y > rect._0) {
        isRoof = true;
    }
    if (center.x < rect._8) {
        isLeft = true;
    }
    if (center.x > rect._C) {
        isRight = true;
    }
    if (isRoof) {
        enemy->move().setSpeedV(-1.0f * Math::Abs(velocity.y));
    }
    if (isFloor) {
        enemy->move().setSpeedV(0.5f * Math::Abs(velocity.y));
    }
    if (isLeft) {
        enemy->move().setSpeedH(0.5f * Math::Abs(velocity.x));
    }
    if (isRight) {
        enemy->move().setSpeedH(-0.5f * Math::Abs(velocity.x));
    }
    return isRoof | isFloor | isLeft | isRight;
}

void Utility::EmDamageUtility_ReqEffectHP0(Enemy* enemy) {
    Vector2 offset = enemy->charaParam()._4;
    Vector2 pos = enemy->location().pos().getXY() + offset;
    Vector2 prevPos = enemy->location().prevPos().getXY() + offset;
    bool isWater = enemy->comp().mapLandManager().native().isWaterGrid(pos);
    bool isWaterPrev = enemy->comp().mapLandManager().native().isWaterGrid(prevPos);
    Vector3 effectOffset = offset.toVector3();
    effectOffset *= enemy::Utility::GetModelScaleBySizeType(*enemy);
    if (isWater != isWaterPrev) {
        enemy->effect().state().release();
        effect::Kind kind = static_cast<effect::Kind>(0x125);
        if (isWater) {
            kind = static_cast<effect::Kind>(0x131);
        }
        enemy->effect().state().requestN(kind, enemy->charaParam()._38, effectOffset);
    }
}

void Utility::OnDamageStart(Enemy* enemy) {
    enemy->footState().setAir();
    enemy->nururi().setCanNururi(false);
    enemy->nururi().setValid(false);
    enemy->mapColl().setPassThroughLandState(false);
    enemy->objColl().bodyColl().setStateHitOnly();
    enemy->objCollReact().setDamageState();
}

void Utility::OnDamageEnd(Enemy* enemy) {
    enemy->nururi().setCanNururi(true);
    enemy->nururi().setValid(true);
    enemy->objColl().bodyColl().setStateNormal();
    enemy->model().anim().setFrameRate(1.0f);
    enemy->damageFlash().unset();
    enemy->move().resetMoveRate();
}

f32 Utility::EmDamageUtility_GetInitVelocityRate(Enemy* enemy, const chara::DamageInfo& info) {
    f32 rate = 1.0f;
    if (info.data()._48) {
        return rate;
    }
    if (enemy->isSuper()) {
        rate *= 0.5f;
    }
    if (enemy->water().isInWater()) {
        if (info.smashType() == 6 || info.smashType() == 7) {
            rate *= 0.75f;
        } else {
            rate *= 0.4f;
        }
    }
    if (enemy->kind() == 0x1a) {
        rate *= 0.5f;
    }
    if (enemy->kind() == 0x31) {
        if (!DynamicCastToRef<sheld::Custom, ICustom>(enemy->custom()).isEscape()) {
            rate *= 0.5f;
        }
    }
    return rate;
}

f32 Utility::EmDamageUtility_GetModelScale(Enemy* enemy) {
    if (enemy->variation() == 0xce) {
        // TODO: gobj::GearModel derives from gobj::Model.
        return 0.9f * reinterpret_cast<gobj::Model&>(enemy->model().model()).scale().x;
    }
    switch (enemy->kind()) {
    case 11:
    case 15:
    case 17:
    case 27:
    case 39:
    case 45:
    case 46:
    case 50:
    case 51:
    case 54:
    case 60:
    case 61:
    case 68:
    case 95:
    case 113:
        return 1.2f * enemy::Utility::GetModelScaleBySizeType(*enemy);
    case 6:
    case 22:
    case 59:
    case 87:
        return 1.5f * enemy::Utility::GetModelScaleBySizeType(*enemy);
    case 7:
    case 8:
    case 13:
    case 37:
    case 76:
    case 86:
    case 132:
        return 2.0f * enemy::Utility::GetModelScaleBySizeType(*enemy);
    default:
        return reinterpret_cast<gobj::Model&>(enemy->model().model()).scale().x;
    }
}

f32 Utility::EmDamageUtility_GetEffectScale(Enemy* enemy) {
    switch (enemy->kind()) {
    case 11:
    case 27:
    case 45:
    case 50:
    case 51:
    case 60:
    case 61:
    case 68:
    case 113:
        return 1.2f;
    case 15:
    case 54:
    case 130:
        return 1.3f;
    case 17:
    case 46:
    case 95:
        return 1.35f;
    case 39:
        return 1.4f;
    case 6:
    case 22:
    case 59:
    case 87:
        return 1.5f;
    case 7:
    case 8:
    case 37:
    case 128:
    case 132:
        return 2.0f;
    case 13:
    case 76:
    case 86:
        return 2.4f;
    case 136:
        return 3.0f;
    default:
        return 1.0f;
    }
}

f32 Utility::EmDamageUtility_GetEffectOffsetY(Enemy* enemy) {
    switch (enemy->kind()) {
    case 15:
    case 17:
    case 51:
    case 60:
    case 61:
        return 0.2f;
    case 6:
    case 22:
    case 27:
    case 50:
    case 68:
    case 87:
        return 0.3f;
    case 37:
        return 0.5f;
    case 115:
        return -0.4f;
    default:
        return 0.0f;
    }
}

f32 Utility::EmDamageUtility_GetOCollOffsetY(Enemy* enemy) {
    if (enemy->variation() == 0xce) {
        return 0.7f;
    }
    enemy->kind();
    return EmDamageUtility_GetEffectOffsetY(enemy);
}

void Utility::EmDamageUtility_DeadWithFreezeEffect(Enemy* enemy) {
    enemy->effect().normal().requestP(static_cast<effect::Kind>(0x302), enemy->location().centerPos());
    enemy->deadWithEffect();
}

void Utility::EmDamageUtility_StopAnimRandomFrame(Enemy* enemy) {
    int total = enemy->model().anim().totalFrame();
    if (total != 0) {
        enemy->model().anim().setFrame(Random::Rand(0, total));
        enemy->model().anim().setFrameRate(0.0f);
    }
}

void Utility::UpdateMoveRate(Enemy* enemy) {
    f32 rate = enemy->water().isInWater() ? 0.4f : 1.0f;
    enemy->move().setMoveRate(rate);
}

void Utility::UpdateMoveRateExtreme(Enemy* enemy) {
    f32 rate = enemy->water().isInWater() ? 0.8f : 1.0f;
    enemy->move().setMoveRate(rate);
}

}}}}  // namespace scn::step::enemy::damage
