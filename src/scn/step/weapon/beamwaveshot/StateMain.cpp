#include "scn/step/weapon/beamwaveshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/beamwaveshot/Param.h"
#include "scn/step/weapon/beamwaveshot/StateExplosion.h"

namespace scn {
namespace step {
namespace weapon {
namespace beamwaveshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x5B));
    obj().objColl().addAttack(0, obj().param().beamWaveShot()._0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x40), 0);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    if (++_8 >= obj().param().beamWaveShot()._4) {
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().airAccelFall(obj().target().isRightDir(), gobj::MoveParamAccel::Zero(), gobj::MoveParamFall::Zero());
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (Utility::PenetrationWeaponMapCollHit(obj())) {
        obj().stateChanger().setNextState<StateExplosion, Weapon*>(objPtr());
    }
}

}}}}  // namespace scn::step::weapon::beamwaveshot
