#include "scn/step/weapon/hammerhammer/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/hammerhammer/Param.h"
#include "scn/step/weapon/hammerhammer/StateExplosion.h"

namespace scn {
namespace step {
namespace weapon {
namespace hammerhammer {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(-45.0f * obj().target().getSign()), _C(0.0f) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xC2));
    obj().objColl().setAttackCenter(0, hel::math::Vector2::ZERO);
    obj().objColl().addAttack(0, obj().param().hammerHammer()._0);
    obj().setDarknessLightVisibility(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x2C4), 2);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    f32 speed = obj().param().hammerHammer()._4;
    _C += speed * obj().target().getSign();
    if (_C > 360.0f) {
        _C = 0.0f;
    }
    obj().model().rotCtrl().setRotH(_8);
    obj().model().rotCtrl().setRotD(90.0f);
    obj().model().rotCtrl().setRotV(-_C);
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide() || obj().objColl().attack().isCollideGimmick()) {
        explode();
    } else if (obj().mapColl().isHit()) {
        explode();
    }
}

void StateMain::explode() {
    obj().stateChanger().setNextState<StateExplosion, Weapon*>(objPtr());
}

}
}
}
}
