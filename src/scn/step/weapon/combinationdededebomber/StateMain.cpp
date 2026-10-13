#include "scn/step/weapon/combinationdededebomber/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/combinationdededebomber/StateExplosion.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationdededebomber {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(0) {
    _C = obj().variation();
    obj().model().setScale(hel::math::Vector3::ALL_ONE * param()._4);
    f32 scale = param()._8;
    obj().effect().normal().requestN(static_cast<effect::Kind>(0xFA), 0, scale);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0xFC), 0, scale);
    f32 radius = param()._0;
    obj().objColl().setAttackType(attackType());
    obj().objColl().addAttack(0, radius);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    _8++;
    if (_8 > obj().param().combinationDededeBomber()._24) {
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().decel(obj().param().combinationDededeBomber()._38);
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (Utility::PenetrationWeaponMapCollHit(obj())) {
        obj().effect().normal().releaseAndVanish();
        obj().stateChanger().setNextState<StateExplosion, Weapon*>(objPtr());
    }
}

const LevelParam& StateMain::param() const {
    const Param& param = obj().param().combinationDededeBomber();
    switch (_C) {
    case 0:
        return param._0;
    case 1:
        return param._C;
    case 2:
        return param._18;
    default:
        return param._0;
    }
}

const ocoll::AttackType& StateMain::attackType() const {
    switch (_C) {
    case 0:
        return static_cast<ocoll::AttackType>(0x19);
    case 1:
        return static_cast<ocoll::AttackType>(0x1A);
    case 2:
        return static_cast<ocoll::AttackType>(0x1B);
    default:
        return static_cast<ocoll::AttackType>(0x19);
    }
}

}}}}  // namespace scn::step::weapon::combinationdededebomber
