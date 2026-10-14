#include "scn/step/enemy/damage/StateDamageCapture.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
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

using hel::geo::Rect;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace damage {

namespace {

// TODO: hel::math::Vector2::normalize(), which the original expands here and the shared header only declares.
inline f32 t_Normalize(Vector2& v) {
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

StateDamageCapture::StateDamageCapture(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mRot(0.0f), mIsLanded(false), mWait(20) {
    Utility::OnDamageStart(&obj());
    obj().model().reqScript(6);
    if (obj().hitPoint().isDead()) {
        Vector3 offset = enemy::Utility::GetDefaultCenterOffset(obj());
        effect::Kind kind = static_cast<effect::Kind>(0x125);
        if (obj().water().isInWater()) {
            kind = static_cast<effect::Kind>(0x131);
        }
        obj().effect().state().requestN(kind, obj().charaParam()._38, offset);
    }
}

StateDamageCapture::~StateDamageCapture() {
    obj().model().rotCtrl().setRotV(0.0f);
    obj().model().rotCtrl().setRotH(0.0f);
    Utility::OnDamageEnd(&obj());
}

void StateDamageCapture::procAnim() {
    if (obj().hitPoint().isDead()) {
        Utility::EmDamageUtility_ReqEffectHP0(&obj());
    }
    mFrame++;
    if (mFrame > 240) {
        if (obj().hitPoint().isDead()) {
            obj().deadWithEffect();
        } else {
            obj().recover();
        }
    } else {
        mRot += 20.0f * obj().target().getSign();
        if (mRot >= 360.0f) {
            mRot -= 360.0f;
        }
        if (mRot < 0.0f) {
            mRot += 360.0f;
        }
        if (!mIsLanded) {
            Vector2 dir = obj().move().velocity().getXY();
            t_Normalize(dir);
            f32 angle = Vector2::BASIS_Y.signedAngle(dir);
            obj().model().rotCtrl().setRotV(57.29578f * angle);
            obj().model().rotCtrl().setRotH(mRot);
        } else {
            obj().model().rotCtrl().setRotV(mRot);
            obj().model().rotCtrl().setRotH(0.0f);
        }
    }
}

void StateDamageCapture::procMove() {
    Utility::UpdateMoveRate(&obj());
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.0001f);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.2f, 0.006f, 0.005f);
    obj().move().airDecelFall(decel, fall);
}

void StateDamageCapture::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    Rect rect = obj().comp().mainCamera().getViewRect();
    Vector3 velocity = obj().move().velocity();
    Vector3 pos = obj().location().pos();
    if (result.mIsHitFloor) {
        mIsLanded = true;
        obj().move().setSpeedV(0.5f * Math::Abs(velocity.y));
    }
    if (result.mIsHitRoof) {
        obj().move().setSpeedV(-1.0f * Math::Abs(velocity.y));
    }
    if (t_IsHitWall(result)) {
        obj().move().setSpeedH(-0.95f * velocity.x);
    }
    if (pos.y > rect._0) {
        obj().move().setSpeedV(-1.0f * Math::Abs(velocity.y));
    }
    if (pos.x < rect._8 || pos.x > rect._C) {
        obj().move().setSpeedH(-0.95f * velocity.x);
    }
    if (mWait != 0) {
        mWait--;
    } else if (result.mIsHitFloor) {
        if (obj().hitPoint().isDead()) {
            obj().deadWithEffect();
            return;
        }
        obj().recover();
        return;
    }
}

}}}}  // namespace scn::step::enemy::damage
