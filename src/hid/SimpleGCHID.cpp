#include "hid/SimpleGCHID.h"

namespace hid {

// TODO: inline in the original; it belongs in its header, which declares it
// out of line for the units that call it.
inline Button::Button(const Button& other)
    : mHold(other.mHold)
    , mTrigger(other.mTrigger)
    , mRelease(other.mRelease) {}

SimpleGCHID::SimpleGCHID()
    : mMainStick(128)
    , mSubStick(128) {
    GCUpdateData data = {};
    update(data);
    update(data);
}

void SimpleGCHID::update(const GCUpdateData& data) {
    mPrevUpdateData = data;
    if (!mPrevUpdateData.isConnected) {
        mPrevUpdateData.input = GCUpdateData::Input();
    }
    mButton.update(mPrevUpdateData.input.button);
    mMainStick.update(mPrevUpdateData.input.mainStick.x, mPrevUpdateData.input.mainStick.y);
    mSubStick.update(mPrevUpdateData.input.subStick.x, mPrevUpdateData.input.subStick.y);
}

Button SimpleGCHID::button() const {
    return mButton;
}

bool SimpleGCHID::isConnected() const {
    return mPrevUpdateData.isConnected;
}

}  // namespace hid
