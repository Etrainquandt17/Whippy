#include "scn/step/weapon/leaperthorn/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/leaperthorn/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace leaperthorn {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().mapColl().setValid(true);
}

void StateMain::procAnim() {
    const Param& param = obj().param().leaperThorn();
    _8++;
    if (_8 == 1) {
        obj().model().setVisibility(true);
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x385), 0);
    }
    if (_8 == param._8) {
        obj().objColl().addHit(0, param._4);
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x386), obj().location().pos());
        obj().dead();
    } else if (Utility::CheckShootingCulling(obj())) {
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().hit().isCollide() || obj().objColl().attack().isCollide()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x386), obj().location().pos());
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::leaperthorn
