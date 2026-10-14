#include "scn/step/boss/mahoroaroah/BodyEffectCtrl.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

namespace {

const u32 T_TARGET_NODES[] = { 7, 1, 2, 3, 4, 5, 6 };

}

BodyEffectCtrl::BodyEffectCtrl(Boss& boss) : mBoss(boss), mIsVisible(false) {}

BodyEffectCtrl::~BodyEffectCtrl() {}

void BodyEffectCtrl::setVisible(bool isWarp) {
    if (!mIsVisible) {
        mIsVisible = true;
        if (isWarp) {
            mBoss.effect().back().requestN(static_cast<effect::Kind>(0x3BE), 10);
        } else {
            for (u32 i = 0; i < 7; i++) {
                mBoss.effect().back().requestN(static_cast<effect::Kind>(0x3BB), T_TARGET_NODES[i]);
                mBoss.effect().back().requestN(static_cast<effect::Kind>(0x3BC), T_TARGET_NODES[i]);
                mBoss.effect().normal().requestN(static_cast<effect::Kind>(0x3BD), T_TARGET_NODES[i]);
            }
        }
    }
}

void BodyEffectCtrl::setInvisible() {
    if (mIsVisible) {
        mIsVisible = false;
        mBoss.effect().back().release();
        mBoss.effect().normal().release();
    }
}

void BodyEffectCtrl::reqAfterImage() {
    mBoss.effect().back().requestN(static_cast<effect::Kind>(0x3AF), 10);
}

void BodyEffectCtrl::releaseAfterImage() {
    mBoss.effect().back().release();
}

}}}}  // namespace scn::step::boss::mahoroaroah
