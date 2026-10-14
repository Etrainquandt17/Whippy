#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#include "scn/step/enemy/damage/StateThrownFighter.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Owner.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/StateChecker.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/damage/Utility.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/ObjColl.h"
#include "util/ObjRefHandle.h"

using hel::geo::Rect;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

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

StateThrownFighter::StateThrownFighter(Enemy* enemy, u64 ownerUid)
    : StateBase(enemy), mFrame(0), mRot(0.0f), mIsReflected(false), mWait(20) {
    Utility::OnDamageStart(&obj());
    obj().model().reqScript(6);
    obj().objColl().bodyColl().setStateXlu();
    obj().damageFlash().set(ocoll::ELEMENT_0);
    bool isBackThrow = Math::Abs(obj().move().velocity().x) == 0.3f;
    if (isBackThrow) {
        obj().effect().state().requestN(static_cast<effect::Kind>(0x16a), 0);
    }
    ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(ownerUid);
    if (hero.isAlive()) {
        ::ocoll::Owner& owner = hero->objColl().objColl().owner();
        obj().objColl().owner().setParentInterim(owner);
        ocoll::AttackType type = isBackThrow ? static_cast<ocoll::AttackType>(0x102) : static_cast<ocoll::AttackType>(0x100);
        obj().objColl().setAttackType(0, type);
        Vector2 offset = enemy::Utility::GetDefaultCenterOffset(obj()).getXY();
        obj().objColl().addAttack(0, 0, 0.8f, offset, offset, true);
    }
    if (!isBackThrow) {
        Vector3 pos = obj().location().pos();
        pos.y += 0.3f;
        obj().location().setPos(pos);
    }
    if (obj().move().velocity().isZeroLoose(0.00001f)) {
        obj().move().setVelocity(Vector3(0.05f * obj().target().getSign(), 0.1f, 0.0f));
    }
}

StateThrownFighter::~StateThrownFighter() {
    obj().model().rotCtrl().setRotV(0.0f);
    obj().model().rotCtrl().setRotH(0.0f);
    Utility::OnDamageEnd(&obj());
    obj().objColl().owner().unsetParentInterim();
    obj().stateChecker().setFighterBackThrow(false);
}

void StateThrownFighter::procAnim() {
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
        if (!mIsReflected) {
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

void StateThrownFighter::procMove() {
    Utility::UpdateMoveRate(&obj());
    Utility::EmDamageUtility_Move(&obj());
}

void StateThrownFighter::procFixPos() {
    bool isReflect = Utility::EmDamageUtility_ReflectWall(&obj());
    if (!mIsReflected) {
        mIsReflected = isReflect;
    }
    chara::MapCollResult result = obj().mapColl().result();
    Rect rect = obj().comp().mainCamera().getViewRect();
    Vector3 pos = obj().location().pos();
    if (mWait != 0) {
        mWait--;
    } else if (result.mIsHitFloor || t_IsHitWall(result) || pos.y > rect._0 || pos.x < rect._8 || pos.x > rect._C) {
        if (obj().hitPoint().isDead()) {
            obj().deadWithEffect();
            return;
        }
        obj().recover();
        return;
    }
}

}}}}  // namespace scn::step::enemy::damage
