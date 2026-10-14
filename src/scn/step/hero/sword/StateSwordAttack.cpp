#include "scn/step/hero/sword/StateSwordAttack.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/sword/StateSwordChargeStart.h"
#include "scn/step/hero/sword/StateSwordMince.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"
#include "util/StateChanger.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordAttack::tryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordAttack, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordAttack::StateSwordAttack(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsHold(true)
    , mIsHit(false)
    , mIsEnd(false) {
    obj().footState().setGround();
    obj().model().script().start(0x76);
    obj().objColl().objColl().setSearchHitTeamXlu(-3);
}

StateSwordAttack::~StateSwordAttack() {
    obj().effect()._58.releaseAndVanish();
}

void StateSwordAttack::procAnim() {
    const SwordParam& param = obj().param().sword();
    mFrame++;
    if (mIsHold && !obj().hid().isHold(0x20)) {
        mIsHold = false;
    }
    if (!mIsHit && mFrame == param._0 && obj().hitPoint().isFull()) {
        Vector2 pos = static_cast<const Hero&>(obj()).location().pos().getXY();
        pos.y += param._8;
        Vector2 weaponPos = pos;
        weaponPos.x += param._4 * obj().target().getSign();
        Vector2 speed(param._C * obj().target().getSign(), 0.0f);
        weapon::Desc desc(static_cast<weapon::Kind>(5), 0, static_cast<ostop::Flag>(1), weaponPos, pos, speed,
                          obj().objColl().objColl().owner());
        obj().comp().weaponManager().request(desc);
        obj().soundSE()._4.start(0x182);
    }
    if (mIsEnd && StateSwordMince::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        if (mIsEnd) {
            obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
        } else if (mIsHold) {
            obj().stateChanger().setNextState<StateSwordChargeStart, Hero*>(objPtr());
        } else {
            obj().model().script().start(0x77);
            mIsEnd = true;
        }
    }
}

void StateSwordAttack::procMove() {
    Utility::MoveDefaultActionNoOnIce(obj());
}

void StateSwordAttack::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

bool StateSwordAttack::procObjCollReact() {
    if (Utility::IsSearchCollideNoStarEffect(obj())) {
        mIsHit = true;
        return false;
    }
    return false;
}

}}}}  // namespace scn::step::hero::sword
