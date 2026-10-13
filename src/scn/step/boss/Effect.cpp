#include "scn/step/boss/Effect.h"

#include "gobj/GearModel.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {

Effect::Effect(Boss& boss)
    : mBoss(boss), mSuper(boss.comp(), boss.model().model().nodes(), static_cast<effect::DrawPriority>(3)), mNormal(boss.comp(), boss.model().model().nodes(), static_cast<effect::DrawPriority>(3)),
      mNormalWarp(boss.comp(), boss.model().model().nodes(), static_cast<effect::DrawPriority>(3)), mState(boss.comp(), boss.model().model().nodes(), static_cast<effect::DrawPriority>(3)),
      mStateWarp(boss.comp(), boss.model().model().nodes(), static_cast<effect::DrawPriority>(3)), mStateBack(boss.comp(), boss.model().model().nodes(), static_cast<effect::DrawPriority>(3)),
      mBack(boss.comp(), boss.model().model().nodes(), static_cast<effect::DrawPriority>(3)), mFore(boss.comp(), boss.model().model().nodes(), static_cast<effect::DrawPriority>(3)) {
    mNormalWarp.changeLayer(static_cast<core::DrawLayerKind>(2));
    mStateWarp.changeLayer(static_cast<core::DrawLayerKind>(2));
    mBack.changeLayer(static_cast<core::DrawLayerKind>(5));
    mStateBack.changeLayer(static_cast<core::DrawLayerKind>(5));
    mFore.changeLayer(core::DRAW_LAYER_KIND_8);
}

chara::Effect& Effect::super() {
    return mSuper;
}

chara::Effect& Effect::normal() {
    return mNormal;
}

chara::Effect& Effect::normalWarp() {
    return mNormalWarp;
}

chara::Effect& Effect::state() {
    return mState;
}

chara::Effect& Effect::stateWarp() {
    return mStateWarp;
}

chara::Effect& Effect::stateBack() {
    return mStateBack;
}

chara::Effect& Effect::back() {
    return mBack;
}

chara::Effect& Effect::fore() {
    return mFore;
}

void Effect::onStateChange() {
    mState.release();
    mStateWarp.release();
    mStateBack.release();
}

void Effect::onHitStopStart() {
    mSuper.requestPause();
    mNormal.requestPause();
    mNormalWarp.requestPause();
    mState.requestPause();
    mStateWarp.requestPause();
    mStateBack.requestPause();
    mBack.requestPause();
    mFore.requestPause();
}

void Effect::onHitStopEnd() {
    mFore.requestUnpause();
    mBack.requestUnpause();
    mStateBack.requestUnpause();
    mStateWarp.requestUnpause();
    mState.requestUnpause();
    mNormalWarp.requestUnpause();
    mNormal.requestUnpause();
    mSuper.requestUnpause();
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
