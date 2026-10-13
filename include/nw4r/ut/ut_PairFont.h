#ifndef NW4R_UT_PAIRFONT_H
#define NW4R_UT_PAIRFONT_H

#include "nw4r/ut/ut_ResFont.h"
#include "types.h"

namespace nw4r {
namespace ut {

// TODO: members and virtual functions. 0x1C bytes.
class PairFont : public Font {
public:
    PairFont(Font* primary, Font* secondary);
    ~PairFont();

private:
    u32 _10[3];
};

}
}

#endif
