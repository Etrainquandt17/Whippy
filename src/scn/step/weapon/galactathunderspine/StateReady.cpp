#include "scn/step/weapon/galactathunderspine/StateReady.h"

#include "scn/step/chara/Location.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactathunderspine {

StateReady::StateReady(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    hel::math::Vector3 pos = obj().location().pos();
    pos.y += 5.5f;
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x19E), pos);
}

void StateReady::procAnim() {
    if (++mFrame == 180) {
        obj().dead();
    }
}

void StateReady::procMove() {}

void StateReady::procFixPos() {}

}
}
}
}
