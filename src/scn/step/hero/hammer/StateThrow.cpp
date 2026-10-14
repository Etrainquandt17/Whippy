#include "scn/step/hero/hammer/StateThrow.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/HammerParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjList.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace hammer {

// The Korean version has no mIsEnd and gives the ability up in the destructor.
#ifdef VERSION_SUKK01
StateThrow::StateThrow(Hero* hero)
    : StateBase(hero) {
#else
StateThrow::StateThrow(Hero* hero)
    : StateBase(hero)
    , mIsEnd(false) {
#endif
    hero::Utility::UpdateMoveTarget(obj());
    obj().invincible().setPerm();
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().weapon().setVisibility(false);
    obj().model().script().start(0x135);
    f32 sign = obj().target().getSign();
    Vector3 heroPos = static_cast<const Hero&>(obj()).location().pos();
    Vector2 pos(heroPos.x, heroPos.y);
    pos.y += 0.5f;
    Vector2 weaponPos = pos;
    Vector2 speed(sign * obj().param().hammer()._28, obj().param().hammer()._2C);
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0x20);
    desc.mVariation = 0;
    desc.mFlag = static_cast<ostop::Flag>(1);
    desc.mPos = weaponPos;
    desc._14 = pos;
    desc._1c = speed;
    desc.mOwner = &obj().objColl().objColl().owner();
    desc._2e = true;
    desc._2f = true;
    desc._30 = 3;
    obj().comp().weaponManager().request(desc);
}

StateThrow::~StateThrow() {
    if (obj().abilityManager().isFixedAbility()) {
        obj().model().subAnimControl().setLiftUpRHand(true);
        obj().model().weapon().setVisibility(true);
    } else {
#ifdef VERSION_SUKK01
        obj().abilityManager().clearAbility();
        obj().abilityManager().changeAbilityIfPossible();
#else
        if (mIsEnd) {
            obj().abilityManager().clearAbility();
        }
#endif
    }
}

void StateThrow::procAnim() {
    if (obj().model().isAllEnd()) {
#ifndef VERSION_SUKK01
        mIsEnd = true;
#endif
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateThrow::procMove() {
    hero::Utility::MoveDefaultBrake(obj());
}

void StateThrow::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::hammer
