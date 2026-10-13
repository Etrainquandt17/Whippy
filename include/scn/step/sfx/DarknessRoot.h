#ifndef SCN_STEP_SFX_DARKNESSROOT_H
#define SCN_STEP_SFX_DARKNESSROOT_H

#include "types.h"

namespace scn {
namespace step {
namespace sfx {

class DarknessLight;

// TODO: members and the other functions.
class DarknessRoot {
public:
    void lightsAdd(DarknessLight& light);
};

}
}
}

#endif
