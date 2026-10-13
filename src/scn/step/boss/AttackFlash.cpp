#include "scn/step/boss/AttackFlash.h"

#include "hel/math/Math.h"

namespace scn {
namespace step {
namespace boss {

AttackFlash::AttackFlash() : mColor((GXColor){ 0xFF, 0xFF, 0xFF, 0x00 }), mState(0), mAngle(0.0f), mAlpha(0.0f), mAlphaIncRate(2.0f) {}

void AttackFlash::update() {
    if (!isValid()) {
        return;
    }
    switch (mState) {
    case 1: {
        mAngle += 90.0f;
        if (mAngle >= 360.0f) {
            mAngle -= 360.0f;
        }
        mAlpha += mAlphaIncRate;
        if (mAlpha > 200.0f) {
            mAlpha = 200.0f;
        }
        int alpha = static_cast<int>(mAlpha) + static_cast<int>(40.0f * hel::math::Math::SinDegF(mAngle));
        mColor.a = hel::math::Math::LimitMinMax(alpha, 0, 255);
        break;
    }
    case 2: {
        int alpha = mColor.a - 5;
        if (alpha < 0) {
            alpha = 0;
            mState = 0;
        }
        mColor.a = alpha;
        break;
    }
    }
}

void AttackFlash::setStart(GXColor color) {
    mState = 1;
    mColor = color;
    mAngle = 0.0f;
    mAlpha = 0.0f;
}

void AttackFlash::setContinue() {
    mState = 1;
}

void AttackFlash::setEnd(GXColor color) {
    mState = 2;
    mColor = color;
}

void AttackFlash::cancel() {
    mState = 0;
}

void AttackFlash::setAlphaIncRate(f32 rate) {
    mAlphaIncRate = rate;
}

bool AttackFlash::isValid() const {
    return mState != 0;
}

GXColor AttackFlash::getColor() const {
    return mColor;
}

}}}  // namespace scn::step::boss
