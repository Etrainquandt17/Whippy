#include "scn/step/boss/GuardFlash.h"

namespace scn {
namespace step {
namespace boss {

namespace {

const u8 T_ALPHA_TABLE[] = { 0x00, 0x00, 0x64, 0x64 };

}

GuardFlash::GuardFlash() : mColor((GXColor){ 0xC0, 0xC0, 0xC0, 0x00 }), mIsValid(false), mCount(0) {}

void GuardFlash::update() {
    if (!mIsValid) {
        return;
    }
    mCount++;
    if (mCount >= 4) {
        mCount = 0;
    }
    mColor.a = T_ALPHA_TABLE[mCount];
}

void GuardFlash::setIsValid(bool isValid) {
    mIsValid = isValid;
}

bool GuardFlash::isValid() const {
    return mIsValid;
}

GXColor GuardFlash::getColor() const {
    return mColor;
}

}}}  // namespace scn::step::boss
