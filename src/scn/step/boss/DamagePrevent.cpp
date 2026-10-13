#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "scn/step/boss/DamagePrevent.h"

namespace scn {
namespace step {
namespace boss {

DamagePrevent::DamagePrevent(Boss& boss) : mBoss(boss), mTargets() {}

DamagePrevent::~DamagePrevent() {}

u32 DamagePrevent::calcDamage(u32 damage, ocoll::AttackType type) {
    if (damage == 0) {
        return 0;
    }
    for (u32 i = 0; i < mTargets.count(); i++) {
        if (mTargets[i].mType == type) {
            f32 rate = mTargets[i].mRate;
            damage = damage * rate;
            if (damage == 0) {
                damage = 1;
            }
            break;
        }
    }
    return damage;
}

void DamagePrevent::addPreventTarget(ocoll::AttackType type, f32 rate) {
    for (u32 i = 0; i < mTargets.count(); i++) {
        if (mTargets[i].mType == type) {
            mTargets[i].mRate = rate;
            return;
        }
    }
    if (!mTargets.isFull()) {
        mTargets.add(PreventTargetData(type, rate));
    }
}

// TODO: the link dropped this function; the body is a guess.
void DamagePrevent::removePreventTarget(ocoll::AttackType type) {
    for (u32 i = 0; i < mTargets.count(); i++) {
        if (mTargets[i].mType == type) {
            mTargets.removeAtIndex(i);
            return;
        }
    }
}

}
}
}
