#include "scn/step/boss/BarrierInvincible.h"

#include "scn/step/chara/DamageInfo.h"

namespace scn {
namespace step {
namespace boss {

BarrierInvincible::BarrierInvincible(Boss& boss) : mBoss(boss), mIsValid(false) {}

bool BarrierInvincible::isInvincible(const chara::DamageInfo& info) const {
    if (info.data()._48) {
        return false;
    }
    return mIsValid;
}

void BarrierInvincible::setIsValid(bool isValid) {
    mIsValid = isValid;
}

}}}  // namespace scn::step::boss
