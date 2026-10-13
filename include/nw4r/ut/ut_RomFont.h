#ifndef NW4R_UT_ROMFONT_H
#define NW4R_UT_ROMFONT_H

#include "types.h"

namespace nw4r {
namespace ut {

// TODO: members and the base class nw4r::ut::Font. 0x1C bytes.
class RomFont {
public:
    static u32 GetRequireBufferSize();

    RomFont();
    ~RomFont();

    bool Load(void* buffer);
    void* Unload();

private:
    u32 _0[7];
};

}
}

#endif
