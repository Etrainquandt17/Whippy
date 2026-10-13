#include "scn/step/hero/Guard.h"

namespace {

const u32 T_ALPHA_TABLE[20] = {
    0xC0, 0xC0, 0xA0, 0x90, 0x80, 0x60, 0x40, 0x20, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x60, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00,
};

}

namespace scn {
namespace step {
namespace hero {

Guard::Guard(Hero& hero)
    : mHero(hero) {
    mIsGuard = false;
    mIsFlash = false;
    mAnimFrame = 0;
}

Guard::~Guard() {}

void Guard::update() {
    if (mIsGuard) {
        mAnimFrame++;
        if (mAnimFrame >= 20) {
            mAnimFrame = 12;
        }
    }
    mIsFlash = mIsGuard;
}

void Guard::resetAnimFrame() {
    mAnimFrame = 0;
}

void Guard::setGuard(bool isGuard) {
    mIsGuard = isGuard;
    if (mIsFlash) {
        return;
    }
    if (mIsGuard != true) {
        return;
    }
    resetAnimFrame();
}

bool Guard::isGuard() const {
    return mIsGuard;
}

GXColor Guard::getColor() const {
    GXColor color;
    u32 alpha = 0;
    if (mIsGuard) {
        alpha = T_ALPHA_TABLE[mAnimFrame];
    }
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = alpha;
    return color;
}

}
}
}
