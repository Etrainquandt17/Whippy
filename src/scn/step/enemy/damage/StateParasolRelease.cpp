#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#include "scn/step/enemy/damage/StateParasolRelease.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/geo/Rect.h"
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
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/damage/Utility.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/ObjColl.h"
#include "util/ObjRefHandle.h"

using hel::geo::Rect;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace damage {

namespace {

// TODO: chara::MapCollResult::isHitWall(), which the shared header declares without its body.
inline bool t_IsHitWall(const chara::MapCollResult& result) {
    return result._2 || result._3;
}

}

StateParasolRelease::StateParasolRelease(Enemy* enemy, u64 ownerUid, u32 endFrame)
    : StateBase(enemy), mRot(0.0f), mFrame(0), mEndFrame(endFrame), mWait(20) {
    Utility::OnDamageStart(&obj());
    obj().objColl().bodyColl().setStateXlu();
    if (obj().hitPoint().isDead()) {
        Vector3 offset = enemy::Utility::GetDefaultCenterOffset(obj());
        obj().effect().state().requestN(static_cast<effect::Kind>(0x125), obj().charaParam()._38, offset);
    }
    ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(ownerUid);
    Vector2 offset = enemy::Utility::GetDefaultCenterOffset(obj()).getXY();
    if (hero.isAlive()) {
        ::ocoll::Owner& owner = hero->objColl().objColl().owner();
        obj().objColl().owner().setParentInterim(owner);
        obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x94));
        obj().objColl().addAttack(0, 0, 1.0f, offset, offset, true);
    }
    obj().model().reqScript(6);
}

StateParasolRelease::~StateParasolRelease() {
    obj().model().rotCtrl().setRotV(0.0f);
    obj().model().rotCtrl().setRotH(0.0f);
    Utility::OnDamageEnd(&obj());
    obj().objColl().owner().unsetParentInterim();
}

void StateParasolRelease::procAnim() {
    mFrame++;
    if (mFrame > mEndFrame) {
        if (obj().hitPoint().isDead()) {
            obj().deadWithEffect();
        } else {
            obj().recover();
        }
    } else {
        mRot -= 20.0f;
        if (mRot < 0.0f) {
            mRot += 360.0f;
        }
        obj().model().rotCtrl().setRotV(mRot);
        obj().model().rotCtrl().setRotH(0.0f);
    }
}

void StateParasolRelease::procMove() {
    Utility::UpdateMoveRate(&obj());
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.0001f);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.2f, 0.01f, 0.005f);
    obj().move().airDecelFall(decel, fall);
}

void StateParasolRelease::procFixPos() {
    Utility::EmDamageUtility_ReflectWall(&obj());
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

void StateParasolRelease::procObjCollReact() {}

}}}}  // namespace scn::step::enemy::damage
