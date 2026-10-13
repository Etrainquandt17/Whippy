#ifndef MINTVM_XDATA_H
#define MINTVM_XDATA_H

#include "types.h"

namespace mintx {

struct XDataHeader {
    u32 mMagic;
    u16 mEndian;
    u8 mVersion;
    u8 _7;
    u32 mSize;
    u32 _C;
};

class XData {
public:
    XData(const void* data)
        : mHeader(static_cast<const XDataHeader*>(data)) {}

    const void* dataHeadAddress() const {
        return isValidData() ? mHeader + 1 : 0;
    }

    bool isValidData() const {
        return isValidVersion() && mHeader->mSize >= sizeof(XDataHeader);
    }

    const char* R2String(unsigned int reference) const {
        return static_cast<const char*>(labelAddressWithReference(reference));
    }

    const void* labelAddressWithReference(unsigned int reference) const {
        if (!isValidData()) {
            return 0;
        }
        if (reference < sizeof(XDataHeader) || mHeader->mSize < reference) {
            return 0;
        }
        return reinterpret_cast<const u8*>(mHeader) + reference;
    }

private:
    // TODO: the names of these four are guesses. The original only shows that the checks nest.
    bool isValidMagic() const {
        return mHeader != 0 && mHeader->mMagic == 'XBIN';
    }

    bool isValidEndian() const {
        return isValidMagic() && mHeader->mEndian == 0x1234;
    }

    bool isValidMajorVersion() const {
        return isValidEndian() && mHeader->mVersion == 2;
    }

    bool isValidVersion() const {
        return isValidMajorVersion() && mHeader->_7 == 0;
    }

    const XDataHeader* mHeader;
};

}  // namespace mintx

#endif
