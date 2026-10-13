#ifndef HID_RUMBLERESOURCE_H
#define HID_RUMBLERESOURCE_H

#include "file/FileAccessor.h"
#include "types.h"
#include "xdata/XData.h"

namespace hid {

enum RumbleResourceKind {
    RUMBLE_RESOURCE_KIND_MAIN,
    RUMBLE_RESOURCE_KIND_SUBGAME,
};

class RumbleResource {
public:
    RumbleResource(RumbleResourceKind kind);

    const void* commandList(u32 index) const;

private:
    file::FileAccessor mFile;
    xdata::XData mXData;
};

}

#endif
