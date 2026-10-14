#include "scn/step/weapon/dededehammer/StateMain.h"

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
#include "scn/step/weapon/dededehammer/Param.h"
#include "scn/step/weapon/dededehammer/StateExplosion.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace dededehammer {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(-45.0f * obj().target().getSign()), _10(0.0f) {
    const Param& param = obj().param().dededeHammer();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x148));
    obj().objColl().setAttackCenter(0, Vector2::ZERO);
    obj().objColl().addAttack(0, param._0, Vector2(param._4, 0.0f), Vector2(param._8, 0.0f));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0xFF), 1);
    obj().setDarknessLightVisibility(false);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    const Param& param = obj().param().dededeHammer();
    _8++;
    if (_8 > param._10) {
        explode();
    } else {
        _10 += param._C * obj().target().getSign();
        if (_10 > 360.0f) {
            _10 = 0.0f;
        }
        obj().model().rotCtrl().setRotH(_C);
        obj().model().rotCtrl().setRotD(90.0f);
        obj().model().rotCtrl().setRotV(-_10);
    }
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

}}}}  // namespace scn::step::weapon::dededehammer
