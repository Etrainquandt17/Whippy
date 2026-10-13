#ifndef SCN_STEP_CHARA_SHAKE_H
#define SCN_STEP_CHARA_SHAKE_H

#include "scn/step/chara/ShakeKind.h"

namespace scn {
namespace step {
namespace chara {

// TODO: the members are unknown.
class Shake {
public:
    void request(ShakeKind kind);
};

}
}
}

#endif
