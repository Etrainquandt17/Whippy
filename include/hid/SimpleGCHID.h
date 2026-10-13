#ifndef HID_SIMPLEGCHID_H
#define HID_SIMPLEGCHID_H

#include "hid/Button.h"
#include "hid/Stick.h"
#include "types.h"

namespace hid {

struct GCUpdateData {
    struct StickInput {
        s32 x;
        s32 y;
    };

    struct Input {
        s32 button;
        StickInput mainStick;
        StickInput subStick;
    };

    bool isConnected;
    Input input;
};

class SimpleGCHID {
public:
    SimpleGCHID();

    void update(const GCUpdateData& data);
    Button button() const;
    Stick mainStick() const;
    Stick subStick() const;
    GCUpdateData prevUpdateData() const;
    bool isConnected() const;

private:
    GCUpdateData mPrevUpdateData;
    Button mButton;
    Stick mMainStick;
    Stick mSubStick;
};

}

#endif
