#ifndef HID_HIDMANAGER_H
#define HID_HIDMANAGER_H

#include "hid/SimpleGCHID.h"
#include "hid/SimpleWRHID.h"
#include "types.h"

namespace hid {

class HIDManager {
public:
    const SimpleWRHID& gameWR(u32 index) const;
    const SimpleGCHID& debugGC(u32 index) const;
    bool isDPDEnable() const;
    void setIsDPDEnable(bool enable);
};

}  // namespace hid

#endif
