#include "scn/step/hero/sleep/Sleep.h"
#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "scn/step/hero/sleep/StateSleepSleep.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sleep {

Sleep::Sleep(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Sleep::~Sleep() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0xA);
    }
}

void Sleep::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/sleep/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0xA, motion);
    mHero.model().hat().set(modeldesc::Sleep::HatPath(), modeldesc::Sleep::HatModel());
    mHero.model().hat().addDynamics(modeldesc::Sleep::HatDyna());
    if (mHero.carryItemUser().isItemExist()) {
        mHero.carryItemUser().set_48(0);
        mHero.carryItemUser().clearTargetItem();
    }
    mIsSetup = true;
}

bool Sleep::tryToChangeState() {
    mHero.stateChanger().setNextState<StateSleepSleep, Hero*>(&mHero);
    return true;
}

void Sleep::onStartClearDanceExternal() {
    clearAbility();
}

void Sleep::onGetEventItem() {
    clearAbility();
}

void Sleep::onStartDemo() {
    clearAbility();
}

void Sleep::clearAbility() {
    mHero.effect()._58.releaseAndVanish();
    mHero.effect()._80.releaseAndVanish();
    mHero.abilityManager().clearAbility();
}

}}}}  // namespace scn::step::hero::sleep
