#ifndef SCN_STEP_SFX_WIPE_H
#define SCN_STEP_SFX_WIPE_H

#include "hel/math/Vector3.h"
#include "scn/step/sfx/WipeKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace sfx {

// TODO: members.
class Wipe {
public:
    void requestWipeOut(WipeKind kind, const hel::math::Vector3& center, u32, u32 frame);
};

}
}
}

#endif
