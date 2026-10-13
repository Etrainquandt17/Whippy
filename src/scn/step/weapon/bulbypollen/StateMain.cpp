#include "scn/step/weapon/bulbypollen/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace bulbypollen {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x19B));
    obj().objColl().addAttack(0, 0.2f);
    obj().objColl().addHit(0, 0.2f);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x377), 0);
}

StateMain::~StateMain() {
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x378), 0);
}

void StateMain::procAnim() {
    if (++_8 >= 60) {
        dead();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide() || obj().objColl().hit().isCollide() || obj().objColl().attack().isCollideGimmick() || obj().mapColl().isHit()) {
        dead();
    }
}

void StateMain::dead() {
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x378), 0);
    obj().dead();
}

}
}
}
}
