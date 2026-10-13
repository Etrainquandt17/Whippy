#include "scn/step/weapon/leaperexp/StateMain.h"

#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/leaperexp/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace leaperexp {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().leaperExp();
    obj().culling().setValid(false);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x382), obj().location().pos());
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1A9));
    obj().objColl().addAttack(0, param._4);
    obj().comp().objStopManager().requestStopPowerful(param._C);
}

void StateMain::procAnim() {
    const Param& param = obj().param().leaperExp();
    _8++;
    if (_8 == param._8) {
        obj().objColl().clearAttack();
    }
    if (_8 == param._0) {
        obj().dead();
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::leaperexp
