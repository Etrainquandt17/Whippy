#include "scn/step/weapon/StateNormal.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

StateNormal::StateNormal(Weapon* weapon) : StateBase(weapon) {}

StateNormal::~StateNormal() {}

void StateNormal::procAnim() {}

void StateNormal::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Create(0.0f);
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.0f, 0.0f, 0.0f);
    obj().move().airDecelFall(decel, fall);
}

void StateNormal::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

}
}
}
