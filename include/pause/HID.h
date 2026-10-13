#ifndef PAUSE_HID_H
#define PAUSE_HID_H

#include "hid/Button.h"
#include "types.h"

namespace pause {

class HID {
public:
    u32 padChan() const;
    hid::Button btn() const;
};

}  // namespace pause

#endif
