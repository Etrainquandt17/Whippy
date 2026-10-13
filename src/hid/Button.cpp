#include "hid/Button.h"

namespace hid {

Button::Button()
    : mHold(0)
    , mTrigger(0)
    , mRelease(0) {}

void Button::update(u32 hold) {
    u32 prev = mHold;
    mHold = hold;
    mTrigger = mHold & ~prev;
    mRelease = prev & ~mHold;
}

bool Button::isHold(u32 mask) const {
    return mHold & mask;
}

bool Button::isTrigger(u32 mask) const {
    return mTrigger & mask;
}

u32 Button::hold() const {
    return mHold;
}

u32 Button::trigger() const {
    return mTrigger;
}

u32 Button::release() const {
    return mRelease;
}

}
