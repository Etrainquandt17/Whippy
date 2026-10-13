#include "scn/step/weapon/HitStopCallback.h"

#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

HitStopCallback::HitStopCallback(Weapon& weapon) : mObj(weapon) {}

HitStopCallback::~HitStopCallback() {}

void HitStopCallback::onStart() {
    mObj.effect().onHitStopStart();
    mObj.model().onHitStopStart();
}

void HitStopCallback::onEnd() {
    mObj.model().onHitStopEnd();
    mObj.effect().onHitStopEnd();
}

}
}
}
