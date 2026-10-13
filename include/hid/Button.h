#ifndef HID_BUTTON_H
#define HID_BUTTON_H

#include "types.h"

namespace hid {

class Button {
public:
    Button();
    Button(const Button& other);

    void update(u32 hold);
    bool isHold(u32 mask) const;
    bool isTrigger(u32 mask) const;
    bool isRelease(u32 mask) const;
    u32 hold() const;
    u32 trigger() const;
    u32 release() const;

private:
    u32 mHold;
    u32 mTrigger;
    u32 mRelease;
};

}

#endif
