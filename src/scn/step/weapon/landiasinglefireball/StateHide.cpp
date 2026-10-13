#include "scn/step/weapon/landiasinglefireball/StateHide.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglefireball {

StateHide::StateHide(Weapon* weapon) : StateBase(weapon) {
    obj().move().resetVelocity();
}

void StateHide::procAnim() {}

void StateHide::procMove() {}

void StateHide::procFixPos() {}

}
}
}
}
