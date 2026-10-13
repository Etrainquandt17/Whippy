#include "scn/step/hero/superice/SuperIce.h"
#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityCustomBaseInfo.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/super/Utility.h"
#include "scn/step/hero/superice/Custom.h"
#include "scn/step/hero/superice/StateAttack.h"

namespace scn {
namespace step {
namespace hero {
namespace superice {

SuperIce::SuperIce(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
    super::Utility::InitFuel(hero);
}

SuperIce::~SuperIce() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x1C);
    }
}

void SuperIce::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/superice/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x1C, motion);
    gobj::GearModelDesc desc;
    desc._0 = "SuperIceHat";
    const char* names[] = { "TopL", "StarJ" };
    desc.mNodes.mCount = 2;
    desc.mNodes.mNames = names;
    mHero.model().hat().set("step/chara/hero/kirby/superice/Hat", desc);
    mHero.abilityManager().customSuperIce().snowBall().setup();
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x313), 1);
    mIsSetup = true;
}

bool SuperIce::tryToChangeState() {
    return StateAttack::TryToChangeState(&mHero);
}

void SuperIce::onShowHero() {
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x313), 1);
    super::Utility::OnShowHero(mHero);
}

void SuperIce::onHideHero() {
    mHero.model().hat().effect().releaseAndVanish();
    super::Utility::OnHideHero(mHero);
}

void SuperIce::onStateEndCleanUp() {
}

void SuperIce::procAnim() {
    super::Utility::SuperLeakFuel(mHero);
}

bool SuperIce::isDepleted() const {
    return mHero.abilityManager().getFuel() == 0;
}

}}}}  // namespace scn::step::hero::superice
