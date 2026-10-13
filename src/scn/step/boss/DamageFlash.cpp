#include "scn/step/boss/DamageFlash.h"

namespace scn {
namespace step {
namespace boss {

namespace {

const u8 T_ALPHA_TABLE[] = { 0x60, 0x18, 0x40, 0x0C, 0x20, 0x00, 0x10, 0x00, 0x08, 0x00 };

}

DamageFlash::DamageFlash() : mColor((GXColor){ 0, 0, 0, 0 }), mFrame(0), mCount(0), mCombo(0) {}

void DamageFlash::update() {
    if (mFrame != 0) {
        mFrame--;
    }
    if (mFrame == 0) {
        mColor.a = 0;
        return;
    }
    mCount++;
    if (mCount >= 20) {
        mCount -= 4;
    }
    mColor.a = T_ALPHA_TABLE[mCount / 2];
}

void DamageFlash::set(ocoll::Element element, u32 frame) {
    switch (element) {
    case ocoll::ELEMENT_1:
    case ocoll::ELEMENT_18:
    case ocoll::ELEMENT_9:
        mColor = (GXColor){ 0xF0, 0xFF, 0xA0, 0xFF };
        break;
    case ocoll::ELEMENT_2:
    case ocoll::ELEMENT_19:
        mColor = (GXColor){ 0xA0, 0x50, 0x00, 0xFF };
        break;
    case ocoll::ELEMENT_3:
        mColor = (GXColor){ 0xA0, 0xF0, 0xFF, 0xFF };
        break;
    case ocoll::ELEMENT_4:
        mColor = (GXColor){ 0xA0, 0xFF, 0x50, 0xFF };
        break;
    default:
        mColor = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
        break;
    }
    if (mFrame != 0) {
        mCombo++;
    } else {
        mCombo = 0;
    }
    if (mCombo > 4) {
        mCount = 16;
    } else if (mCombo > 3) {
        mCount = 12;
    } else if (mCombo > 2) {
        mCount = 8;
    } else if (mCombo > 1) {
        mCount = 4;
    } else {
        mCount = 0;
    }
    mColor.a = T_ALPHA_TABLE[mCount / 2];
    mFrame = frame;
}

void DamageFlash::cancel() {
    mFrame = 0;
}

bool DamageFlash::isValid() const {
    return mFrame != 0;
}

GXColor DamageFlash::getColor() const {
    return mColor;
}

}
}
}
