#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE
#include "scn/step/hero/tornado/StateGust.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/TornadoParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace tornado {

bool StateGust::TryToChangeState(Hero* hero) {
    if (hero->hid().isHold(8) && !hero->hid().isHold(3) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateGust, Hero*, bool>(hero, true);
        return true;
    }
    if (hero->footState().isAir() && hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateGust, Hero*, bool>(hero, false);
        return true;
    }
    return false;
}

StateGust::StateGust(Hero* hero, bool isUp)
    : StateBase(hero)
    , mWeapon()
    , mIsUp(isUp)
    , mIsWeaponHit(false) {
    ScriptKind kind = mIsUp ? static_cast<ScriptKind>(0x128) : static_cast<ScriptKind>(0x129);
    obj().model().script().start(kind);
    obj().move().resetVelocity();
    const TornadoParam& param = obj().param().tornado();
    obj().invincible().set(param._D0);
    createWeapon();
}

StateGust::~StateGust() {
}

void StateGust::procAnim() {
    if (obj().model().isAllEnd()) {
        const TornadoParam& param = obj().param().tornado();
        obj().abilityManager().setActionInterval(param._CC);
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateGust::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateGust::procConstraint() {
    if (mWeapon.isAlive() && !mIsWeaponHit) {
        hel::math::Vector3 pos = mWeapon->location().pos();
        pos.x = static_cast<const Hero&>(obj()).location().pos().x;
        mWeapon->location().setPos(pos);
    }
}

void StateGust::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
    if (mWeapon.isAlive() && !mIsWeaponHit) {
        if (mWeapon->mapColl().isHit()) {
            mIsWeaponHit = true;
        }
    }
}

void StateGust::createWeapon() {
    const TornadoParam& param = obj().param().tornado();
    hel::math::Vector3 heroPos = static_cast<const Hero&>(obj()).location().pos();
    hel::math::Vector2 pos = heroPos.getXY();
    hel::math::Vector2 offset = mIsUp ? hel::math::Vector2::BASIS_Y * param._D4 : hel::math::Vector2::BASIS_Y * param._D8;
    hel::math::Vector2 weaponPos = pos + offset;
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0x5B);
    desc.mVariation = !mIsUp;
    desc.mFlag = static_cast<ostop::Flag>(1);
    desc.mPos = weaponPos;
    desc._14 = pos;
    desc._1c = hel::math::Vector2::ZERO;
    desc.mOwner = &obj().objColl().objColl().owner();
    mWeapon = obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::hero::tornado
