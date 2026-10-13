#include "scn/step/weapon/Effect.h"

#include "gobj/GearModel.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

Effect::Effect(Weapon& weapon)
    : mObj(weapon), mNormal(weapon.comp(), weapon.model().model().nodes(), static_cast<effect::DrawPriority>(0)),
      mWarp(weapon.comp(), weapon.model().model().nodes(), static_cast<effect::DrawPriority>(0)) {
    mWarp.changeLayer(static_cast<core::DrawLayerKind>(2));
}

chara::Effect& Effect::normal() {
    return mNormal;
}

chara::Effect& Effect::warp() {
    return mWarp;
}

void Effect::onHitStopStart() {
    mNormal.requestPause();
    mWarp.requestPause();
}

void Effect::onHitStopEnd() {
    mWarp.requestUnpause();
    mNormal.requestUnpause();
}

void Effect::onObjStopStarted() {
    onHitStopStart();
}

void Effect::onObjStopFinished() {
    onHitStopEnd();
}

}
}
}
