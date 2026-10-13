#include "scn/step/weapon/mahoroaicicle/StateFloorHit.h"

#include "gobj/Move.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaicicle {

StateFloorHit::StateFloorHit(Weapon* weapon) : StateBase(weapon), mWait(20) {
    obj().move().resetVelocity();
    obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    obj().soundSE().start(0x42A);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x40C), 0);
    obj().model().setViewOffset(hel::math::Vector3(0.0f, -0.5f, 0.0f));
}

StateFloorHit::~StateFloorHit() {
    obj().model().resetViewOffset();
}

void StateFloorHit::procAnim() {
    if (mWait != 0) {
        mWait--;
    } else {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x40B), obj().location().pos());
        obj().comp().permSoundSE().start(0x42B);
        obj().dead();
    }
}

void StateFloorHit::procMove() {}

void StateFloorHit::procFixPos() {}

}
}
}
}
