#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#include "scn/step/enemy/damage/StateThrownNinja.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "ocoll/Owner.h"
#include "scn/step/Component.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/damage/Utility.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/ObjColl.h"
#include "util/ObjRefHandle.h"

using hel::math::Vector2;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace damage {

StateThrownNinja::StateThrownNinja(Enemy* enemy, u64 ownerUid, f32 speedRate) : StateBase(enemy), mFrame(0) {
    Utility::OnDamageStart(&obj());
    obj().model().reqScript(6);
    obj().objColl().bodyColl().setStateXlu();
    obj().damageFlash().set(ocoll::ELEMENT_0);
    ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(ownerUid);
    if (hero.isAlive()) {
        ::ocoll::Owner& owner = hero->objColl().objColl().owner();
        obj().objColl().owner().setParentInterim(owner);
        obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0xe2));
        Vector2 offset = enemy::Utility::GetDefaultCenterOffset(obj()).getXY();
        obj().objColl().addAttack(0, 0, 0.9f, offset, offset, true);
    }
    obj().move().setSpeedH(0.1f * speedRate);
    obj().move().setSpeedV(0.2f);
}

StateThrownNinja::~StateThrownNinja() {
    Utility::OnDamageEnd(&obj());
    obj().objColl().owner().unsetParentInterim();
}

void StateThrownNinja::procAnim() {
    mFrame++;
    if (mFrame > 54) {
        if (obj().hitPoint().isDead()) {
            obj().deadWithEffect();
        } else {
            obj().recover();
        }
    }
}

void StateThrownNinja::procMove() {
    Utility::UpdateMoveRate(&obj());
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0008f), obj().param().common().mFall);
}

}}}}  // namespace scn::step::enemy::damage
