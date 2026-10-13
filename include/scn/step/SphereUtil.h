#ifndef SCN_STEP_SPHEREUTIL_H
#define SCN_STEP_SPHEREUTIL_H

#include "scn/step/SphereUnlockKind.h"
#include "types.h"

namespace scn {
namespace step {

class SphereUtil {
public:
    static u32 GetNeedSphere(SphereUnlockKind kind);
};

}
}

#endif
