#include "scn/step/hero/mike/Mike.h"
#include "g3d/ResFileRepository.h"
#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/mike/StateAttack.h"
#include "scn/step/hero/mike/StateCharge.h"
#include "scn/step/hero/mike/utility/Hat.h"
#include "scn/step/hero/mike/utility/Mike.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

namespace scn {
namespace step {
namespace hero {
namespace mike {

Mike::Mike(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Mike::~Mike() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x17);
    }
}

void Mike::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/mike/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x17, motion);
    mHero.model().hat().set(modeldesc::Mike::HatPath(), modeldesc::Mike::HatModel());
    utility::Hat::Wait(mHero);
    mHero.model().weapon().set(modeldesc::Mike::MikePath(), modeldesc::Mike::MikeModel());
    mHero.model().weapon().setAnim(modeldesc::Mike::MikePath(), modeldesc::Mike::MikeAnim());
    utility::Mike::Clear(mHero);
    mIsSetup = true;
}

bool Mike::tryToChangeState() {
    if (mHero.water().isInWater()) {
        return false;
    }
    if (mHero.stateChecker().isFloat()) {
        return false;
    }
    if (StateAttack::TryToChangeState(&mHero) || StateCharge::TryToChangeState(&mHero)) {
        return true;
    }
    return false;
}

}
}
}
}
