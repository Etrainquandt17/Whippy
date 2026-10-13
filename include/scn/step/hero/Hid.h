#ifndef SCN_STEP_HERO_HID_H
#define SCN_STEP_HERO_HID_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hid {
public:
    void disableInputs();
    bool isHold(u32 mask) const;
    bool isTrigger(u32 mask) const;
    void setAutoInputHold(u32 mask);
    bool isEnableInputs() const;
    void setIgnoreInputUntilRelease(u32 mask);
    void cancelTrigger(u32 mask);
};

}
}
}

#endif
