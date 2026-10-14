#include "scn/step/hero/superhammer/SuperHammer.h"
#include "g3d/ResFileRepository.h"
#include "gobj/G3DAnimDataReposDesc.h"
#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityCustomBaseInfo.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/super/Utility.h"
#include "scn/step/hero/superhammer/StateAttack.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace superhammer {

SuperHammer::SuperHammer(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
    super::Utility::InitFuel(hero);
}

SuperHammer::~SuperHammer() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x1B);
    }
}

void SuperHammer::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/superhammer/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x1B, motion);
    {
        gobj::GearModelDesc desc;
        gobj::NodeReposDesc nodes;
        nodes.mCount = 1;
        const char* names[] = { "StarJ" };
        nodes.mNames = names;
        desc.mNodes = nodes;
        mHero.model().hat().set("step/chara/hero/kirby/superhammer/Hat", desc);
    }
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x2D9), 0);
    {
        gobj::GearModelDesc desc;
        gobj::NodeReposDesc nodes;
        nodes.mCount = 5;
        const char* names[] = { "TopL", "AllL", "Hammer01M", "Hammer02M", "Hammer03M" };
        nodes.mNames = names;
        desc.mNodes = nodes;
        mHero.model().weapon().set("step/chara/hero/kirby/superhammer/Hammer", desc);
    }
    mHero.model().weapon().setNodeVisibility(2, true);
    mHero.model().weapon().setNodeVisibility(3, false);
    mHero.model().weapon().setNodeVisibility(4, false);
    {
        static gobj::GearAnimDesc desc;
        static gobj::G3DAnimDataReposDesc dataDesc;
        static const gobj::G3DAnimDataReposDesc::Entry entries[] = {
            { "Carry", 0 },
            { "SuperAbilityGet", 0 },
            { "SuperAttackStart", 0 },
            { "SuperAttackCharge", 0 },
            { "SuperAttackCharge", 0 },
            { "SuperAttackChargeLvUp", 0 },
            { "SuperAttack01", 0 },
            { "SuperAttack01Hit", 0 },
            { "SuperAttack02", 0 },
            { "SuperAttack02Hit", 0 },
            { "SuperAttack03", 0 },
            { "SuperAttack03Hit", 0 },
        };
        desc._C = 1;
        dataDesc._4 = 12;
        dataDesc._0 = 1;
        dataDesc._8 = entries;
        reinterpret_cast<gobj::G3DAnimDataReposDesc&>(desc) = dataDesc;
        mHero.model().weapon().setAnim("step/chara/hero/kirby/superhammer/Hammer", desc);
    }
    mHero.model().subAnimControl().setLiftUpRHand(true);
    mHero.model().weapon().model().setIsParentScaleIgnore(true);
    mIsSetup = true;
}

bool SuperHammer::tryToChangeState() {
    return StateAttack::TryToChangeState(&mHero);
}

void SuperHammer::onShowHero() {
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x2D9), 0);
    super::Utility::OnShowHero(mHero);
}

void SuperHammer::onHideHero() {
    mHero.model().hat().effect().releaseAndVanish();
    super::Utility::OnHideHero(mHero);
}

void SuperHammer::onStateEndCleanUp() {
    if (mHero.model().weapon().isValid()) {
        mHero.model().weapon().setNodeVisibility(2, true);
        mHero.model().weapon().setNodeVisibility(3, false);
        mHero.model().weapon().setNodeVisibility(4, false);
        if (!mHero.wearBack().isBack()) {
            mHero.model().weapon().anim().clear();
        }
    }
}

void SuperHammer::procAnim() {
    super::Utility::SuperLeakFuel(mHero);
}

bool SuperHammer::isDepleted() const {
    return mHero.abilityManager().getFuel() == 0;
}

}}}}  // namespace scn::step::hero::superhammer
