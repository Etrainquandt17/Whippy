#ifndef SCN_STEP_ENEMY_ROCKY_BRAINWALK_H
#define SCN_STEP_ENEMY_ROCKY_BRAINWALK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

class BrainWalk : public BrainBase {
public:
    BrainWalk(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
