#include "scn/step/weapon/beamshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/beamshot/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace beamshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().setValidAttackRumble(true);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x58));
    obj().objColl().addAttack(0, obj().param().beamShot()._0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x36), 0);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    const Param& param = obj().param().beamShot();
    _8++;
    if (_8 >= param._4) {
        obj().dead();
    }
    f32 rate = static_cast<f32>(_8) / (static_cast<f32>(param._4) - 1.0f);
    f32 scale = param._C * rate + param._8;
    obj().model().setScale(hel::math::Vector3::ALL_ONE * scale);
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollideGimmick()) {
        obj().dead();
    }
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::beamshot
