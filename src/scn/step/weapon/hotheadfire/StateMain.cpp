#include "scn/step/weapon/hotheadfire/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace hotheadfire {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().model().reqScript(0);
    Matrix34 mtx;
    f32 rot = 90.0f;
    if (obj().target().isRightDir()) {
        rot = -90.0f;
    }
    mtx = Matrix34::CreateRotAxisDeg(Vector3::BASIS_Y, rot);
    obj().model().setCustomMtx(mtx);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x237));
    obj().objColl().addAttack(0, 0.35f);
    obj().objColl().addHit(0, 0.35f);
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x127), obj().location().pos());
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (++_8 == 180 || obj().objColl().hit().isCollide() || obj().objColl().attack().isCollideGimmick() || obj().objColl().attack().isCollide()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x127), obj().location().pos());
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::hotheadfire
