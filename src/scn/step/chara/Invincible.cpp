#include "scn/step/chara/Invincible.h"

namespace scn {
namespace step {
namespace chara {

namespace {

const u32 T_ALPHA_ANIM_TABLE[10] = {0xF0, 0x50, 0xA0, 0x14, 0x8C, 0x0A, 0x78, 0x00, 0x64, 0x00};

}

Invincible::Invincible() {
    mFrame = 0;
    mAnimFrame = 0;
    mIsPerm = false;
    mIsMighty = false;
}

void Invincible::update() {
    if (isInvincible()) {
        updateFrame();
        if (++mAnimFrame == 0x14) {
            mAnimFrame = 0x10;
        }
    }
}

bool Invincible::isInvincible() const {
    return mIsPerm || mIsMighty || mFrame != 0;
}

void Invincible::set(u32 frames) {
    if (mFrame < frames) {
        mFrame = frames;
    }
    mAnimFrame = 0;
}

void Invincible::clear() {
    mFrame = 0;
    unsetPerm();
}

void Invincible::setPerm() {
    mIsPerm = true;
    mAnimFrame = 0;
}

void Invincible::unsetPerm() {
    mIsPerm = false;
}

bool Invincible::isPerm() const {
    return mIsPerm;
}

void Invincible::setMighty() {
    mIsMighty = true;
}

void Invincible::unsetMighty() {
    mIsMighty = false;
}

bool Invincible::isMighty() const {
    return mIsMighty;
}

u32 Invincible::getFrame() const {
    return mFrame;
}

u32 Invincible::getFlashAlpha() const {
    if (isInvincible()) {
        return T_ALPHA_ANIM_TABLE[mAnimFrame / 2];
    }
    return 0;
}

void Invincible::updateFrame() {
    if (mFrame != 0) {
        mFrame--;
    }
}

}
}
}
