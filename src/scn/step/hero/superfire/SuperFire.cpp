#include "scn/step/hero/superfire/SuperFire.h"
#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityCustomBaseInfo.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/super/Utility.h"
#include "scn/step/hero/superfire/StateAttack.h"

namespace scn {
namespace step {
namespace hero {
namespace superfire {

SuperFire::SuperFire(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
    super::Utility::InitFuel(hero);
}

SuperFire::~SuperFire() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x19);
    }
}

void SuperFire::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/superfire/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x19, motion);
    gobj::GearModelDesc desc;
    const char* names[] = { "TopL", "PtclJ", "StarAllJ" };
    desc.mNodes.mCount = 3;
    desc.mNodes.mNames = names;
    mHero.model().hat().set("step/chara/hero/kirby/superfire/Hat", desc);
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x188), 1);
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x189), 2);
    mIsSetup = true;
}

bool SuperFire::tryToChangeState() {
    return StateAttack::TryToChangeState(&mHero);
}

void SuperFire::onShowHero() {
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x188), 1);
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x189), 2);
    super::Utility::OnShowHero(mHero);
}

void SuperFire::onHideHero() {
    mHero.model().hat().effect().releaseAndVanish();
    super::Utility::OnHideHero(mHero);
}

void SuperFire::procAnim() {
    super::Utility::SuperLeakFuel(mHero);
}

bool SuperFire::isDepleted() const {
    return mHero.abilityManager().getFuel() == 0;
}

}
}
}
}
