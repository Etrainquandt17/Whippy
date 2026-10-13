#include "scn/step/boss/Invincible.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/chara/HitPoint.h"

namespace scn {
namespace step {
namespace boss {

Invincible::Invincible(Boss& boss) : mBoss(boss), mInvincible(), mColor((GXColor){ 0xFF, 0xFF, 0xFF, 0x00 }), mIsNoFlash(false) {}

void Invincible::update() {
    mInvincible.update();
    u32 alpha = mInvincible.getFlashAlpha();
    if (mIsNoFlash) {
        alpha = 0;
    }
    mColor.a = alpha;
}

void Invincible::setPerm() {
    mInvincible.setPerm();
}

void Invincible::setPermNoFlash() {
    setPerm();
    mIsNoFlash = true;
}

void Invincible::unsetPerm() {
    mInvincible.unsetPerm();
    mIsNoFlash = false;
}

bool Invincible::isInvincible() const {
    if (mBoss.hitPoint().isDead()) {
        return false;
    }
    return mInvincible.isInvincible();
}

}}}  // namespace scn::step::boss
