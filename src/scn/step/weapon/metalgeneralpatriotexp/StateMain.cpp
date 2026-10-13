#include "scn/step/weapon/metalgeneralpatriotexp/StateMain.h"

#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/metalgeneralpatriotexp/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralpatriotexp {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().metalGeneralPatriotExp();
    obj().culling().setValid(false);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x467), obj().location().pos(), param._8);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
    obj().comp().objStopManager().requestStopPowerful(param._14);
}

void StateMain::procAnim() {
    const Param& param = obj().param().metalGeneralPatriotExp();
    _8++;
    if (_8 == param._C) {
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1E0));
        obj().objColl().addAttack(0, param._4);
    }
    if (_8 == param._10) {
        obj().objColl().clearAttack();
    }
    if (_8 == param._0) {
        obj().dead();
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::metalgeneralpatriotexp
