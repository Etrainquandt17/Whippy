#ifndef SCN_STEP_CARRYITEM_PARAM_H
#define SCN_STEP_CARRYITEM_PARAM_H

#include "param/JITParam.h"
#include "scn/step/carryitem/abilitystar/Param.h"
#include "scn/step/carryitem/balloonbomb/Param.h"
#include "scn/step/carryitem/common/Param.h"
#include "scn/step/carryitem/cracker/Param.h"
#include "scn/step/carryitem/invisiblestone/Param.h"
#include "scn/step/carryitem/lockkey/Param.h"
#include "scn/step/carryitem/mtomatobox/Param.h"
#include "scn/step/carryitem/prismshield/Param.h"
#include "scn/step/carryitem/repairparts/Param.h"
#include "scn/step/carryitem/stepshoe/Param.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

class Param {
public:
    Param();

    const common::Param& common() const;
    const mtomatobox::Param& mtomatoBox() const;
    const cracker::Param& cracker() const;
    const lockkey::Param& lockKey() const;
    const invisiblestone::Param& invisibleStone() const;
    const abilitystar::Param& abilityStar() const;
    const balloonbomb::Param& balloonBomb() const;
    const stepshoe::Param& stepShoe() const;
    const prismshield::Param& prismShield() const;
    const repairparts::Param& repairparts() const;

private:
    param::JITParam mCommon;
    param::JITParam mMTomatoBox;
    param::JITParam mCracker;
    param::JITParam mLockKey;
    param::JITParam mInvisibleStone;
    param::JITParam mAbilityStar;
    param::JITParam mBalloonBomb;
    param::JITParam mStepShoe;
    param::JITParam mPrismShield;
    param::JITParam mRepairParts;
};

}}}  // namespace scn::step::carryitem

#endif
