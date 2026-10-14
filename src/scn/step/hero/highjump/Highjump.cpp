#include "scn/step/hero/highjump/Highjump.h"
#include "dynamics/Desc.h"
#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/highjump/StateCharge.h"
#include "scn/step/hero/highjump/StateRocketFallStart.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace highjump {

Highjump::Highjump(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Highjump::~Highjump() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0xD);
    }
}

void Highjump::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/highjump/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0xD, motion);
    mHero.model().hat().set(modeldesc::Highjump::HatPath(), modeldesc::Highjump::HatModel());
    mHero.model().hat().addDynamics(modeldesc::Highjump::HatDynaL());
    mHero.model().hat().addDynamics(modeldesc::Highjump::HatDynaR());
    mIsSetup = true;
}

bool Highjump::tryToChangeState() {
    if (mHero.water().isInWater()) {
        return false;
    }
    if (mHero.stateChecker().isFloat()) {
        return false;
    }
    if (StateRocketFallStart::tryToChangeState(&mHero) || StateCharge::tryToChangeState(&mHero)) {
        return true;
    }
    return false;
}

}}}}  // namespace scn::step::hero::highjump
