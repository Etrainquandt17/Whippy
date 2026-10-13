#ifndef SCN_STEP_GIMMICK_BLOCK_BLOCKEFFREQUESTINFO_H
#define SCN_STEP_GIMMICK_BLOCK_BLOCKEFFREQUESTINFO_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace gimmick {
namespace block {

class BlockEffRequestInfo {
public:
    struct Info {
        u32 _0;
        u32 _4;
        f32 _8;
        f32 _C;
        hel::math::Vector3 _10;
        hel::math::Vector3 _1C;
    };
};

}
}
}
}

#endif
