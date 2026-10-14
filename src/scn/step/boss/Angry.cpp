#include "scn/step/boss/Angry.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/chara/HitPoint.h"

using hel::common::Traits;

namespace scn {
namespace step {
namespace boss {

Angry::Angry(Boss& boss) : mBoss(boss), mIsAngry(false), mAngryHpRate(0.5f), mIsChangeBrain(false), mBrainName() {}

Angry::~Angry() {}

bool Angry::check() {
    if (mIsAngry) {
        return false;
    }
    if (mBoss.hitPoint().isDead()) {
        return false;
    }
    if (mBoss.hitPoint().rate() <= mAngryHpRate) {
        mIsAngry = true;
        if (mIsChangeBrain) {
            mBoss.brainCtrl().set(mBrainName);
        }
        return true;
    }
    return false;
}

bool Angry::isAngry() const {
    return mIsAngry;
}

void Angry::setAngryHpRate(float rate) {
    mAngryHpRate = rate;
}

float Angry::getAngryHpRate() const {
    return mAngryHpRate;
}

void Angry::setChangeBrain(const char* name) {
    mIsChangeBrain = true;
    // TODO: an assignment of the string in the original; hel::common::FixedStringIN has none yet.
    Traits<char>::Strncpy(const_cast<char*>(static_cast<const char*>(mBrainName)), name, 128);
}

}}}  // namespace scn::step::boss
