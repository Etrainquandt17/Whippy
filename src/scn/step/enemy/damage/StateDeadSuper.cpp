#include "scn/step/enemy/damage/StateDeadSuper.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/damage/Utility.h"

namespace scn {
namespace step {
namespace enemy {
namespace damage {

namespace {

// TODO: hel::math::Vector2::normalize(), which the original expands here and the shared header only declares.
inline f32 t_Normalize(hel::math::Vector2& v) {
    f32 len = v.length();
    if (len == 0.0f) {
        return len;
    }
    v /= len;
    return len;
}

// TODO: chara::MapCollResult::isHitWall(), which the shared header declares without its body.
inline bool t_IsHitWall(const chara::MapCollResult& result) {
    return result._2 || result._3;
}

}

StateDeadSuper::StateDeadSuper(Enemy* enemy)
    : StateBase(enemy), mRot(0.0f), mReflectCount(0), _10(20), mReflectMax(2), mElement(0), mFrame(0) {
    mElement = obj().damageInfo().data().mElement;
    Utility::OnDamageStart(&obj());
    obj().model().reqScript(6);
    Utility::EmDamageUtility_InitTarget(&obj());
    Utility::EmDamageUtility_InitVelocity(&obj());
    if (obj().isSuper()) {
        obj().mapColl().setPassInvisibleLand(false);
    }
    obj().damageFlash().set(static_cast<ocoll::Element>(mElement));
    if (obj().hitPoint().isDead()) {
        hel::math::Vector3 offset = enemy::Utility::GetDefaultCenterOffset(obj());
        effect::Kind kind = static_cast<effect::Kind>(0x125);
        if (obj().water().isInWater()) {
            kind = static_cast<effect::Kind>(0x131);
        }
        obj().effect().state().requestN(kind, obj().charaParam()._38, offset);
    }
}

StateDeadSuper::~StateDeadSuper() {
    obj().model().rotCtrl().setRotV(0.0f);
    obj().model().rotCtrl().setRotH(0.0f);
    Utility::OnDamageEnd(&obj());
}

void StateDeadSuper::procAnim() {
    mFrame++;
    if (obj().hitPoint().isDead()) {
        Utility::EmDamageUtility_ReqEffectHP0(&obj());
    }
    f32 speed = obj().water().isInWater() ? 28.0f : 35.0f;
    mRot += speed * obj().target().getSign();
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    if (mReflectCount < mReflectMax) {
        hel::math::Vector2 dir = obj().move().velocity().getXY();
        t_Normalize(dir);
        f32 angle = hel::math::Vector2::BASIS_Y.signedAngle(dir);
        obj().model().rotCtrl().setRotV(57.29578f * angle);
        obj().model().rotCtrl().setRotH(mRot);
    } else {
        obj().model().rotCtrl().setRotV(mRot);
        if (obj().kind() == 0x3b) {
            obj().model().rotCtrl().setRotH(90.0f);
        } else {
            obj().model().rotCtrl().setRotH(0.0f);
        }
    }
}

void StateDeadSuper::procMove() {
    Utility::UpdateMoveRate(&obj());
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
    gobj::MoveParamFall fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateDeadSuper::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    hel::geo::Rect rect = obj().comp().mainCamera().getViewRect();
    hel::math::Vector3 velocity = obj().move().velocity();
    hel::math::Vector3 pos = obj().location().pos();
    bool isReflect = false;
    if (result.mIsHitFloor) {
        obj().move().setSpeedV(-1.0f * velocity.y);
        isReflect = true;
    }
    if (result.mIsHitRoof) {
        obj().move().setSpeedV(-1.0f * velocity.y);
        isReflect = true;
    }
    if (t_IsHitWall(result)) {
        obj().move().setSpeedH(-1.0f * velocity.x);
        isReflect = true;
    }
    if (pos.y > rect._0) {
        obj().move().setSpeedV(-1.0f * velocity.y);
        isReflect = true;
    }
    if (pos.x < rect._8 || pos.x > rect._C) {
        obj().move().setSpeedH(-1.0f * velocity.x);
        isReflect = true;
    }
    if (isReflect) {
        mReflectCount++;
    }
    if (mReflectCount > mReflectMax || mFrame > 240) {
        if (!obj().isSuper() && mElement == 0x16) {
            obj().deadWithEffectNoItem();
        } else {
            obj().deadWithEffect();
        }
    }
}

}
}
}
}
