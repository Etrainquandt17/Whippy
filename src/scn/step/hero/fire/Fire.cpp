#include "scn/step/hero/fire/Fire.h"
#include "g3d/ResFileRepository.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/FireParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/fire/StateFireBreath.h"
#include "scn/step/hero/fire/StateFireBurning.h"
#include "scn/step/hero/fire/StateFireRolling.h"
#include "scn/step/hero/fire/StateFireSpiral.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

Fire::Fire(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false)
    , mIsHatFire(false)
    , mBurningCount(0) {
}

Fire::~Fire() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(5);
    }
}

void Fire::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/fire/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(5, motion);
    mHero.model().hat().set(modeldesc::Fire::HatPath(), modeldesc::Fire::HatModel());
    requestHatFire();
    mIsSetup = true;
}

bool Fire::tryToChangeState() {
    if (mHero.water().isInWater()) {
        return false;
    }
    if (mHero.stateChecker().isFloat()) {
        return false;
    }
    if (!isContinueBurning() && StateFireRolling::TryToChangeState(&mHero)) {
        return true;
    }
    if (StateFireBurning::TryToChangeState(&mHero, mBurningCount)) {
        mBurningCount++;
        return true;
    }
    if (StateFireSpiral::TryToChangeState(&mHero) || StateFireBreath::TryToChangeState(&mHero)) {
        endContinueBurning();
        return true;
    }
    return false;
}

void Fire::onShowHero() {
    requestHatFire();
}

void Fire::onHideHero() {
    releaseHatFire();
}

void Fire::procAnim() {
    if (mIsSetup && mHero.abilityManager().isStarted()) {
        if (mHero.footState().isGround()) {
            endContinueBurning();
        }
        if (mHero.isVisible()) {
            if (mHero.water().isInWater()) {
                releaseHatFire();
            } else {
                requestHatFire();
            }
        }
    }
}

bool Fire::isContinueBurning() {
    return mBurningCount != 0;
}

void Fire::endContinueBurning() {
    mBurningCount = 0;
}

void Fire::requestHatFire() {
    if (!mIsHatFire && mHero.model().hat().isValid()) {
        mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x176), 1);
        Hero& hero = mHero;
        mHero.model().hat().effectWarp().requestN(static_cast<effect::Kind>(0x5CF), 2,
            hel::math::Vector3(0.0f, mHero.param().fire()._E0, hero.param().fire()._DC), hero.param().fire()._E4);
        mIsHatFire = true;
    }
}

void Fire::releaseHatFire() {
    if (mIsHatFire && mHero.model().hat().isValid()) {
        mHero.model().hat().effect().release();
        mHero.model().hat().effectWarp().release();
        mIsHatFire = false;
    }
}

}
}
}
}
