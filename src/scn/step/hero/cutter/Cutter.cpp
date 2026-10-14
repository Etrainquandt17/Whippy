#include "scn/step/hero/cutter/Cutter.h"
#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/cutter/StateCutterCatch.h"
#include "scn/step/hero/cutter/StateCutterCharge.h"
#include "scn/step/hero/cutter/StateCutterDashCutter.h"
#include "scn/step/hero/cutter/StateCutterDrop.h"
#include "scn/step/hero/cutter/StateCutterFinalCutterRise.h"
#include "scn/step/hero/cutter/StateCutterSlash1.h"
#include "scn/step/hero/cutter/StateCutterSlash2.h"
#include "scn/step/hero/cutter/StateCutterSweepCutter.h"
#include "scn/step/hero/cutter/StateCutterThrow.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace cutter {

Cutter::Cutter(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Cutter::~Cutter() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(2);
    }
}

void Cutter::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/cutter/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(2, motion);
    mHero.model().hat().set(modeldesc::Cutter::HatPath(), modeldesc::Cutter::HatModel());
    mHero.model().weapon().set(modeldesc::Cutter::CutterPath());
    mHero.model().weapon().setVisibility(false);
    mIsSetup = true;
}

bool Cutter::tryToChangeState() {
    if (mHero.water().isInWater()) {
        return false;
    }
    if (mHero.stateChecker().isFloat()) {
        return false;
    }
    if (StateCutterDashCutter::TryToChangeState(&mHero) || StateCutterFinalCutterRise::TryToChangeState(&mHero)
        || StateCutterSlash2::TryToChangeState(&mHero) || StateCutterSlash1::TryToChangeState(&mHero)
        || StateCutterDrop::TryToChangeState(&mHero) || StateCutterThrow::TryToChangeState(&mHero)
        || StateCutterSweepCutter::TryToChangeState(&mHero) || StateCutterCharge::TryToChangeState(&mHero)
        || StateCutterCatch::TryToChangeState(&mHero)) {
        return true;
    }
    return false;
}

void Cutter::onStateEndCleanUp() {
    if (mHero.model().weapon().isValid()) {
        mHero.model().weapon().setVisibility(false);
    }
    if (mHero.model().hat().isValid()) {
        mHero.model().hat().setNodeVisibility(1, true);
    }
}

}}}}  // namespace scn::step::hero::cutter
