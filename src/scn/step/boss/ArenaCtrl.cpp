#include "scn/step/boss/ArenaCtrl.h"

#include "hel/common/Color.h"
#include "scn/step/Component.h"
#include "scn/step/core/PauseTrigger.h"
#include "scn/step/core/SceneChanger.h"
#include "scn/step/sfx/ScreenFade.h"

using hel::common::Color;

namespace scn {
namespace step {
namespace boss {

ArenaCtrl::ArenaCtrl(Component& component) : mComponent(component), mIsNextScene(false), mIsFade(false), mDelay(150), mEntryId() {}

void ArenaCtrl::setNextScene(bool isFade) {
    mIsNextScene = true;
    mIsFade = isFade;
    stopTime();
}

void ArenaCtrl::setNextSceneWithAdditionalDelay(u32 delay) {
    mDelay += delay;
    setNextScene(true);
}

void ArenaCtrl::update() {
    if (!mIsNextScene) {
        return;
    }
    if (mDelay != 0) {
        mDelay--;
        if (mDelay == 35) {
            if (mIsFade) {
                mComponent.screenFade().setColor(Color(0, 0, 0, 255));
                mComponent.screenFade().setFadeOut(30);
            }
            mComponent.pauseTrigger().setIsEnable(core::PauseTrigger::ENABLE_KIND_8, false);
        }
    } else {
        mComponent.sceneChanger().changeBossClearArena();
    }
}

void ArenaCtrl::stopTime() {
    if (!mEntryId.isValid()) {
        mComponent.arenaManager().timeStopEntry(mEntryId);
    }
}

void ArenaCtrl::startTime() {
    if (mEntryId.isValid()) {
        mComponent.arenaManager().timeStopRelease(mEntryId);
        mEntryId = arena::EntryManager::EntryId();
    }
}

}}}  // namespace scn::step::boss
