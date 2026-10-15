#include "scn/step/boss/goliath/EyeCtrl.h"

#include "gobj/Anim.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace {

const u32 T_EYE_OPEN_FRAME_TABLE[6] = { 120, 120, 60, 120, 120, 30 };

}

EyeCtrl::EyeCtrl(Boss& boss) : mBoss(boss), mIsAngry(false), mIsOpen(true), mIsAnim(true), mFrame(0), mOpenIndex(0) {
    setFrame();
}

void EyeCtrl::update() {
    if (mIsAnim) {
        if (mFrame != 0) {
            mFrame--;
        } else {
            mIsOpen = !mIsOpen;
            setSubAnim();
            setFrame();
        }
    }
}

void EyeCtrl::setAngry(bool isAngry) {
    mIsAngry = isAngry;
    mIsOpen = true;
    setSubAnim();
    setFrame();
}

void EyeCtrl::setKeepOpen() {
    if (!mIsOpen) {
        mIsOpen = true;
        setSubAnim();
        setFrame();
    }
    mIsAnim = false;
}

void EyeCtrl::startAnim() {
    mIsAnim = true;
}

void EyeCtrl::setFrame() {
    if (mIsOpen) {
        mFrame = T_EYE_OPEN_FRAME_TABLE[mOpenIndex];
        mOpenIndex++;
        if (mOpenIndex == 6) {
            mOpenIndex = 0;
        }
    } else {
        mFrame = 6;
    }
}

void EyeCtrl::setSubAnim() {
    u32 anim;
    if (mIsOpen) {
        anim = mIsAngry ? 0x49 : 0x4C;
    } else {
        anim = 0x4B;
    }
    mBoss.model().anim().subAnimClear(1);
    mBoss.model().anim().subAnimSet(1, anim, 10);
}

}}}}  // namespace scn::step::boss::goliath
