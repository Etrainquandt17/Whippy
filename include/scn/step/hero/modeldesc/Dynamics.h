#ifndef SCN_STEP_HERO_MODELDESC_DYNAMICS_H
#define SCN_STEP_HERO_MODELDESC_DYNAMICS_H

#include "dynamics/Desc.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace modeldesc {

class Dynamics {
public:
    // TODO: names of the members.
    struct NodeParam {
        f32 _0[9];
    };

    static void SetDescNode(dynamics::DescNode& node, const NodeParam& param);
};

}
}
}
}

#endif
