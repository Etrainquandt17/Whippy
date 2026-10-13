#include "scn/step/hero/leaf/StateDisorderShot.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/LeafParam.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

namespace {

inline const LeafParamDisorderShot& param(Hero& hero) {
    return hero.param().leaf()._54;
}


}

bool StateDisorderShot::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isHold(4) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateDisorderShot, Hero*>(hero);
        return true;
    }
    return false;
}

StateDisorderShot::StateDisorderShot(Hero* hero)
    : StateBase(hero)
    , mCount(0)
    , mIsRightDir(false) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    mIsRightDir = obj().target().isRightDir();
    obj().model().script().start(0xA0);
    obj().move().setSpeedV(param(obj())._24);
}

StateDisorderShot::~StateDisorderShot() {
    const LeafParamDisorderShot& p = param(obj());
    obj().abilityManager().setActionInterval(p._30);
}

void StateDisorderShot::procAnim() {
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    if (mCount < param(obj())._20) {
        hel::math::Vector2 pos = static_cast<const Hero&>(obj()).location().pos().getXY();
        pos.y += param(obj())._2C;
        hel::math::Vector2 dir(0.0f, -1.0f);
        dir.rotate(0.017453292f * param(obj())._0[mCount]);
        dir.x *= mIsRightDir ? 1.0f : -1.0f;
        dir *= param(obj())._28;
        weapon::Desc desc(static_cast<weapon::Kind>(0xA), 0, static_cast<ostop::Flag>(1), pos, dir,
                          obj().objColl().objColl().owner());
        obj().comp().weaponManager().request(desc);
        obj().soundSE()._EC.start(0x1BE);
        mCount++;
    }
}

void StateDisorderShot::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateDisorderShot::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
