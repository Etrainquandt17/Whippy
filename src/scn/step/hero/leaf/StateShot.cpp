#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#include "scn/step/hero/leaf/StateShot.h"
#include "app/Random.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/LeafParam.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
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

bool StateShot::TryToChangeState(Hero* hero) {
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateShot, Hero*>(hero);
        return true;
    }
    return false;
}

StateShot::StateShot(Hero* hero)
    : StateBase(hero)
    , mWait(0)
    , mShotCount(0) {
    obj().model().setFixDir(true);
    obj().model().script().start(0x99);
    Utility::AirAttackInitSpeedV(obj());
}

StateShot::~StateShot() {
    obj().model().modelRotCtrl().resetRotTarget();
    const LeafParam& param = obj().param().leaf();
    obj().abilityManager().setActionInterval(param._C);
}

void StateShot::procAnim() {
    if (mWait == 0 && mShotCount < obj().param().leaf()._4) {
        hel::math::Vector2 pos = static_cast<const Hero&>(obj()).location().pos().getXY();
        pos.y += app::Random::RandNF() * obj().param().leaf()._0;
        hel::math::Vector2 dir(0.0f, 0.0f);
        weapon::Desc desc(static_cast<weapon::Kind>(9), 0, static_cast<ostop::Flag>(1), pos, dir,
                          obj().objColl().objColl().owner());
        {
            util::ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
            if (weapon.isAlive()) {
                weapon->target().setIsRightDir(obj().target().isRightDir());
                hel::math::Matrix34 mtx =
                    hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3::BASIS_Z, -2.0f + 40.0f * app::Random::RandNF());
                weapon->model().setCustomMtx(mtx);
            }
        }
        mWait = obj().param().leaf()._8;
        mShotCount++;
    }
    mWait--;
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateShot::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateShot::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::leaf
