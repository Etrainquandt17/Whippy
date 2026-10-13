#include "scn/step/boss/DeadFlash.h"

namespace scn {
namespace step {
namespace boss {

namespace {

const u8 T_ALPHA_TABLE[] = { 0x50, 0x60, 0x70, 0x80, 0x78, 0x70, 0x68, 0x60, 0x58, 0x50, 0x40, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

}

DeadFlash::DeadFlash() : mColor((GXColor){ 0xC0, 0xC0, 0xC0, 0x00 }), mIsValid(false), mCount(0) {}

void DeadFlash::update() {
    if (!mIsValid) {
        return;
    }
    mCount++;
    if (mCount >= 21) {
        mCount = 0;
    }
    mColor.a = T_ALPHA_TABLE[mCount];
}

void DeadFlash::setIsValid(bool isValid) {
    mIsValid = isValid;
}

bool DeadFlash::isValid() const {
    return mIsValid;
}

GXColor DeadFlash::getColor() const {
    return mColor;
}

}}}  // namespace scn::step::boss
