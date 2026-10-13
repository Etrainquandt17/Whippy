#include "scn/step/carryitem/Param.h"

namespace scn {
namespace step {
namespace carryitem {

Param::Param()
    : mCommon("step/carryitem/Common")
    , mMTomatoBox("step/carryitem/MTomatoBox")
    , mCracker("step/carryitem/Cracker")
    , mLockKey("step/carryitem/LockKey")
    , mInvisibleStone("step/carryitem/InvisibleStone")
    , mAbilityStar("step/carryitem/AbilityStar")
    , mBalloonBomb("step/carryitem/BalloonBomb")
    , mStepShoe("step/carryitem/StepShoe")
    , mPrismShield("step/carryitem/PrismShield")
    , mRepairParts("step/carryitem/RepairParts") {}

const common::Param& Param::common() const {
    return mCommon.data<common::Param>();
}

const mtomatobox::Param& Param::mtomatoBox() const {
    return mMTomatoBox.data<mtomatobox::Param>();
}

const cracker::Param& Param::cracker() const {
    return mCracker.data<cracker::Param>();
}

const lockkey::Param& Param::lockKey() const {
    return mLockKey.data<lockkey::Param>();
}

const invisiblestone::Param& Param::invisibleStone() const {
    return mInvisibleStone.data<invisiblestone::Param>();
}

const abilitystar::Param& Param::abilityStar() const {
    return mAbilityStar.data<abilitystar::Param>();
}

const balloonbomb::Param& Param::balloonBomb() const {
    return mBalloonBomb.data<balloonbomb::Param>();
}

const stepshoe::Param& Param::stepShoe() const {
    return mStepShoe.data<stepshoe::Param>();
}

const prismshield::Param& Param::prismShield() const {
    return mPrismShield.data<prismshield::Param>();
}

const repairparts::Param& Param::repairparts() const {
    return mRepairParts.data<repairparts::Param>();
}

}}}  // namespace scn::step::carryitem
