#ifndef SCN_STEP_MAP_BINGMKGENERALENTRY_H
#define SCN_STEP_MAP_BINGMKGENERALENTRY_H

#include "scn/step/map/BinMaproPos.h"
#include "types.h"

namespace scn {
namespace step {
namespace map {

struct BinGmkGeneralEntry {
    u32 _0;
    BinMaproPos _4;
    u8 _C[0x14 - 0xC];
    u32 _14;
    u32 _18;
    u32 _1C;
};

}
}
}

#endif
