#ifndef XDATA_XDATA_H
#define XDATA_XDATA_H

#include "types.h"

namespace xdata {

class XData {
public:
    XData() : mData(0) {}
    explicit XData(const void* data) : mData(data) {}

    bool isValidData() const;
    const void* labelAddressWithReference(unsigned int offset) const;
    const void* dataHeadAddress() const;

    const void* data() const { return mData; }

private:
    // TODO: the names of these two are guesses, as in mintvm/XData.h. isValidData is built on them; a unit
    // that expands it defines it itself until this header can.
    bool isValidMagic() const { return mData != 0 && *static_cast<const u32*>(mData) == 'XBIN'; }
    bool isValidEndian() const { return isValidMagic() && static_cast<const u16*>(mData)[2] == 0x1234; }

    const void* mData;
};

}  // namespace xdata

#endif
