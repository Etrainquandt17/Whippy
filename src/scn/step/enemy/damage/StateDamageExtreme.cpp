#include "scn/step/enemy/damage/StateDamageExtreme.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
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

// TODO: an inline function of chara::MapCollResult.
inline bool t_IsHit(const chara::MapCollResult& result) {
    return result.mIsHitFloor || result.mIsHitRoof || result._2 || result._3;
}

}

StateDamageExtreme::StateDamageExtreme(Enemy* enemy) : StateBase(enemy), mRot(0.0f), mIsReflected(false), mFrame(20) {
    Utility::OnDamageStart(&obj());
    obj().model().reqScript(6);
    Utility::EmDamageUtility_InitTarget(&obj());
    Utility::EmDamageUtility_InitVelocity(&obj());
    ocoll::Element element = static_cast<ocoll::Element>(obj().damageInfo().data().mElement);
    obj().damageFlash().set(element);
    if (obj().hitPoint().isDead()) {
        hel::math::Vector3 offset = enemy::Utility::GetDefaultCenterOffset(obj());
        effect::Kind kind = static_cast<effect::Kind>(0x125);
        if (obj().water().isInWater()) {
            kind = static_cast<effect::Kind>(0x131);
        }
        obj().effect().state().requestN(kind, obj().charaParam()._38, offset);
    }
}

StateDamageExtreme::~StateDamageExtreme() {
    obj().model().rotCtrl().setRotV(0.0f);
    obj().model().rotCtrl().setRotH(0.0f);
    Utility::OnDamageEnd(&obj());
}

void StateDamageExtreme::procAnim() {
    if (obj().hitPoint().isDead()) {
        Utility::EmDamageUtility_ReqEffectHP0(&obj());
    }
    mRot += 20.0f * obj().target().getSign();
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    if (!mIsReflected) {
        hel::math::Vector2 dir = obj().move().velocity().getXY();
        t_Normalize(dir);
        f32 angle = hel::math::Vector2::BASIS_Y.signedAngle(dir);
        obj().model().rotCtrl().setRotV(57.29578f * angle);
        obj().model().rotCtrl().setRotH(mRot);
    } else {
        obj().model().rotCtrl().setRotV(mRot);
        obj().model().rotCtrl().setRotH(0.0f);
    }
}

void StateDamageExtreme::procMove() {
    Utility::UpdateMoveRateExtreme(&obj());
    Utility::EmDamageUtility_Move(&obj());
}

void StateDamageExtreme::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    hel::geo::Rect rect = obj().comp().mainCamera().getViewRect();
    if (Utility::EmDamageUtility_ReflectWall(&obj())) {
        mIsReflected = true;
    }
    if (mFrame != 0) {
        mFrame--;
    } else if (t_IsHit(result)) {
        if (obj().hitPoint().isDead()) {
            obj().deadWithEffect();
        }
        obj().recover();
        return;
    }
}

}
}
}
}
