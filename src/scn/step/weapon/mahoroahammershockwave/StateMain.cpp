#include "scn/step/weapon/mahoroahammershockwave/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroahammershockwave {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mLifetime(), mPrevPosX(weapon->location().pos().x) {
    obj().mapColl().setValid(false);
    mLifetime.set(300);
    obj().model().rotCtrl().setValid(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x407), 0);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x205));
    obj().objColl().addAttack(0, 0.25f, hel::math::Vector2(0.0f, 2.5f), hel::math::Vector2(0.0f, 0.0f));
    obj().objColl().setAttackCenter(0, hel::math::Vector2::ZERO);
}

void StateMain::procAnim() {
    mLifetime.update();
    if (mLifetime.isDead()) {
        obj().dead();
        return;
    }
    if (hel::math::Math::Abs(obj().location().pos().x - mPrevPosX) >= 2.0f) {
        ::ocoll::Owner& owner = obj().objColl().owner();
        Desc desc(static_cast<Kind>(0x95), 0, static_cast<ostop::Flag>(8), obj().location().pos().getXY(), hel::math::Vector2::ZERO, owner);
        obj().comp().weaponManager().request(desc);
        mPrevPosX = obj().location().pos().x;
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

}
}
}
}
