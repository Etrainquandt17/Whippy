#include "scn/step/boss/HitStopCallback.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {

HitStopCallback::HitStopCallback(Boss& boss) : mBoss(boss) {}

HitStopCallback::~HitStopCallback() {}

void HitStopCallback::onStart() {
    mBoss.effect().onHitStopStart();
    mBoss.gearManager().onHitStopStart();
    mBoss.model().onHitStopStart();
    mBoss.soundSE().onHitStopStart();
    mBoss.custom()->onHitStopStart();
}

void HitStopCallback::onEnd() {
    mBoss.custom()->onHitStopEnd();
    mBoss.soundSE().onHitStopEnd();
    mBoss.model().onHitStopEnd();
    mBoss.gearManager().onHitStopEnd();
    mBoss.effect().onHitStopEnd();
}

}
}
}
