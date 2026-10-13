#include "scn/step/weapon/landiacannon/StateMain.h"

#include "gobj/Anim.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/landiacannon/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiacannon {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().landiaCannon();
    obj().setVisibility(true);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x10E));
    obj().objColl().addAttack(0, param._0);
    obj().model().setBaseScale(hel::math::Vector3::ALL_ONE * param._8);
    hel::math::Vector2 velocity = obj().move().velocity().getXY();
    velocity *= param._4;
    obj().move().setVelocity(velocity.toVector3());
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x80), 0);
    obj().model().anim().setFrame(0.0f);
}

void StateMain::procAnim() {}

void StateMain::procMove() {
    if (obj().isVisible()) {
        const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
        obj().move().decel(decel);
    }
}

void StateMain::procFixPos() {
    if (obj().isVisible() && Utility::CheckShootingCulling(obj(), 5.0f)) {
        setInvisible();
    }
}

void StateMain::procObjCollReact() {}

void StateMain::setInvisible() {
    obj().setVisibility(false);
    obj().effect().normal().release();
    obj().objColl().clearAttack();
    obj().move().resetVelocity();
}

}}}}  // namespace scn::step::weapon::landiacannon
