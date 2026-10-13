#include "hid/RumbleResource.h"

// TODO: inline in the original; they belong in their header, which declares them
// out of line for the units that call them.
namespace xdata {

inline const void* XData::dataHeadAddress() const {
    return isValidData() ? static_cast<const u8*>(mData) + 0x10 : 0;
}

inline const void* XData::labelAddressWithReference(unsigned int offset) const {
    if (!isValidData()) {
        return 0;
    }
    if (offset < 0x10 || static_cast<const u32*>(mData)[2] < offset) {
        return 0;
    }
    return static_cast<const u8*>(mData) + offset;
}

}

namespace hid {

namespace {

const char* T_DAT_PATH_TABLE[2] = {
    "hid/rumble/Rumble.dat.cmp",
    "hid/rumble/subgame/Rumble.dat.cmp",
};

}

RumbleResource::RumbleResource(RumbleResourceKind kind)
    : mFile(T_DAT_PATH_TABLE[kind], false)
    , mXData(mFile.block().startAddress()) {}

const void* RumbleResource::commandList(u32 index) const {
    const u32* head = static_cast<const u32*>(mXData.dataHeadAddress());
    return mXData.labelAddressWithReference(head[index + 1]);
}

}
