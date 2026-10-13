#ifndef NW4R_UT_RESFONT_H
#define NW4R_UT_RESFONT_H

#include "types.h"

namespace nw4r {
namespace ut {

// TODO: members and virtual functions. 0x10 bytes.
class Font {
private:
    u32 _0[4];
};

// TODO: members and the base class nw4r::ut::detail::ResFontBase. 0x1C bytes.
class ResFont : public Font {
public:
    ResFont();
    ~ResFont();

    bool SetResource(void* resource);
    void* RemoveResource();

private:
    u32 _10[3];
};

}}  // namespace nw4r::ut

#endif
