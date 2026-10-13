#ifndef SCN_STEP_GIMMICK_BLOCK_BLOCKRESFILES_H
#define SCN_STEP_GIMMICK_BLOCK_BLOCKRESFILES_H

#include "g3d/ResFileAccessor.h"
#include "scn/step/map/BinGmkBlockKind.h"

namespace scn {
namespace step {
namespace gimmick {
namespace block {

class BlockResFiles {
public:
    g3d::ResFileAccessor get(map::BinGmkBlockKind kind);
    const char* entryName(map::BinGmkBlockKind kind) const;
};

}
}
}
}

#endif
