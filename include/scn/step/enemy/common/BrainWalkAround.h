#ifndef SCN_STEP_ENEMY_COMMON_BRAINWALKAROUND_H
#define SCN_STEP_ENEMY_COMMON_BRAINWALKAROUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class BrainWalkAround : public BrainBase {
public:
    BrainWalkAround(Enemy& enemy);
    virtual bool onLanding();
};

}
}
}
}

#endif
