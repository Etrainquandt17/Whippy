#include "scn/step/enemy/damage/StateDeadExtreme.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
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

}

StateDeadExtreme::StateDeadExtreme(Enemy* enemy, u32 reflectMax)
    : StateBase(enemy), mRot(0.0f), mReflectCount(0), _10(20), mReflectMax(reflectMax), mFrame(0) {
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

StateDeadExtreme::~StateDeadExtreme() {
    obj().model().rotCtrl().setRotV(0.0f);
    obj().model().rotCtrl().setRotH(0.0f);
    Utility::OnDamageEnd(&obj());
}

void StateDeadExtreme::procAnim() {
    mFrame++;
    if (obj().hitPoint().isDead()) {
        Utility::EmDamageUtility_ReqEffectHP0(&obj());
    }
    f32 speed = obj().water().isInWater() ? 16.0f : 20.0f;
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

void StateDeadExtreme::procMove() {
    Utility::UpdateMoveRateExtreme(&obj());
    Utility::EmDamageUtility_Move(&obj());
}

void StateDeadExtreme::procFixPos() {
    if (Utility::EmDamageUtility_ReflectWall(&obj())) {
        mReflectCount++;
    }
    if (mReflectCount > mReflectMax || mFrame > 240) {
        obj().deadWithEffect();
    }
}

}
}
}
}
